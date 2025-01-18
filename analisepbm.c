#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "definitions.h"

//Função de verificação de extensão .pbm
int tem_extensao_pbm(const char *nome_arquivo)
{
    const char *extensao = strrchr(nome_arquivo, '.'); //Localiza o último ponto no nome do arquivo
    if(extensao != NULL) //Se não retornar nada, nem extensão possui
    {
        if(strcmp(extensao, ".pbm") == 0) //Compara do ponto pra frente com a string ".pbm"
        {
            return 1; //Verdadeiro, é um .pbm
        }
    }
    return 0; //Falso, não é .pbm
}

//Função que fecha o arquivo e o programa simultâneamente para não haver corrompimento do arquivo
void erro_encontrado(FILE *arquivo)
{
    fclose(arquivo); //Fecha arquivo
    exit(1); //Fim de código
}

//Função de verificação de existência de arquivo
int arquivo_existe(const char *nome_arquivo) {
    //Abrindo arquivo para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    //Se arquivo existir, fecha imediatamente e retorna verdadeiro
    if (arquivo) 
    {
        fclose(arquivo);
        return 1;
    }
    return 0;
}

//Função que recebe o arquivo enviado e verifique se é válido ou não, possui diversas condicionais que buscam analisar cada problema possível
void verificar_validade_pbm(FILE *arquivo)
{
        if(arquivo == NULL) //Caso não houver arquivo
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    char cabecalho[4];
    if (fgets(cabecalho, sizeof(cabecalho), arquivo) == NULL)
    {
        printf("Erro ao ler cabeçalho\n"); //Caso haja erro ao ler a primeira linha do bpm, fim de código
        erro_encontrado(arquivo);
    }
    cabecalho[strcspn(cabecalho, "\n")] = '\0'; //Tratamento do cabeçalho
    if (strcmp(cabecalho, "P1") != 0) //Checa se o cabeçalho é realmente P1, cao não, fim de código
    {
        printf("Erro: Arquivo .pbm inválido");
        erro_encontrado(arquivo);
    }
}

//Função que registra em dois ponteiros a largura e altura do bpm, passadas na segunda linha
void registrar_dimensao_pbm(FILE *arquivo, int *largura, int *altura)
{
    char linha[100]; //Iniciando string que recebe a segunda linha inteira
    if (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%d %d", largura, altura); //Caso a linha esteja na formatação "%d %d", escaneia ints
    }
    else
    {
        printf("Erro ao ler as dimensões.\n"); //Caso contrário, fim de código
        erro_encontrado(arquivo);
    }
}

void pegar_espacamento_codigo(FILE *arquivo, int largura, int *espacamento_lateral, char* codigo_barra)
{
    int contador = 0;
    int condicao = 0;
    char linha[(largura + 1) * 2];
    while(fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        for (int i = 0; linha[i] != '\0'; i++)
        {
            if(linha[i] == '1')
            {
                condicao = 1;
                break;
            }
        }
        if(condicao == 1) break;
        contador++;
    }
    *espacamento_lateral = contador;
    strcpy(codigo_barra, linha);
}

char* criar_verificador(char *codigo_barra, int espacamento_lateral, int area)
{
    char *verificador = malloc(68 * sizeof(char));
    verificador[67] = '\0';
    for (int i = 0; i < 67; i++)
    {
        verificador[i] = codigo_barra[i * area * 2 + (espacamento_lateral * 2)];
    }
    return verificador;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "definitions.h"
#include "verificador.c"
//Tratamento do primeiro parâmetro
int* tratarIdentificador(const char *input)
{
    //Verificamos se está do tamanho correto
    if (strlen(input) != 8)
    {
        printf("Erro: o número deve conter exatamente 8 dígitos\n");
        return NULL;
    }
    //Alocamos dinamicamente o vetor que irá ser retornado no final
    int *num = malloc(8 * sizeof(int));
    for (int i = 0; i < 8; i++)
    {
        //Verificamos se todos os dígitos são de fato números
        if (input[i] < '0' || input[i] > '9')
        {
            printf("Erro: Apenas números são permitidos.\n");
            free(num);
            return NULL;
        }
        //Alocamos cada novo dígito como um número no vetor novo
        num[i] = input[i] - '0';
    }
    //Verificamos se o dígito final é válido
    if(verificarDigitoVerificador(num) != 1){
        printf("Erro: Dígito verificador inválido.\n");
        return NULL;
    }
    return num;
}

void gerarArquivoPBM(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo)
{
    int largura = 67 * 3 + 2 * espaco_lateral;
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }
    char *stringArea = criarStringArea(verificador);
    fprintf(arquivo, "P1\n%d %d\n", largura, altura_barra);
    for (int i = 0; i < altura_barra; i++)
    {
        printarLateral(arquivo, espaco_lateral);
        for (int j = 0; j < 67; j++)
        {
            for (int k = 0; k < pixel_area; k++)
            {
                fprintf(arquivo, "%c ", stringArea[j]);
            }
        }
        printarLateral(arquivo, espaco_lateral);
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
    free(stringArea);
}

int main(int argc, char const *argv[])
{
    if (argc < 2 || argc > 6)
    {
        printf("Uso: %s <identificador> [espacamento_lateral] [quantidade_pixels_area] [altura_barras] [nome_imagem]\n", argv[0]);
        return 1;
    }
    const char *identificador = argv[1];
    int espaco_lateral = (argc > 2) ? atoi(argv[2]) : 4;
    int pixel_area = (argc > 3) ? atoi(argv[3]) : 3;
    int altura_barra = (argc > 4) ? atoi(argv[4]) : 50;
    const char *nome_arquivo = (argc > 5) ? argv[5] : "codigo_de_barras.pbm";
    int *new_identificador = tratarIdentificador(identificador);
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo)
    {
        fclose(arquivo);
        char resposta;
        printf("O arquivo %s já existe. Deseja sobrecrevê-lo? (s/n): ", nome_arquivo);
        resposta == getchar();
        if(resposta != 's' && resposta != 'S')
        {
            printf("Erro: Arquivo já existe.\n");
            return 1;
        }
    }

    return 0;
}
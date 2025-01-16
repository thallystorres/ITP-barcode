#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "definitions.h"
#include "verificador.c"
#include "pbm.c"

//Tratamento do primeiro parâmetro
int* tratar_identificador(const char *input)
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
    if(verificar_digito_verificador(num) != 1){
        printf("Erro: Dígito verificador inválido.\n");
        return NULL;
    }
    return num;
}

int main(int argc, char const *argv[])
{
    //Verificando os argumentos passados por linha de comando, se não obedecerem o total e mínimo requerido o programa se encerra
    if (argc < 2 || argc > 6)
    {
        printf("Uso: %s <identificador> [espacamento_lateral] [quantidade_pixels_area] [altura_barras] [nome_imagem]\n", argv[0]);
        return 1;
    }
    //Direcionando cada argumento para uma variável
    //Char constante imutável do identificador (sequência de 8 números)
    const char *identificador = argv[1];
    //Se for dado três ou mais argumentos, o terceiro será o espaçamento lateral da imagem, caso não for passado, adota 4 pixels como pré-definição
    int espaco_lateral = (argc > 2) ? atoi(argv[2]) : 4;
    //Se for dado quatro ou mais argumentos, o quarto será o número de pixels por área de código de barras, caso não for passado, adota 3 pixels como pré-definição
    int pixel_area = (argc > 3) ? atoi(argv[3]) : 3;
    //Se for dado cinco ou mais argumentos, o quinto será a altura do código de barras em pixels, caso não for passado, adota 50 de altura como pré-definição
    int altura_barra = (argc > 4) ? atoi(argv[4]) : 50;
    //Se for dado seis argumentos, o sexto será o nome do arquivo a ser criado, caso não for passasdo, adota o nome template "codigo_de_barras.pbm"
    const char *nome_arquivo = (argc > 5) ? argv[5] : "codigo_de_barras.pbm";
    //Tratamento do identificador passado como argumento usando a função tratarIdentificador
    int *new_identificador = tratar_identificador(identificador);
    //Verificando se o identificador novo é válido ou não, caso não, encerra o programa
    if (new_identificador == NULL)
    {
        return 1;
    }
    //Verificando a já existência do arquivo
    if(arquivo_existe(nome_arquivo))
    {
        //Declarando char de resposta s/n
        char resposta;
        printf("O arquivo %s já existe. Deseja sobrecrevê-lo? (s/n): ", nome_arquivo);
        resposta = getchar();
        //Se resposta for não, então finaliza-se o programa
        if(resposta != 's' && resposta != 'S')
        {
            printf("Erro: Arquivo já existe.\n");
            return 1;
        }
    }
    //Gerando arquivo .pbm e encerrando o programa
    gerar_arquivo_pbm(new_identificador, espaco_lateral, pixel_area, altura_barra, nome_arquivo);
    return 0;
}
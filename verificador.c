#include "definitions.h"

//Função para calcular o dígito verificador
int calcula_digito_verificador(int *identificador) {
    int soma = 0;
    for (int i = 0; i < TAMANHO_IDENTIFICADOR - 1; i++) {
        int peso = (i % 2 == 0) ? 3 : 1; //Verifica o peso do dígito, se for par peso 3 se for ímpar peso 1
        soma += (identificador[i]) * peso; //Soma os dígitos
    }
    int digito_verificador = (10 - (soma % 10)) % 10; //Define o digito identificador usando mod
    return digito_verificador;
}

//Função que verifica a validez do digito verificador
int validar_digito_verificador(int *identificador)
    {
    int digito_verificador = calcula_digito_verificador(identificador);
    //Se o dígito verificador não estiver de acordo com o cálculo, retorne 1 para verdadeiro ou 0 para falso
    return (digito_verificador == identificador[TAMANHO_IDENTIFICADOR-1]);
}

//Tratamento do primeiro parâmetro
int* tratar_identificador(const char *input)
{
    //Verificamos se está do tamanho correto
    if (strlen(input) != TAMANHO_IDENTIFICADOR)
    {
        printf("Erro: o número deve conter exatamente %d dígitos\n", TAMANHO_IDENTIFICADOR);
        return NULL;
    }
    //Alocamos dinamicamente o vetor que irá ser retornado no final
    int *num;
    num = malloc(TAMANHO_IDENTIFICADOR * sizeof(int));
    for (int i = 0; i < TAMANHO_IDENTIFICADOR; i++)
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
    if(validar_digito_verificador(num) != 1){
        printf("Erro: Dígito verificador inválido.\n");
        return NULL;
    }
    return num;
}

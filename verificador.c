#include <stdio.h>
#include "definitions.h"

// Função para calcular o dígito verificador
int calculaDigitoVerificador(int *identificador) {
    int soma = 0;
    for (int i = 0; i < 8 - 1; i++) {
        int peso = (i % 2 == 0) ? 3 : 1; //Verifica o peso do dígito, se for par peso 3 se for ímpar peso 1
        soma += (identificador[i]) * peso; //Soma os dígitos
    }
    int digito_verificador = (10 - (soma % 10)) % 10; //Define o digito identificador usando mod
    return digito_verificador;
}

int verificarDigitoVerificador(int *identificador)
    {
    int digito_verificador = calculaDigitoVerificador(identificador);
    // Se o dígito verificador não estiver de acordo com o cálculo, retorne 1 para verdadeiro ou 0 para falso
    return (digito_verificador == identificador[7]);
}

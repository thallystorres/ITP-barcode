#include <stdio.h>
#include "definitions.h"

// Função para calcular o dígito verificador
int verificarDigito(int ean[8])
    {
        int soma = 0;

    // Calcula a soma dos dígitos com os pesos
    for (int i = 0; i < 7; i++)
    {
        if (i % 2 == 0)
        {
            soma += ean[i] * 3; // Multiplica os dígitos nas posições ímpares por 3
        }
        else
        {
            soma += ean[i]; // Multiplica os dígitos nas posições pares por 1
        }
    }

    // Calcula o dígito verificador
    int digitoVerificador = (10 - (soma % 10)) % 10;
    // Se o dígito verificador não estiver de acordo com o cálculo, retorne 1 para verdadeiro ou 0 para falso
    if(digitoVerificador == ean[7])
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
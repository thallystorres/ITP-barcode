#include <stdio.h>
#include <string.h>

// Função para converter um int em array

void str_array(char *str, int *array) 
{
    for (int i = 0; i < 7; i++) 
    { 
        // O array recebe os caracteres da string convertidos em seu valor númerico correspondente por meio do ASCII
        array[i] = str[i] - '0'; 
    }

}

// Função para calcular o dígito verificador
int calcularDigitoVerificador(int ean[7])
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

    return digitoVerificador;
}

int main(){
    // Declarando as variáveis
    int array[8];
    int verificador;
    char n[8];

    // Recebe a string n
    fgets(n, sizeof(n), stdin);
    
    // Aplicando função que converte string em vetor
    str_array(n, array);

    // Definimos "verificador" como o valor retornado pela função
    verificador = calcularDigitoVerificador(array);

    // Atribuimos o valor do dígito verificador á última casa do nosso vetor
    array[7] = verificador;

    
   for (int j = 0; j < 8; j++)
   {
        printf("%d", array[j]);
   }
   /*
    printf("%d", k);
   */
    return 0;
}
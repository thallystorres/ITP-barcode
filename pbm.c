#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
#include "verificador.c"

typedef struct {
    int digit;
    char l_code[8];
    char r_code[8];
} DigitCode;

char** transformarCode(int *verificador)
{
    DigitCode codes[] = 
    {
        {0, "0001101", "1110010"},
        {1, "0011001", "1100110"},
        {2, "0010011", "1101100"},
        {3, "0111101", "1000010"},
        {4, "0100011", "1011100"},
        {5, "0110001", "1001110"},
        {6, "0101111", "1010000"},
        {7, "0111011", "1000100"},
        {8, "0110111", "1001000"},
        {9, "0001011", "1110100"}
    };
    char **final = malloc(8 * sizeof(char *));
    for (int i = 0; i < 8; i++)
    {
        final[i] = malloc(8 * sizeof(char));
        for (int j = 0; j < 10; j++)
        {
            if(codes[j].digit == verificador[i])
            {
                if(i < 4)
                {
                    strcpy(final[i], codes[j].l_code);
                }
                else
                {
                    strcpy(final[i], codes[j].r_code);
                }
                break;
            }
        }
    }
    return final;
}

void printarLateral(FILE *arquivo, int espaco_lateral)
{
    for (int i = 0; i < espaco_lateral; i++)
    {
        fprintf(arquivo, "0 ");
    }
    
}

char* criarStringArea(int *verificador)
{
    char **codigo = transformarCode(verificador);
    char *stringArea = (char *)malloc((67+1) * sizeof(char));
    memset(stringArea, '\0', 68);
    strncpy(stringArea, "101", 3);
    strncpy(stringArea + 31, "01010", 5);
    strncpy(stringArea + 64, "101", 3);
    int index = 3; // Começar após os 3 primeiros caracteres
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 7; j++) {
            if (index >= 31 && index < 36) {
                index = 36; // Pular os caracteres reservados para "01010"
            }
            if (index >= 64) {
                break; // Não ultrapassar o limite da string
            }
            stringArea[index++] = codigo[i][j];
        }
    }
    return stringArea;
}

int main(int argc, char const *argv[])
{
    int a[] = {4, 0, 1, 7, 0, 7, 2, 5};
    gerarArquivoPBM(a, 4, 3, 50, "teste.pbm");
}

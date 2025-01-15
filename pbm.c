#include <stdio.h>
#include <string.h>
#include "definitions.h"
#include "verificador.c"
void gerarArquivoPBM(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo)
{
    int largura = 67 * 3 + 2 * espaco_lateral;
    FILE *arquivo = fopen(nome_arquivo, 'w');
    if(arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return 0;
    }

    fprintf(arquivo, "P1\n%d %d\n", largura, altura_barra);
    for (int i = 0; i < altura_barra; i++)
    {
        for (int j = 0; j < espaco_lateral; j++)
        {
            fprintf(arquivo, "0 ");
        }

        for (int j = 0; j < espaco_lateral; j++)
        {
            fprintf(arquivo, "0 ");
        }
    }
    
}
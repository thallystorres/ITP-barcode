#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "definitions.h"
#include "verificador.c"
#include "analisepbm.c"

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("Uso: %s <nome_imagem.pbm>\n", argv[0]);
        return 1;
    }
    const char *nome_arquivo = argv[1];
    if(!arquivo_existe(nome_arquivo))
    {
        printf("Erro: Arquivo não encontrado.\n");
        return 1;
    }
    if(!tem_extensao_pbm(nome_arquivo))
    {
        printf("Erro: Arquivo não suportado, por favor inserir arquivo de extensão .pbm\n");
        return 1;
    }
    FILE *arquivo = fopen(nome_arquivo, "r");
    verificar_validade_pbm(arquivo);
    int largura, altura, espacamento_lateral;
    registrar_dimensao_pbm(arquivo, &largura, &altura);
    analisar_espacamento_lateral(arquivo, largura, &espacamento_lateral);
    printf("%d", espacamento_lateral);
    fclose(arquivo);
    return 0;
}

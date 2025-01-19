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
    char *codigo_barra = malloc((largura+1)*2*sizeof(char));
    pegar_espacamento_codigo(arquivo, largura, &espacamento_lateral, codigo_barra);
    fclose(arquivo);
    int area = (largura - (2 * espacamento_lateral))/67;
    char *verificador = criar_verificador(codigo_barra, espacamento_lateral, area);
    char *new_verificador = apenas_digitos(verificador);
    free(verificador);
    char *final = traduzir_numeros(new_verificador);
    free(new_verificador);
    printf("%s", final);
    return 0;
}

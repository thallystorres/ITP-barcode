// definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//includes comuns
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define TAMANHO_IDENTIFICADOR 8
#define TAMANHO_DIGITO 7
#define TAMANHO_CODIGO_BARRAS 67
#define TAMANHO_INICIAL_FINAL 3
#define TAMANHO_CENTRAL 5
#define TAMANHO_L_R 4
#define STRING_INICIAL_FINAL "101"
#define STRING_CENTRAL "01010"

//Funções declaradas no verificador.c
int calcula_digito_verificador(int *verificador);
int validar_digito_verificador(int *verificador);
int* tratar_identificador(const char *input);

//Funções declaradas no manipularpbm.c
char** transformar_code(int *verificador);
void printar_horizontal(FILE *arquivo, int espaco_lateral);
void printar_vertical(FILE *arquivo, int largura, int espaco_lateral);
char* criar_string_area(int *verificador);
void gerar_arquivo_pbm(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo);
//Funções declaradas no analisepbm.c
int arquivo_existe(const char *nome_arquivo);
int tem_extensao_pbm(const char *nome_arquivo);
void erro_encontrado(FILE *arquivo);
void verificar_validade_pbm(FILE *arquivo);
void extrair_dimensao_pbm(FILE *arquivo, int *largura, int *altura);
void extrair_espacamento_codigo(FILE *arquivo, int largura, int *espacamento_lateral, char* codigo_barra);
//Funções declaradas no analisarcodigo.pbm
void manipular_codigo_barra(char *codigo_barra, int espacamento_lateral, int area);
int* traduzir_numeros(char *new_verificador);
//Struct definido para a tabela de r/l-code
typedef struct {
    int digit;
    char l_code[TAMANHO_DIGITO+1];
    char r_code[TAMANHO_DIGITO+1];
} DigitCode;

//Externalizando fator global
extern DigitCode codes[];

#endif // definitions.h

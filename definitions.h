// definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Funções declaradas no verificador.c
int calcula_digito_verificador(int *verificador);
int verificar_digito_verificador(int *verificador);

//Funções declaradas no pbm.c
char** transformar_code(int *verificador);
void printar_horizontal(FILE *arquivo, int espaco_lateral);
void printar_vertical(FILE *arquivo, int largura, int espaco_lateral);
char* criar_string_area(int *verificador);
void gerar_arquivo_pbm(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo);
int arquivo_existe(const char *nome_arquivo);

//Struct definido para a tabela de r/l-code
typedef struct {
    int digit;
    char l_code[8];
    char r_code[8];
} DigitCode;

//Externalizando fator global
extern DigitCode codes[];

#endif // definitions.h

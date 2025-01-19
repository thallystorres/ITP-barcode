// definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Funções declaradas no verificador.c
int calcula_digito_verificador(int *verificador);
int verificar_digito_verificador(int *verificador);

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
void registrar_dimensao_pbm(FILE *arquivo, int *largura, int *altura);
void pegar_espacamento_codigo(FILE *arquivo, int largura, int *espacamento_lateral, char* codigo_barra);
char* criar_verificador(char *codigo_barra, int espacamento_lateral, int area);
char* apenas_digitos(char *verificador);
char* traduzir_numeros(char *new_verificador);
//Struct definido para a tabela de r/l-code
typedef struct {
    int digit;
    char l_code[8];
    char r_code[8];
} DigitCode;

//Externalizando fator global
extern DigitCode codes[];

#endif // definitions.h

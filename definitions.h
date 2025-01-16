// definitions.h
#ifndef DEFINITIONS_H
#define DEFINITIONS_H

//Funções declaradas no verificador.c
int calculaDigitoVerificador(int *verificador);
int verificarDigitoVerificador(int *verificador);

//Funções declaradas no pbm.c
char** transformarCode(int *verificador);
void printarHorizontal(FILE *arquivo, int espaco_lateral);
void printarVertical(FILE *arquivo, int largura, int espaco_lateral);
char* criarStringArea(int *verificador);
void gerarArquivoPBM(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo);
int arquivoExiste(const char *nome_arquivo);

//Struct definido para a tabela de r/l-code
typedef struct {
    int digit;
    char l_code[8];
    char r_code[8];
} DigitCode;

//Externalizando fator global
extern DigitCode codes[];

#endif // definitions.h

#include "definitions.h"

//Função de verificação de existência de arquivo
int arquivo_existe(const char *nome_arquivo) {
    //Abrindo arquivo para leitura
    FILE *arquivo = fopen(nome_arquivo, "r");
    //Se arquivo existir, fecha imediatamente e retorna verdadeiro
    if (arquivo) 
    {
        fclose(arquivo);
        return 1;
    }
    return 0;
}

//Função de verificação de extensão .pbm
int tem_extensao_pbm(const char *nome_arquivo)
{
    const char *extensao = strrchr(nome_arquivo, '.'); //Localiza o último ponto no nome do arquivo
    if(extensao != NULL) //Se não retornar nada, nem extensão possui
    {
        if(strcmp(extensao, ".pbm") == 0) //Compara do ponto pra frente com a string ".pbm"
        {
            return 1; //Verdadeiro, é um .pbm
        }
    }
    return 0; //Falso, não é .pbm
}

//Função que fecha o arquivo e o programa simultâneamente para não haver corrompimento do arquivo
void erro_encontrado(FILE *arquivo)
{
    fclose(arquivo); //Fecha arquivo
    exit(1); //Fim de código
}

//Função que recebe o arquivo enviado e verifique se é válido ou não, possui diversas condicionais que buscam analisar cada problema possível
void verificar_validade_pbm(FILE *arquivo)
{
        if(arquivo == NULL) //Caso não houver arquivo
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }
    char cabecalho[4];
    if (fgets(cabecalho, sizeof(cabecalho), arquivo) == NULL)
    {
        printf("Erro ao ler cabeçalho\n"); //Caso haja erro ao ler a primeira linha do bpm, fim de código
        erro_encontrado(arquivo);
    }
    cabecalho[strcspn(cabecalho, "\n")] = '\0'; //Tratamento do cabeçalho
    if (strcmp(cabecalho, "P1") != 0) //Checa se o cabeçalho é realmente P1, cao não, fim de código
    {
        printf("Erro: Arquivo .pbm inválido");
        erro_encontrado(arquivo);
    }
}

//Função que registra em dois ponteiros a largura e altura do bpm, passadas na segunda linha
void extrair_dimensao_pbm(FILE *arquivo, int *largura, int *altura)
{
    char linha[50]; //Iniciando string que recebe a segunda linha inteira
    if (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        sscanf(linha, "%d %d", largura, altura); //Caso a linha esteja na formatação "%d %d", escaneia ints
    }
    else
    {
        printf("Erro ao ler as dimensões.\n"); //Caso contrário, fim de código
        erro_encontrado(arquivo);
    }
}

//Função que extrai o espaçamento lateral e a primeira linha do código de barras
void extrair_espacamento_codigo(FILE *arquivo, int largura, int *espacamento_lateral, char* codigo_barra)
{
    int contador = 0; //Contador que vai ser somado recursivamente a cada linha que contêm apenas 0

    //String que irá comportar toda a linha extraída do arquivo. O tamanho da string tem essa forma por contar o número de caracteres 0's e 1's da linha, os espaçamentos (que são o dobro da largura + 1) e o char nulo '\0'
    char linha[(largura + 1) * 2];

    //Enquanto houver linhas, analisa cada uma delas
    while (fgets(linha, sizeof(linha), arquivo) != NULL)
    {
        if (strchr(linha, '1')) //Verifica se há '1' na linha, caso encontre, quebra o while
        {
            break;
        }
        contador++; //+1 ao contador a cada linha sem '1'
    }

    *espacamento_lateral = contador; //Atribui o valor de contador para o espaçamento lateral
    strcpy(codigo_barra, linha); //Copia o código de barras extraído para a string
}

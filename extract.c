#include "definitions.h"

int main(int argc, char const *argv[])
{
    //Se foi passado um número de argumentos que não satisfaz o exigido, alerta erro e fim de programa
    if(argc != 2)
    {
        printf("Uso: %s <nome_imagem.pbm>\n", argv[0]);
        return 1;
    }
    const char *nome_arquivo = argv[1]; //Atribuindo nome do arquivo a variável
    if(!arquivo_existe(nome_arquivo)) //Se arquivo não existir, fim de programa
    {
        printf("Erro: Arquivo não encontrado.\n");
        return 1;
    }
    if(!tem_extensao_pbm(nome_arquivo)) //Se arquivo existir mas não houver extensão .pbm, fim de programa
    {
        printf("Erro: Arquivo não suportado, por favor inserir arquivo de extensão .pbm\n");
        return 1;
    }
    FILE *arquivo = fopen(nome_arquivo, "r"); //Começo de leitura do arquivo
    verificar_validade_pbm(arquivo); //Verifica se há cabeçalho P1 no arquivo
    int largura, altura, espacamento_lateral;
    extrair_dimensao_pbm(arquivo, &largura, &altura); //Extraindo dimensões e atribuindo à largura e à altura
    char *codigo_barra;
    codigo_barra = malloc((largura+1)*2*sizeof(char)); //Inicializando string que comportará linha de código
    extrair_espacamento_codigo(arquivo, largura, &espacamento_lateral, codigo_barra);
    fclose(arquivo); //Fechando arquivo
    //Calculando o tamanho da área de cada digito, subtraindo o espaçamento lateral e dividindo pelo número de áreas existentes
    int area = (largura - (2 * espacamento_lateral))/TAMANHO_CODIGO_BARRAS;
    manipular_codigo_barra(codigo_barra, espacamento_lateral, area);
    int *final = traduzir_numeros(codigo_barra);
    if(final == NULL)
    {
        return 1;
    }
    printf("O identificador do código de barras é: ");
    for (int i = 0; i < 7; i++)
    {
        printf("%d", final[i]);
    }
    free(codigo_barra); //Liberando memória de alocação dinâmica
    return 0;
}

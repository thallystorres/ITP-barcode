#include "definitions.h"

//Função que recebe o verificador analisado pela função verificarDigitoVerificador() e retorna um array de strings que representa cada número em l/r-code
char** transformar_code(int *verificador)
{
    //Alocação do array que irá ser retornado
    char **final;
    final = malloc(TAMANHO_IDENTIFICADOR * sizeof(char *));
    if (final == NULL)
    {
        perror("Erro ao alocar memória");
        return NULL;
    }
    //For loop que passa por cada dígito do verificador EAN 
    for (int i = 0; i < TAMANHO_IDENTIFICADOR; i++)
    {
        //Alocação da string de índice i
        final[i] = malloc(TAMANHO_DIGITO + 1 * sizeof(char));
        //For loop aninhado que passará por todos os dígitos da tabela para verificar em qual dígito se encaixa
        for (int j = 0; j < 10; j++)
        {   
            //Se o dígito j for igual ao dígito i do verificador então a condição foi aceita
            if(codes[j].digit == verificador[i])
            {
                //Se o dígito for um dos primeiros quatro, então será um l-code
                if(i < 4)
                {
                    strcpy(final[i], codes[j].l_code);
                }
                //Se não for, então será um r-code
                else
                {
                    strcpy(final[i], codes[j].r_code);
                }
                //Caso algum for satisfeito, há um break para não haver loops desnecessários
                break;
            }
        }
    }
    //Retornando o verificador final em padrão EAN-8
    return final;
}

//Função chave para gerar o arquivo PBM em si, recebendo como parâmetro todos os argumentos de linha de comando
void gerar_arquivo_pbm(int *verificador, int espaco_lateral, int pixel_area, int altura_barra, const char *nome_arquivo)
{
    //Para imprimir no arquivo ".pbm" calculamos de forma simples a largura, que se dá pelo número de áreas (sempre será 67 em EAN-8) vezes a quantidade de pixels por área, somada aos pixels de espaço lateral multiplicados por dois por serem contados da esquerda e direita
    int largura = TAMANHO_CODIGO_BARRAS * pixel_area + 2 * espaco_lateral;
    //De mesma forma, calculamos a altura somando o argumento passado na linha de comando com o dobro dos pixels de espaço lateral, por serem contados de cima e de baixo
    int altura_total = altura_barra + 2 * espaco_lateral;
    //Criação do FILE arquivo, e abrindo para escrita, passando como parâmetro o nome do arquivo dado na linha de comando
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL) //Caso haja algum problema na criação do arquivo, retorna erro e fim de programa 
    {
        printf("Erro ao criar o arquivo.\n");
        return;
    }
    char *string_area = criar_string_area(verificador); //Utilizando a função de criar string de área
    //Imprimindo o cabeçalho P1, com informações da largura e altura calculadas
    fprintf(arquivo, "P1\n%d %d\n", largura, altura_total);
    //Imprimindo as linhas verticais iniciais
    printar_vertical(arquivo, largura, espaco_lateral);
    //Inicio do for loop que irá imprimir as linhas horizontais, utilizando como delimitador a altura das barras
    for (int i = 0; i < altura_barra; i++)
    {
        //Imprimindo o espaçamento horizontal direito
        printar_horizontal(arquivo, espaco_lateral);
        //Para cada dígito na string área
        for (int j = 0; j < TAMANHO_CODIGO_BARRAS; j++)
        {
            //Para esse dígito, irá imprimir até o número de pixels por área passado como argumento
            for (int k = 0; k < pixel_area; k++)
            {
                fprintf(arquivo, "%c ", string_area[j]);
            }
        }
        //Imprimindo o espaçamento horizontal esquerdo
        printar_horizontal(arquivo, espaco_lateral);
        //Quebrando linha
        fprintf(arquivo, "\n");
    }
    //Imprimindo as linhas verticais finais
    printar_vertical(arquivo, largura, espaco_lateral);
    //Fechando arquivo para evitar erros de subscrição
    fclose(arquivo);
    //Liberando a memória da string_area utilizada
    free(string_area);
}

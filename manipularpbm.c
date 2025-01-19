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

//Função utilizada para imprimir os espaçamentos horizontais do arquivo pbm, recebe o endereço do arquivo e o espaçamento que deverá ser feito
void printar_horizontal(FILE *arquivo, int espaco_lateral)
{
    //For loop que conta quantos caracteres precisará imprimir
    for (int i = 0; i < espaco_lateral; i++)
    {
        //Por ser apenas pixels brancos, então será impresso o 0
        fprintf(arquivo, "0 ");
    }
    
}

//De forma análoga, imprime o espaçamento vertical do arquivo pbm, recebe o endereço do arquivo, o espaçamento que deverá ser feito e a largura horizontal do arquivo
void printar_vertical(FILE *arquivo, int largura, int espaco_lateral)
{
    //For loop que irá passar por todos os espaços laterais exigidos
    for (int j = 0; j < espaco_lateral; j++)
    {
        //For loop que irá imprimir pixels brancos por toda a largura do arquivo
        for (int i = 0; i < largura; i++)
        {
            fprintf(arquivo, "0 ");
        }
        //Quebra de linha para prosseguir para a próxima linha
        fprintf(arquivo, "\n");
    }
    
}

//Função que retornará a string que define a área de barras, recebendo como parâmetro o verificador EAN
char* criar_string_area(int *verificador)
{
    //Codifica o verificador para EAN-8
    char **codigo = transformar_code(verificador);
    //Alocação dinâmica da string que será retornada na função. A string terá 67 dígitos, já que é o total de áreas em um código de barras.
    char *string_area;
    string_area = malloc((TAMANHO_CODIGO_BARRAS+1) * sizeof(char));
    //Todos os dígitos da string serão inicializados com \0 para garantir que não haja vazamento
    memset(string_area, '\0', TAMANHO_CODIGO_BARRAS+1);
    //Por definição dos códigos de barra, os três primeiros e últimos dígitos são sempre "101" e os cinco dígitos centrais sempre seão "01010"
    
    memcpy(string_area, STRING_INICIAL_FINAL, TAMANHO_INICIAL_FINAL);
    string_area[TAMANHO_INICIAL_FINAL] = '\0';  // Garantir o '\0' após a cópia
    
    memcpy(string_area + TAMANHO_INICIAL_FINAL + (TAMANHO_DIGITO * TAMANHO_L_R), STRING_CENTRAL, TAMANHO_CENTRAL);
    string_area[TAMANHO_INICIAL_FINAL + (TAMANHO_DIGITO * TAMANHO_L_R) + TAMANHO_CENTRAL] = '\0';  // Garantir o '\0' após a cópia
    
    memcpy(string_area + TAMANHO_CODIGO_BARRAS - TAMANHO_INICIAL_FINAL, STRING_INICIAL_FINAL, TAMANHO_INICIAL_FINAL);
    string_area[TAMANHO_CODIGO_BARRAS - TAMANHO_INICIAL_FINAL + TAMANHO_INICIAL_FINAL] = '\0';  // Garantir o '\0' após a cópia
    
    int index = TAMANHO_INICIAL_FINAL; //Começar após os 3 primeiros caracteres
    //For loop que irá analisar cada item do vetor de strings codificadas
    for (int i = 0; i < TAMANHO_IDENTIFICADOR; i++) {
        //For loop que irá analisar cada dígito dos itens do vetor de strings codificadas
        for (int j = 0; j < TAMANHO_DIGITO; j++) {
            if (index >= TAMANHO_INICIAL_FINAL + (TAMANHO_DIGITO*TAMANHO_L_R) && index < TAMANHO_INICIAL_FINAL + (TAMANHO_DIGITO*TAMANHO_L_R) + TAMANHO_CENTRAL) 
            {
                index = TAMANHO_INICIAL_FINAL + (TAMANHO_DIGITO*TAMANHO_L_R) + TAMANHO_CENTRAL; //Pular os caracteres reservados para "01010"
            }
            if (index >= TAMANHO_CODIGO_BARRAS - TAMANHO_INICIAL_FINAL) 
            {
                break; //Não ultrapassar o limite da string
            }
            //Aloca o caracter na nova string e adiciona um ao index
            string_area[index++] = codigo[i][j];
        }
    }
    return string_area;
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

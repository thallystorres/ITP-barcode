#include "definitions.h"


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


//Função que filtra a string codigo_barra para facilitar a leitura e tradução para EAN-8
void manipular_codigo_barra(char *codigo_barra, int espacamento_lateral, int area)
{
    //Etapa 1: criando verificador sem o espaçamento lateral e espaços entre caracteres
    char *verificador;
    verificador = malloc((TAMANHO_CODIGO_BARRAS + 1) * sizeof(char));
    verificador[TAMANHO_CODIGO_BARRAS] = '\0';
    
    for (int i = 0; i < TAMANHO_CODIGO_BARRAS; i++) 
    {
        verificador[i] = codigo_barra[i * area * 2 + (espacamento_lateral * 2)];
    }

    //Etapa 2: Filtrar apenas os dígitos L e R, sem contar os iniciais e finais '101' e centrais '01010'
    char *new_verificador;
    int tamanho_new_verificador = TAMANHO_CODIGO_BARRAS - TAMANHO_CENTRAL - (TAMANHO_INICIAL_FINAL * 2) + 1;
    new_verificador = malloc(tamanho_new_verificador * sizeof(char));
    new_verificador[tamanho_new_verificador] = '\0';
    
    int contador = 0;
    for (int i = 0; i < TAMANHO_CODIGO_BARRAS; i++) 
    {
        // Filtrando a parte central, inicial e final
        if ((i >= TAMANHO_INICIAL_FINAL && i < (TAMANHO_L_R * TAMANHO_DIGITO) + TAMANHO_INICIAL_FINAL) || 
            (i >= (TAMANHO_L_R * TAMANHO_DIGITO) + TAMANHO_INICIAL_FINAL + TAMANHO_CENTRAL && 
            i < TAMANHO_CODIGO_BARRAS - TAMANHO_INICIAL_FINAL))
        {
            new_verificador[contador] = verificador[i];
            contador++;
        }
    }

    //Atualiza o código de barras com a versão filtrada
    strcpy(codigo_barra, new_verificador);

    //Libera a memória alocada
    free(verificador);
    free(new_verificador);
}

//Função que traduz o código de barras extraído para o formato EAN-8
int* traduzir_numeros(char *new_verificador)
{
    char *final; //String final que irá ser retornada como código EAN-8
    final = malloc(TAMANHO_IDENTIFICADOR + 1 * sizeof(char));
    final[TAMANHO_IDENTIFICADOR] = '\0';
    //Para cada zona de 7 dígitos, verifica se é L/R-code e compara com cada número da tabela
    for (int i = 0; i <= 50; i += TAMANHO_DIGITO)
    {
        char substring[TAMANHO_DIGITO+1]; //Substring auxiliar que comporta 7 dígitos usada para comparação
        strncpy(substring, &new_verificador[i], TAMANHO_DIGITO);
        substring[TAMANHO_DIGITO] = '\0';
        for (int j = 0; j < 10; j++)
        {
            if (i < TAMANHO_DIGITO * TAMANHO_L_R) //Se for da posição 4 pra baixo, então L-code
            {
                if(strcmp(substring, codes[j].l_code) == 0) //Comparando strings
                {
                    final[i/TAMANHO_DIGITO] = '0' + j; //Atribuindo char
                    break;
                }
            }
            else //Se for da posição 5 pra cima, então é R-code
            {
                if(strcmp(substring, codes[j].r_code) == 0) //Comparando strings
                {
                    final[i/TAMANHO_DIGITO] = '0' + j; //Atribuindo char
                    break;
                }
            }
        }
    }
    return tratar_identificador(final);
}

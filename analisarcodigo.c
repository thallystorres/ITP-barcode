#include "definitions.h"

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

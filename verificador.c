#include <stdio.h>

// Função para calcular o dígito verificador
int calcularDigitoVerificador(int ean[7]) {
    int soma = 0;
    
    // Calcula a soma dos dígitos com os pesos
    for (int i = 0; i < 7; i++) {
        if (i % 2 == 0) {
            soma += ean[i] * 3;  // Multiplica os dígitos nas posições ímpares por 3
        } else {
            soma += ean[i];      // Multiplica os dígitos nas posições pares por 1
        }
    }
    
    // Calcula o dígito verificador
    int digitoVerificador = (10 - (soma % 10)) % 10;
    
    return digitoVerificador;
}

int main() {
    int ean[7] = {1, 2, 3, 4, 5, 6, 7};  // Digitos iniciais do EAN-8 (7 primeiros números)
    
    // Calcular o dígito verificador
    int digitoVerificador = calcularDigitoVerificador(ean);
    
    // Imprimir o código EAN-8
    printf("EAN-8 gerado: ");
    for (int i = 0; i < 7; i++) {
        printf("%d", ean[i]);
    }
    printf("%d\n", digitoVerificador);  // Adiciona o dígito verificador
    
    return 0;
}

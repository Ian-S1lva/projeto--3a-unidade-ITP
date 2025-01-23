#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h> 

#include "padrao.h"



//codificações p os dígitos em L-code e R-code
const char *L_CODE[] = {"0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011"};
const char *R_CODE[] = {"1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100"};

//brunno

//verificar se o identificador fornecido é válido
bool verificar_identificadorA(const char *identificador) {
    if (strlen(identificador) != 8) return false; 
    for (int i = 0; i < 8; i++) {
        if (!isdigit(identificador[i])) return false; 
    }

    // Cálculo do dígito verificador (o último dígito do identificador)
    int soma = 0;
    for (int i = 0; i < 7; i++) { 
        int peso = (i % 2 == 0) ? 3 : 1; 
        soma += (identificador[i] - '0') * peso;
    }
    int proximo_multiplo = (soma + 9) / 10 * 10; 
    int digito_verificador_calculado = proximo_multiplo - soma; 
    int digito_verificador_fornecido = identificador[7] - '0'; 

    return digito_verificador_calculado == digito_verificador_fornecido;
}

//função para gerar o código de barra
void gerar_codigo_barras(const char *identificador, int espaco_lateral, int pixels_area, int altura, const char *nome_arquivo) {
    char codigo[1000] = "101"; 

    // Adiciona os 4 primeiros dígitos usando L-code
    for (int i = 0; i < 4; i++) {
        strcat(codigo, L_CODE[identificador[i] - '0']); //Converte o dígito para seu equivalente em lcode
    }

    strcat(codigo, "01010");

    //mesmo coisa pra p Rcode
    for (int i = 4; i < 8; i++) {
        strcat(codigo, R_CODE[identificador[i] - '0']);//faz a msm coisa só q pra rcode
    }

    strcat(codigo, "101"); //Adiciona o marcador final "101"

    int largura = espaco_lateral * 2 + pixels_area * strlen(codigo); //largura total da imagem

    // Criação do arquivo PBM
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (!arquivo) { 
        fprintf(stderr, "Erro ao criar o arquivo PBM.\n");
        exit(1);
    }

    fprintf(arquivo, "P1\n%d %d\n", largura, altura);

    //Gera cada linha da imagem
    for (int y = 0; y < altura; y++) {
        //pixels do espaçamento lateral esquerdo
        for (int x = 0; x < espaco_lateral; x++) {
            fprintf(arquivo, "0 ");
        }
        //pixels correspondentes ao código de barras
        for (int i = 0; i < strlen(codigo); i++) {
            char cor = codigo[i]; 
            for (int p = 0; p < pixels_area; p++) { 
                fprintf(arquivo, "%c ", cor);
            }
        }
        //adiciona os pixels do espaçamento lateral direito
        for (int x = 0; x < espaco_lateral; x++) {
            fprintf(arquivo, "0 ");
        }
        fprintf(arquivo, "\n"); 
    }

    fclose(arquivo);
}

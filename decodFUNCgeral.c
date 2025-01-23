#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define MSG_ERRO "codigo nao encontrado\n"
#include "padrao.h"

//codificações p os dígitos em L-code e R-code
const int L_CODE[10][7] = {{0,0,0,1,1,0,1}, {0,0,1,1,0,0,1}, {0,0,1,0,0,1,1}, {0,1,1,1,1,0,1}, {0,1,0,0,0,1,1}, {0,1,1,0,0,0,1}, {0,1,0,1,1,1,1}, {0,1,1,1,0,1,1}, {0,1,1,0,1,1,1}, {0,0,0,1,0,1,1}};
const int R_CODE[10][7] = {{1,1,1,0,0,1,0},{1,1,0,0,1,1,0},{1,1,0,1,1,0,0},{1,0,0,0,0,1,0},{1,0,1,1,1,0,0},{1,0,0,1,1,1,0},{1,0,1,0,0,0,0},{1,0,0,0,1,0,0},{1,0,0,1,0,0,0},{1,1,1,0,1,0,0}};

// Função para ler o arquivo PBM
int lerImagemPBM(const char* nome_arquivo, ImagemPBM* imagem) {
    FILE* arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) {
        perror("Arquivo invalido.\n");
        return 0;
    }

    char formato[3];
    fscanf(arquivo, "%s", formato);
    if (strcmp(formato, "P1") != 0) {
        fprintf(stderr, "Arquivo invalido.\n");
        fclose(arquivo);
        return 0;
    }
   
    // Lê a largura e altura da imagem
   fscanf(arquivo, "%d %d", &imagem->largura, &imagem->altura);

    // Lê os pixels da imagem
    for (int i = 0; i < imagem->altura; i++) {
        for (int j = 0; j < imagem->largura; j++) {
            fscanf(arquivo, "%d", &imagem->pixels[i][j]);
        }
    }

    fclose(arquivo);
    return 1;
}


//
int obterUnidade(ImagemPBM* imagem){
int un = 1;
int larg = imagem->largura;
int posicao;
int i;
int padrao = 0;


if(imagem->pixels[0][larg/2]==0 &&
    imagem->pixels[0][larg/2+1]==0 &&
        imagem->pixels[0][larg/2+2]==1){
    //verifica padrao,
    return PIXELS_POR_AREA;
}
else if(larg%2 == 0){
    //calcula unidade para o caso PAR
    posicao = larg/2;
    un = 0;
    i = posicao;
    while(imagem->pixels[0][i]==0){
        i++;
        un++;           
    }
    un= un*2;

}
else{
    //calcula unidade para o caso IMPAR
    posicao = larg -(larg - 1)/2;
        un = 1;
    i = posicao;
    while(imagem->pixels[0][i]==0){
        i++;
        un++;           
    }
    un= un*2-1; 
}
    return un;
}

//
int inicioCodigo(ImagemPBM* imagem, int unidade) {
    for (int x = 0; x < imagem->largura - 3 * unidade; x++) {
        if (imagem->pixels[0][x] == 1 && 
            imagem->pixels[0][x + unidade] == 0 && 
            imagem->pixels[0][x + 2 * unidade] == 1) {
            return x; 
        }
    }
    return -1;
}

int meioCodigo(ImagemPBM* imagem, int unidade) {
    for (int x = 0; x < imagem->largura - 3 * unidade; x++) {
        if (imagem->pixels[0][x] == 0 && 
            imagem->pixels[0][x + unidade] == 1 && 
            imagem->pixels[0][x + 2 * unidade] == 0 &&
            imagem->pixels[0][x + 3*unidade] == 1 && 
            imagem->pixels[0][x + 4 *unidade] == 0) {
            return x; 
        }
    }
    return -1;
}

//
int fimCodigo(ImagemPBM* imagem, int inicio, int unidade) {
    for (int x = inicio + 3 * unidade; x < imagem->largura - 3 * unidade; x++) {
        if (imagem->pixels[0][x] == 1 && 
            imagem->pixels[0][x + unidade] == 0 && 
            imagem->pixels[0][x + 2 * unidade] == 1) {
            return x + 3 * unidade; 
        }
    }
    return -1; 
}

int RdecodificarBarras(int pos, int* barras) {

    int OK = 1;
    int m = 0;
    int n = 0;
    for(n=0; n<10; n++){
        OK = 1;
        for(m=0;m<7; m++){
            if(R_CODE[n][m] != barras[m+pos]){
                OK = 0;
            }
        }
        if(OK == 1){
            return n;
        }
    }

    return -1; // Código inválido ou não reconhecido
}

int LdecodificarBarras(int pos, int* barras) {

    int OK = 1;
    int m = 0;
    int n = 0;
    for(n=0; n<10; n++){
        OK = 1;
        for(m=0;m<7; m++){
            if(L_CODE[n][m] != barras[m+pos]){
                OK = 0;
            }
        }
        if(OK == 1){
            return n;
        }
    }

    
    return -1; // Código inválido ou não reconhecido
}

bool verificar_identificadorB(int* codigo) {

    // Cálculo do dígito verificador
    int soma = 0;
    for (int i = 0; i < 7; i++) { 
        int peso = (i % 2 == 0) ? 3 : 1; 
        soma += codigo[i] * peso;
    }
    int proximo_multiplo = (soma + 9) / 10 * 10; 
    int digito_verificador_calculado = proximo_multiplo - soma; 
    int digito_verificador_fornecido = codigo[7]; 

    return digito_verificador_calculado == digito_verificador_fornecido;
}

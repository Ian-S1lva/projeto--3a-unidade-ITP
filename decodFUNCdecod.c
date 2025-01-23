#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#define MSG_ERRO "codigo nao encontrado\n"
#include "padrao.h"
#include "interface.h"


//identificar o código de barras EAN-8
int extrairCodigoDeBarras(int unidade, ImagemPBM* imagem) {

    int barras[(imagem->largura)/unidade];  
    int indice = 0;
    for (int j = 0; j < imagem->largura; j=j+unidade) {
        if (imagem->pixels[0][j] == 1) { // Barra preta
            barras[indice++] = 1;
        } else { // Espaço branco
            barras[indice++] = 0;
        }
    }
    
    // decodificar as barras 

int codigo[8];
int pos = 0;
int tam = 7;

pos = inicioCodigo(imagem, unidade);
if(pos == -1){
    printf(MSG_ERRO);
    return -1;
}
if(fimCodigo(imagem,pos, unidade) == -1){
    printf(MSG_ERRO);
    return -1;}

    pos = pos/unidade +3;


codigo[0] = LdecodificarBarras(pos,barras);
codigo[1] = LdecodificarBarras(pos+tam,barras);
codigo[2] = LdecodificarBarras(pos+2*tam,barras);
codigo[3] = LdecodificarBarras(pos+3*tam,barras);

if(meioCodigo(imagem, unidade) == -1){
    printf(MSG_ERRO);
    return -1;}
    pos = pos + 5;

codigo[4] = RdecodificarBarras(pos+4*tam,barras);
codigo[5] = RdecodificarBarras(pos+5*tam,barras);
codigo[6] = RdecodificarBarras(pos+6*tam,barras);
codigo[7] = RdecodificarBarras(pos+7*tam,barras);



for(indice=0;indice<8;indice++){
    if(codigo[indice]==-1){
        printf(MSG_ERRO);
    return -1;
    }

if(verificar_identificadorB(codigo) == 0){
    printf(MSG_ERRO);
    return -1;}

for(indice=0;indice<8;indice++){
    printf("%d", codigo[indice]);
    }
    printf("\n");
return 0;
}





}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 
    
#include "padrao.h"
#include "interface.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nome do arquivo>\n", argv[0]);
        return 1;
    }
  ImagemPBM imagem;   

    if (lerImagemPBM(argv[1], &imagem)) {
        extrairCodigoDeBarras(obterUnidade(&imagem),&imagem);
    }

    return 0;
}

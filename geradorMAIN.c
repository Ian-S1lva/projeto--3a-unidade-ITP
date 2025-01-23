#include <stdio.h>  
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include <ctype.h> 

#include "padrao.h"
#include "interface.h"


int main(int argc, char *argv[]) {
    //verifica se o identificador foi fornecido
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <identificador> [espacamento] [pixels_por_area] [altura] [nome_arquivo]\n", argv[0]);
        return 1;
    }

    const char *identificador = argv[1]; // Identificador fornecido pelo usuário
    int espaco_lateral = (argc > 2) ? atoi(argv[2]) : ESPACAMENTO_PADRAO;
    int pixels_area = (argc > 3) ? atoi(argv[3]) : PIXELS_POR_AREA;
    int altura = (argc > 4) ? atoi(argv[4]) : ALTURA_PADRAO; 
    const char *nome_arquivo = (argc > 5) ? argv[5] : NOME_PADRAO; 

    // Verifica se o identificador é válido
    if (!verificar_identificadorA(identificador)) {
        fprintf(stderr, "Identificador inválido. Certifique-se de que possui 8 dígitos numéricos válidos.\n");
        return 1;
    }

    //Verifica se o arquivo já existe e pergunta se o usuário deseja sobrescrever
    FILE *teste_arquivo = fopen(nome_arquivo, "r");
    if (teste_arquivo) {
        fclose(teste_arquivo);
        char resposta;
        printf("O arquivo '%s' já existe. Deseja sobrescrevê-lo? (s/n): ", nome_arquivo);
        scanf(" %c", &resposta);
        if (resposta != 's' && resposta != 'S') { 
            fprintf(stderr, "Arquivo resultante já existe.\n");
            return 1;
        }
    }

    gerar_codigo_barras(identificador, espaco_lateral, pixels_area, altura, nome_arquivo);
    printf("Imagem PBM com o código de barras gerada em '%s'.\n", nome_arquivo);

    return 0;
}

//ian
#define PIXELS_POR_AREA 2      // Largura padrão de cada barra em pixels
#define ALTURA_PADRAO 50       // Altura padrão do código de barras
#define ESPACAMENTO_PADRAO 10  // Espaçamento lateral padrão
#define NOME_PADRAO "codigo_barras.pbm" 

#define MAX_LINHAS 1000
#define MAX_COLUNAS 1000

typedef struct {
    int largura;
    int altura;
    int pixels[MAX_LINHAS][MAX_COLUNAS];
} ImagemPBM;

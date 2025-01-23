

//INTERFACE


// Função para ler o arquivo PBM
// nome do arquivo, ImagemPBM (struct) -> Lê imagem
int lerImagemPBM(const char* , ImagemPBM* );



//calcula a unidade
//ImagemPBM -> medida da unidade
int obterUnidade(ImagemPBM* );

//encontra o inicio do codigo,"101"
//ImagemPBM, unidade -> posicao ou erro
int inicioCodigo(ImagemPBM* , int );

//encontra o meio do codigo, "10101" 
//ImagemPBM, unidade -> posicao ou erro
int meioCodigo(ImagemPBM* imagem, int );

//encontra o fim do codigo,"101"
//ImagemPBM, unidade -> posicao ou erro
int fimCodigo(ImagemPBM* , int , int );

//decodifica 01 trecho em R_CODE
//posicao, barras -> valor numerico de 01 barra
int RdecodificarBarras(int pos, int* );

//decodifica 01 trecho em L_CODE
//posicao, barras -> valor numerico de 01 barra
int LdecodificarBarras(int pos, int* );

//calcula o digito verificador
//codigo -> valido ou invalido
bool verificar_identificadorB(int* );


//identificar o código de barras EAN-8
//unidade, ImagemPBM -> ... funcoes ... -> exibe o codigo
int extrairCodigoDeBarras(int , ImagemPBM* );






//brunno

//verificar se o identificador fornecido é válido
//identificador ->  válido ou inválido
bool verificar_identificadorA(const char *);

//função para gerar o código de barra
//identificador, espaço_lateral, pixels_area, altura, nome_arquivo -> cria codigo
void gerar_codigo_barras(const char *, int , int , int , const char *);
USE PARA COMPILAR OS ARQUIVOS:
gcc geradorMAIN.c geradorFUNCOES.c -o gerador -g -W
gcc decodMAIN.c decodFUNCgeral.c decodFUNCdecod.c -o decod -g -W

EXEMPLOS  DE COMANDO DO GERADOR:
1)
  ./gerador
retorna erro

2)
./gerador 40170725
retorna saida pradrão

3)
./gerador 11111115 10 5 25 teste
retorna saída especificada


EXEMPLOS  DE COMANDO DO DECODIFICADOR:
1)
./decod
retorna erro

2)
./decod codigo_barras.pbm
./decod teste
retorna o codigo verificador
obs.: codigo_barras.pbm, teste são o nome dos arquivos

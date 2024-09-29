
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// int argc,char*argv[] - argc=quantos parametros estao sendo recebidos, argv
// guarda o que foi recebido parametros delimitados por espa�o
//  sem nada = quant � 1 , e a primeira posi�o de argv � o nome do arquivo

typedef struct{
    unsigned char r, g, b;
} pixel;

int main(int argC,char*argV[]) { // vai pedir parametros e vamos checar se e um mes valido
    char id[3];
    char arq[300];
    char carac[]="@MBNEOR#8Q&mÃGXZA5ñk2S%3Fz¢yYCJf1t7Lc?r(/!+-*;,.'´ ";
    unsigned char r, g, b,atual;
    int i, j, linhas, colunas,maximo,caracter;
    pixel **p; // p um ponteiro para ponteiro de inteiro
    char *novo_arquivo_nome;
    FILE *fp;  // ponteiro para arquivo

    if(argC==1){
    printf("Houve um erro na passagem de parametros !\n Voce pode ter cometido o seguinte erro : ter passado menos parametros que o necessario");
    }
	// o nome do arquivo sera obtido mediante linha de comando

	strcpy(arq,argV[1]);  // nome do arquivo com caminho relativo (imagem esta no memsmo diretorio do programa)

    fp = fopen(arq, "rb"); // abrir arquivo para r - Read no modo b - Binario
    if (fp == NULL) {  // retorna NULL se deu algum problema na abertura
        printf("Erro na abertura do arquivo <%s>", arq);
        exit(EXIT_FAILURE);  // sai com código de falha
    }

	// lendo as informacoes iniciais do arquivo ppm
    fscanf (fp, "%s", id); // identificador do formato PPM - P6
    fscanf (fp, "%d", &colunas); // largura da imagem = total de colunas
    fscanf (fp, "%d", &linhas); // altura da imagem = total de linhas
    fscanf (fp, "%d", &maximo); // maximo de intensidade
    fscanf (fp, "%c", &r); // consumir um quebra de linha no arquivo
    printf("\nTipo do arquivo <%s>: %s\n", arq, id);
    printf("\nMaximo: %d\n", maximo);
    printf("\nImagem tem %d x %d pixels\n", linhas, colunas);
    novo_arquivo_nome = strtok(arq, ".");
    printf("\nO nome do arquivo txt será : %s.txt",novo_arquivo_nome);
    strcat (novo_arquivo_nome,".txt");
    // ****** precisa criar uma matriz dinamica com linhas x colunas do tipo pixel
    p = (pixel **)malloc(linhas * sizeof(pixel *));
    for (i = 0; i < linhas; i++) {
        p[i] = (pixel *)calloc(colunas, sizeof(pixel));
    }//p agora é a matriz com os valores
    printf("\nAlocado\n");
    	// **** no for duplo abaixo, ler o r g b para os campos da matriz de struct
    for (i=0; i<linhas; i++) {
        for (j=0; j<colunas; j++) {
            fscanf (fp, "%c%c%c", &r, &g, &b);
            p[i][j].r=r;
            p[i][j].g=g;
            p[i][j].b=b;
        }
    }
    printf("\nLidos\n");
    fclose(fp);

    fp = fopen(novo_arquivo_nome, "w");
    for (i=0; i<linhas; i++) {
        for (j=0; j<colunas; j++) {
        //muda pra cinza
        atual=((p[i][j].r*0.30)+(p[i][j].g*0.59)+(p[i][j].b*0.11));
        //atual=(p[i][j].r+p[i][j].g+p[i][j].b)/3;
        //ve qual caractere
        caracter=((int)atual/5)-1;
        //printa tela
        printf("%c",carac[caracter]);
        //coloca no arquivo
        fwrite(&carac[caracter], 1, 1, fp);

        }
        //pula linha tela
        //pula linha arquivo
        printf("\n");
        //coloca no arquivo
        fwrite("\n", 1, strlen("\n"), fp);
    }
    for (i=0; i<linhas; i++){
        free(p[i]);
    }
    free (p); // depois as linhas
    fclose(fp);
  return 0;
}

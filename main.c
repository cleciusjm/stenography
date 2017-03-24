#include <stdlib.h>
#include <stdio.h>
#include "stenography.h"
#define MAX_NAME 256 /* tamanho maximo para nome de arquivo */
#define MAX 1020 /* tamanho maximo para as matrizes e, consequentemente, para a figura, em pixels)*/
/**
 * Lê um arquivo P3 como uma string
 */
int *readP3File(char* path);
/**
 * Escreve o conteudo em um arquivo P3
 */
void writeP3File(char* path, char* content);

int main() {
	char *inFile = "img/imagem2.ppm";
	char *message = "teste";

	writeStegTo(inFile, message);

	printf("Write process complete.\n");

	char *outFile = "out.ppm";
	char *decodedMessage = readStegFrom_v2(outFile);

	printf("Read process complete.\n");
//	printf("(%s)", decodedMessage);




//	const outFile = "teste_out.bmp";
//	int *phrase = "Teste 123";
//	int *content = readP3File(inFile);
//	char *processedContent = writeStegTo(content, phrase);
//	writeP3File(outFile, processedContent);
//	puts("Mensagem escrita com sucesso");

	return 0;
}

int *readP3File(char* path) {
	FILE *arq1;
	char key[128];
	int r, g, b;

	arq1 = fopen(path, "r");
	if (arq1 == NULL) {
		printf("Erro na abertura do arquivo %s\n", path);
		return 0;
	}

	fscanf(arq1, "%s", key);
	if (strcmp(key, "P3") != 0) {
		printf("Arquivo nao e um PPM\n");
		fclose(arq1);
		return 0;
	}

	int max, w, h;
	fscanf(arq1, "%d %d %d", &w, &h, &max);

	int size = h * w;
	static int *retorno;

	retorno = malloc(size * sizeof(int));

	int pos = 0;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {

			fscanf(arq1, " %d %d %d ", &r, &g, &b); /* para analise de caracteres trocar printf pela funcao que ira analisar a mensagem*/
//
//			printf("V1 %d %d %d \n ", r, g, b);

			*(retorno + pos++) = r;
			*(retorno + pos++) = g;
			*(retorno + pos++) = b;

			int v1 = *(retorno + pos - 3);
			int v2 = *(retorno + pos - 2);
			int v3 = *(retorno + pos - 1);

//			printf("V2 %d %d %d \n ", v1, v2, v3);
		}
	}
	printf("Finalizou leitura");

	fclose(arq1);

	return retorno;
}

void writeP3File(char* path, char* content) {
    FILE *fp;
    //Abrir arquivo
    fp = fopen(path, "wb");
    if (!fp) {
         fprintf(stderr, "Não é possível abrir o arquivo '%s'\n", path);
         exit(1);
    }

    fprintf(stderr, "Arquivo aberto '%s'\n", path);

    //Escreve o header
//    fprintf(fp, "P3\n");
//    fprintf(fp, "%d %d\n",img->w,img->h);
//    fprintf(fp, "%d\n",img->max);
//    fwrite(img->data, 3 * img->w, img->h, fp);
    fclose(fp);
}

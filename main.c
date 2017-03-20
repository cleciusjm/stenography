#include <stdlib.h>
#include <stdio.h>
#include "stenography.h"
/**
 * Lê um arquivo P3 como uma string
 */
P3Image *readP3File(char* path);
/**
 * Escreve o conteudo em um arquivo P3
 */
void writeP3File(char* path, P3Image* content);

int main() {
	const char *inFile = "teste.bmp";
	const char *outFile = "teste_out.bmp";
	char *phrase = "Teste 123";
	P3Image *content = readP3File(inFile);
	writeStegTo(content, phrase);
	writeP3File(outFile, content);
	puts("Mensagem escrita com sucesso");
	return 0;
}

P3Image *readP3File(char *path) {
	P3Image *image = malloc(sizeof(P3Image));
	FILE *arq1;
	char key[128];
	int i, j;

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

	fscanf(arq1, "%d %d", &image->w, &image->h);
	fscanf(arq1, "%d", &image->max);

	int size = image->h * image->w;

	image->data = malloc(sizeof(unsigned int) * size);
	int tmp;
	for (i = 0; i <= size - 1; i++) {
		fscanf(arq1, "%d", &tmp); /* para analise de caracteres trocar printf pela funcao que ira analisar a mensagem*/
		image->data[i] = tmp;
	}
	fclose(arq1);

	return image;
}

void writeP3File(char *path, P3Image *content) {
	for (int i = 0; i < content->w * content->h; i++) {
		printf("%d \n", content->data[i]);
	}
}

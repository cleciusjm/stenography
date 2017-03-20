#include <stdlib.h>
#include <stdio.h>
#include "stenography.h"
#define MAX_NAME 256 /* tamanho maximo para nome de arquivo */
#define MAX 1020 /* tamanho maximo para as matrizes e, consequentemente, para a figura, em pixels)*/
/**
 * Lê um arquivo P3 como uma string
 */
char *readP3File(char* path);
/**
 * Escreve o conteudo em um arquivo P3
 */
void writeP3File(char* path, char* content);

int main() {
	const inFile = "teste.bmp";
	const outFile = "teste_out.bmp";
	char *phrase = "Teste 123";
	char *content = readP3File(inFile);
	char *processedContent = writeStegTo(content, phrase);
	writeP3File(outFile, processedContent);
	puts("Mensagem escrita com sucesso");

	return 0;
}

char *readP3File(char* path) {
	FILE *arq1;
	char key[128];
	int i, j, n, m, max;
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

	fscanf(arq1, "%d %d %d", &m, &n, &max);
	for (i = 0; i <= n - 1; i++)
		for (j = 0; j <= m - 1; j++) {

			fscanf(arq1, " %d %d %d ", &r, &g, &b); /* para analise de caracteres trocar printf pela funcao que ira analisar a mensagem*/

			printf(" %d %c %d \n ", r, g, b);

		}
	fclose(arq1);

	return 0;
}

void writeP3File(char* path, char* content) {

}

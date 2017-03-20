#include <stdio.h>
#include "stenography.h"
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

}
void writeP3File(char* path, char* content) {

}

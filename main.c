#include <stdlib.h>
#include <stdio.h>
#include "stenography.h"

int main() {
	char *inFile = "img/imagem2.ppm";
	char *message = "o segredo foi revelado";

	writeStegTo(inFile, message);

	printf("Write process complete.\n");

	char *outFile = "out.ppm";
	char *decodedMessage = readStegFrom_v2(outFile);

	printf("Read process complete.\n");
//	printf("(%s)", decodedMessage);

	return 1;
}


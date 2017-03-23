#include "stenography.h"
#include "imageHelper.h"

#include <stdio.h>
#include <stdlib.h>

void finishWritingImage(FILE *original, FILE *created);

void putCharBits(int binOfC[], FILE *original, FILE *created);

int getMessageLength(char my_msg[]);

char *readStegFrom(FILE *fp) {
	return 0;
}

int writeStegTo(char *filePath, char *message) {

	FILE *originalImage;
	if((originalImage = fopen(filePath, "r+")) == NULL) {
		printf("Could not open image %s.\nAborting\n", filePath);
	    return 0;
	}

	if(isImgOfP3Type(originalImage)){
		printf("Image is not a P3.\nAborting\n", filePath);
		return 0;
	}

	int imgWidth = getImgWidth(originalImage);
	int imgHeight = getImgHeight(originalImage);
	int imgLines = countImgLines(originalImage);

	FILE *createdImage = fopen("out.ppm","w");

	copyHeader(originalImage, createdImage);

	int messageLength = sizeof(message) / sizeof(char);

	for(int i=0 ; i<messageLength ; i++){
		char c = *(message + i);

	    int binOfC[8] = {0};

	    for (int i = 7; i >= 0; i--){
	        binOfC[i] = (c & (1 << i)) ? 1 : 0;
	    }

		putCharBits(binOfC, originalImage, createdImage);
	}

	int binOfEndMessage[8] = {0,0,0,0,0,0,0,0};

	putCharBits(binOfEndMessage, originalImage, createdImage);

	finishWritingImage(originalImage, createdImage);

	printf("Write process complete.\n");

  	fclose(originalImage);
  	fclose(createdImage);

	return 1;
}

void finishWritingImage(FILE *original, FILE *created){
	char temp;
	while((temp = fgetc(original)) != EOF){
		fputc('\n', created);
	}
}

void putCharBits(int binOfC[], FILE *original, FILE *created){
	for(int i=0 ; i<8 ; i++){
		char temp = fgetc(original);

		while(temp == ' ' || temp == '\n'){
			fputc(temp, created);
			temp = fgetc(original);
		}

		if(temp == EOF){
			break;
		}

		printf("Leitura Temp[%c]\n", temp);

		ungetc(temp, original);

		int color;
		fscanf(original, "%d", &color);

		int bin = *(binOfC + 7 -i);

		int resultColor = (color %2 == bin) ? color : ( color == 0 ? 1 : color -1);

		fprintf(created, "%d", resultColor);
	}
}

int getMessageLength(char my_msg[]) {
  int i = 0;
  while(my_msg[i] != '\0') {
    i++;
  }
  return i * 8 + 8;
}

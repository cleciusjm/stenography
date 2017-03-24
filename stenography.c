#include "stenography.h"
#include "imageHelper.h"

#include <stdio.h>
#include <stdlib.h>

int myPow(int base,int power);

char buildCharThroughBitArray(int a[]);

int getByteArraySize(int a[]);

int isEndOfMessage(int a[]);

void finishWritingImage(FILE *original, FILE *created);

void putCharBits(int binOfC[], FILE *original, FILE *created);

int getMessageLength(char my_msg[]);

char *readStegFrom_v2(char *filePath){
	FILE *imageWithMessage;
	if((imageWithMessage = fopen(filePath, "r+")) == NULL) {
		printf("Could not open image %s.\nAborting\n", filePath);
	    return 0;
	}

	if(isImgOfP3Type(imageWithMessage)){
		printf("Image is not a P3.\nAborting\n", filePath);
		return 0;
	}

	int imgWidth = getImgWidth(imageWithMessage);
	int imgHeight = getImgHeight(imageWithMessage);

	skipImgColorDepth(imageWithMessage);
	skipImgColorDepth(imageWithMessage);

	int charBitBufferPos = 0;
	int charBitsBuffer[8];
	int messagePos = 0;
	char *message = malloc(sizeof(char) * 128);

	char temp;
	int color;
	while((temp = fgetc(imageWithMessage)) != EOF){
		if(temp == ' ' || temp == '\n'){
			continue;
		}

		ungetc(temp, imageWithMessage);

		fscanf(imageWithMessage, "%d", &color);

		charBitsBuffer[charBitBufferPos++] = color % 2;

		printf("Post %d, Color %d, Bit %d\n",charBitBufferPos,color, charBitsBuffer[charBitBufferPos -1]);

		if(charBitBufferPos > 7){

			if(isEndOfMessage(charBitsBuffer) == 1){
				break;
			}

			char c = buildCharThroughBitArray(charBitsBuffer);

			*(message + messagePos++) = c;

			printf("%c\n", c);

			charBitBufferPos = 0;
		}

	}

	return message;
}

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

  	fclose(originalImage);
  	fclose(createdImage);

	return 1;
}


int myPow(int base,int power){


	if(power == 0){
		return 1;
	}else if(power == 1){
		return 2;
	}

	int result = 2;
	for(int i= 0; i<(power -1) ; i++){
		result *= 2;
	}

	return result;
}

char buildCharThroughBitArray(int a[]){
	int result = 0;

	for(int i=0 ; i<8 ; i++){
		if(i == 7){
			result += a[7];
		}else if(a[i] == 1){
			result += myPow(2, 7 -i);
		}
	}

	printf("result %d\n", result);

	return result;
}

int getByteArraySize(int a[]){
	int size = 0;

	for(int i=0 ; i<8 ; i++){
		if(a[i] != '\0'){
			size++;
		}
	}
	return size;
}

int isEndOfMessage(int a[]){
	int result = 1;
	for(int i=0 ; i<8 ; i++){
		if(a[i] == 1){
			result = 0;
		}
	}
	return result;
}

void finishWritingImage(FILE *original, FILE *created){
	char temp;
	while((temp = fgetc(original)) != EOF){
		fputc(temp, created);
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

		ungetc(temp, original);

		int color;
		fscanf(original, "%d", &color);

		int bin = *(binOfC + 7 -i);

		int resultColor =
				(color % 2 == bin % 2) ? color : (color == 0 ? 1 : color - 1);

//		printf("Original color:%d | Bin: %d | Result color: %d\n", color, bin, resultColor);

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

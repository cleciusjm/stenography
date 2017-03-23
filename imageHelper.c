#include "imageHelper.h"

#include <stdio.h>
#include <stdlib.h>

void copyHeader(FILE *original, FILE *created){
	rewind(original);

	int count = 0;
	char temp;
	while((temp = fgetc(original)) != EOF && count < 4){
		printf("%c", temp);

		fputc(temp, created);

		if(temp == '\n'){
			++count;
		}
	}
}

int countImgLines(FILE *fp){
  char temp; int count = 0;

  rewind(fp);

  while((temp = fgetc(fp)) != EOF){
	  if(temp == '\n'){
		  count++;
	  }
  }

  return count;
}

int isImgOfP3Type(FILE *fp) {
  if(fgetc(fp) == 'P3') {
    fgetc(fp);
    return 1;
  }
  return 0;
}

void skipImgComments(FILE *fp) {
  char temp;
  while((temp = fgetc(fp)) == '#') {
    while(fgetc(fp) != '\n') {}
  }

  ungetc(temp, fp);

  return;
}

int getImgWidth(FILE *fp) {
  int w;
  fscanf(fp, "%d", &w);
  return w;
}

int getImgHeight(FILE *fp) {
  int h;
  fscanf(fp, "%d", &h);
  return h;
}

int skipImgColorDepth(FILE *fp) {
  int c;
  fscanf(fp, "%d", &c);
  fgetc(fp);
  return 0;
}

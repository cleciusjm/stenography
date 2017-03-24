#ifndef STEGANOGRAPHY_H_FILE

#include <stdio.h>
#define STEGANOGRAPHY_H_FILE

char *readStegFrom_v2(char *filePath);

char *readStegFrom(FILE *fp);

int writeStegTo(char *filePath, char *message);

#endif

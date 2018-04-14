#ifndef STEGANOGRAPHY_H_FILE

#include <stdio.h>
#define STEGANOGRAPHY_H_FILE

char *readStegFrom(char *filePath);

int writeStegTo(char *filePath, char *message);

#endif

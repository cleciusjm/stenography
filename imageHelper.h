#ifndef IMAGE_HELPER_H_FILE

#include <stdio.h>
#define IMAGE_HELPER_H_FILE

/*
 * Based on P3 File specification:
 * http://netpbm.sourceforge.net/doc/ppm.html
 */

int isImgOfP3Type(FILE *fp);

int countImgLines(FILE *fp);

void skipImgComments(FILE *fp);

int getImgWidth(FILE *fp);

int getImgHeight(FILE *fp);

int skipImgColorDepth(FILE *fp);

#endif

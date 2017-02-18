#ifndef __IMAGE_H__
#define __IMAGE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "haar.h"

#ifndef __PARAMETERS__
#define __PARAMETERS__

#define TOTAL_NODES 2913
#define TOTAL_STAGES 25
#define TOTAL_COORDINATES TOTAL_NODES*12
#define TOTAL_WEIGHTS TOTAL_NODES*3
#define IMAGE_HEIGHT 240
#define IMAGE_WIDTH 320


#endif

#ifdef __cplusplus
extern "C" {
#endif

void drawRectangle ( unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH], 
                     MyRect r);

int writePgm(char *fileName, unsigned char Data[IMAGE_HEIGHT][IMAGE_WIDTH] );

#ifdef __cplusplus
}
#endif

#endif

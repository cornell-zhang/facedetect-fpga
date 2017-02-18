#ifndef __HAAR_H__
#define __HAAR_H__

#include "ap_int.h"
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "ap_int.h"

const int ROWS = 25;
const int COLS = 25;

const int NUM_BANKS = 12;
const int SIZE = 2913;

typedef ap_uint<18> uint18_t;
typedef ap_uint<10> uint10_t;
typedef ap_uint<1>  bit;
typedef ap_uint<5> uint5_t;


#ifndef __PARAMETERS__
#define __PARAMETERS__

#define IMAGE_HEIGHT 240 
#define IMAGE_WIDTH 320
#define IMAGE_MAXGREY 255
#define IMAGE_SIZE  ( IMAGE_HEIGHT * IMAGE_WIDTH )

#define RESULT_SIZE 100

#define TOTAL_NODES 2913
#define TOTAL_STAGES 25
#define TOTAL_COORDINATES TOTAL_NODES*12
#define TOTAL_WEIGHTS TOTAL_NODES*3

#define WINDOW_SIZE 25
#define SQ_SIZE 2
#define PYRAMID_HEIGHT 12

#define OUTPUT_FILENAME "Output.pgm"
#define INPUT_IMAGE "image0_320_240.h"


#endif


typedef ap_uint<13> int_I;  
typedef ap_uint<21> int_SI;
typedef ap_uint<18> int_II;             
typedef ap_uint<26> int_SII;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct MyPoint
{
    int x;
    int y;
}
MyPoint;

typedef struct
{
    int width;
    int height;
}
MySize;

typedef struct
{
    int x; 
    int y;
    int width;
    int height;
}
MyRect;

typedef struct 
{
        int width;
        int height;
        int maxgrey;
        int flag;
}
MyInputImage;

void detectFaces( unsigned char Data[IMAGE_WIDTH], 
                  int _result_x[RESULT_SIZE], 
                  int _result_y[RESULT_SIZE], 
                  int _result_w[RESULT_SIZE], 
                  int _result_h[RESULT_SIZE], 
                  int *result_size);
		
#ifdef __cplusplus
}
#endif

#endif

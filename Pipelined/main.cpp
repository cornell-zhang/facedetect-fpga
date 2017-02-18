#include <stdio.h>
#include <ctime>
#include <stdlib.h>
#include "haar.h"
#include "image.h"

using namespace std;

int main ( int argc, char *argv[] ) 
{
 
  int flag;
  int in_flag , in_width , in_height , in_maxgrey;
  int ret_val=1;
	     
  printf ("-- entering main function --\r\n");
  printf ("-- loading image --\r\n");
         
  // 320 X 240 Input image in hex format 
  #include INPUT_IMAGE

  double duration;

  // Arguments to be passed to DUT	
  MyRect result[RESULT_SIZE];
  int result_x[RESULT_SIZE];
  int result_y[RESULT_SIZE];
  int result_w[RESULT_SIZE];
  int result_h[RESULT_SIZE];

  int res_size=0;
  int *result_size = &res_size;
  int i;

  // As the SDSoC generated data motion network does not support sending 320 X 240 images at once
  // We needed to send all the 240 rows using 240 iterations. The last invokation of detectFaces() does the actual face detection

  for ( i = 0; i < IMAGE_HEIGHT-1; i+=1 ){
      detectFaces ( Data[i], result_x, result_y, result_w, result_h, result_size);
  }

  printf ("-- detecting faces --\r\n");

  std::clock_t start = std::clock();
  detectFaces ( Data[IMAGE_HEIGHT-1], result_x, result_y, result_w, result_h, result_size);
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;

  printf("\nresult_size = %d", *result_size);

  for (int j = 0; j < RESULT_SIZE; j++){
    result[j].x = result_x[j];
    result[j].y = result_y[j];
    result[j].width = result_w[j];
    result[j].height = result_h[j];
  }

  for( int i=0 ; i < *result_size ; i++ )
    printf("\n [Test Bench (main) ] detected rects: %d %d %d %d",result[i].x,result[i].y,result[i].width,result[i].height);
 
  if ( *result_size > 0 )  ret_val = 0;
	
  printf("\n-- saving output image [Start] --\r\n"); 

  // Draw the rectangles onto the images and save the outputs.
  for(i = 0; i < *result_size ; i++ )
  {
    MyRect r = result[i];
    drawRectangle(Data, r);
  }

  flag = writePgm((char *)(OUTPUT_FILENAME),Data); 
  printf("\n-- saving output image [Done] --\r\n");
  printf("DURATION: %2f", duration);
   
  return ret_val;        

}

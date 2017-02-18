#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ctype.h>
#include <string.h>
//#include "image.h"

#define MYDEBUG

char* strrev(char* str)
{
  char *p1, *p2;
  if (!str || !*str)
    return str;
  for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
  {
    *p1 ^= *p2;
    *p2 ^= *p1;
    *p1 ^= *p2;
  }
  return str;
}



int myatoi (char* string)
{
  int sign = 1;
  int length = strlen(string);
  int i = 0;
  int number = 0;
  
  // handle sign
  if (string[0] == '-')
  {
    sign = -1;
    i++;
  }
  
  for (i; i < length; i++)
  while(i < length)
  {
    if (string[i] == '.')
      break;
    number = number * 10 + (string[i]- 48);
    i++;
  }
  
  number *= sign;
  
  return number;
}

void itochar(int x, char* szBuffer, int radix)
{
  int i = 0, n, xx;
  n = x;
  while (n > 0)
  {
    xx = n%radix;
    n = n/radix;
    szBuffer[i++] = '0' + xx;
  }
  szBuffer[i] = '\0';
  strrev(szBuffer);
}


int readPgm(char* imagefile, char* outputfile){
  
  FILE *in_file;
  FILE *out_file;
  char ch;
  int type;
  char version[3];
  char line[100];
  char mystring [20];
  char *pch;
  int i,j;
  long int position;
  int height, width, maxgrey;
  
  in_file = fopen(imagefile, "r");
  out_file = fopen(outputfile,"w");
  
  if (in_file == NULL)
  {
  	printf("ERROR: Unable to open file %s\n\n","Face.pgm");
  	return -1;
  }
  
  if (out_file == NULL)
  {
  	printf("ERROR: Unable to open file %s\n\n", "image_data.h");
  	return -1;
  }
  
  fprintf(out_file,"in_flag =1;\n");
  
  printf("\nReading image file: %s\n",imagefile);

  /* Determine image type (only pgm format is allowed)*/
  ch = fgetc(in_file);
  if(ch != 'P')
  {
  	printf("ERROR: Not valid pgm file type\n");
  	return -1;
  }
  
  ch = fgetc(in_file);
  
  /*convert the one digit integer currently represented as a character to */
  
  type = ch - 48;
  
  if(type != 5)
  {
  	printf("ERROR: only pgm raw format is allowed\n");
  	return -1;
  }
  
  while ((ch = fgetc(in_file)) != EOF && isspace(ch));
  position = ftell(in_file);
  
  // skip comments
  if (ch == '#'){
    fgets(line, sizeof(line), in_file); 
    while ((ch = fgetc(in_file)) != EOF && isspace(ch));
    position = ftell(in_file);
  }
  
  fseek(in_file, position-1, SEEK_SET);  
  
  fgets (mystring , 20, in_file);  
  pch = (char *)strtok(mystring," "); 
  width = atoi(pch); 
  fprintf(out_file,"in_width = %d;\n",width);
  
  pch = (char *)strtok(NULL," ");  
  
  height = atoi(pch);  
  fprintf(out_file,"in_height = %d;\n",height);
  
  fgets (mystring , 5, in_file);
  maxgrey = atoi(mystring);
  
  fprintf(out_file,"in_maxgrey = %d;\n",maxgrey);
  
  fprintf(out_file,"unsigned char Data[%d][%d]={\n",height,width);
  
  for(i=0;i<height;i++){	
    for(j=0;j<width;j++){
      ch = fgetc(in_file);

      if(j==0)
        fprintf(out_file,"{0x%x,",(unsigned char)ch);

      else if(j==width-1 && i!=height-1 )
        fprintf(out_file,"0x%x},\n",(unsigned char)ch);

      else if(j==width-1 && i==height-1 )
        fprintf(out_file,"0x%x}\n",(unsigned char)ch);

      else
      fprintf(out_file,"0x%x,",(unsigned char)ch);
     
    }
    fprintf(out_file,"\n");
  }
  fprintf(out_file,"};\n\n");
  
  fclose(in_file);
  fclose(out_file);

  return 0;
}

int main(int argc, char* argv[])
{
  if ( argc != 3 )
    printf("usage: %s pgm-filename output-hex-file", argv[0]);
  else {
    readPgm(argv[1], argv[2]);
  }
  return 0;
}


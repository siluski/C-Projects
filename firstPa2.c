#include<stdlib.h>
#include<stdio.h>
#include<string.h>

unsigned short get(unsigned short value, int position)
{
  unsigned short x = value;
  x = (x<<position)&1;
  return x;
}
unsigned short set(unsigned short value, int position, int bit)
{
  unsigned short bitToChange;
  bitToChange = get(value,position);
  if(bitToChange == bit)
  {
    return value;
  }
  unsigned short y = 1;
  y = y<<position;
  y = y^value;
  return y;
}
unsigned short comp(unsigned short value, int position)
{
  unsigned short x = value;
  unsigned short y = 1;
  y = y<<position;
  x = x^y;
  return x;
}
int main(int argc, char *argv[])
{
  FILE *fp = fopen(argv[1],"r");
  unsigned short value;
  fscanf(fp,"%hu",&value);
  //printf("Value is: %u\n",value);
  while(!feof(fp))
  {
    char c[10];
    int position,bitVal,currentBit;
    //fscanf(fp,"%c%d\t%d",&c,&position,&bitVal);
    //printf("%c\n",c);
    //printf("%s\n",c);
    //fscanf(fp,"%c",&c);
    fscanf(fp,"%s\t%d\t%d\n",c,&position, &bitVal);
    //printf("current position: %d\n",position);
    //printf("current bitval: %d\n",bitVal);

    if(strcmp(c,"set")==0)
    {
      //fscanf(fp,"%d\t%d",&position,&bitVal);
      //printf("Setting bit at %d to %d\n",position,bitVal);
      value = set(value,position,bitVal);
      printf("%u\n",value);
    }
    if(strcmp(c,"comp")==0)
    {
      //fscanf(fp,"%d\t",&position);
      value = comp(value,position);
      printf("%u\n",value);
    }
    if(strcmp(c,"get")==0)
    {
      //fscanf(fp,"%d\t",&position);
      currentBit = get(value,position);
      printf("%u\n",currentBit);
    }
  }
  fclose(fp);
  return 0;
}

#include<stdio.h>
#include<stdlib.h>
unsigned short get(unsigned short value, int position)
{
  unsigned short x = value;
  x = (x>>position)&1;
  return x;
}
int main(int argc, char *argv[])
{
  unsigned short value = atoi(argv[1]);
  //printf("value = %u\n",value);
  unsigned short nxtBit, currBit;
  int i,j,pairs,oneBits;
  oneBits = 0;
  pairs = 0;
  for(i = 0; i<16; i++)
  {
    //prevBit = get(value,i);
    //currBit = get(value,i+1);
    currBit = get(value,i);
    j = i;
    while(currBit!=0)
    {
      //printf("current bit = %u\n",currBit);
      oneBits++;
      nxtBit = get(value,j+1);
      //printf("next bit = %u\n",nxtBit);
      if(nxtBit==currBit)
      {
        oneBits++;
        pairs++;
        j+=2;
      }
      else
      {
        j++;
      }
      currBit = get(value,j);
    }
    //printf("all onebits found at this iteration\n");
    i=j;
    /*if(prevBit==1&&currBit==1)
    {
      pairs++;
      oneBits+=2;
    }
    else if(prevBit==1)
    {
      oneBits++;
    }
    else if(currBit==1)
    {
      oneBits++;
    }*/

  }
  //printf("one Bits in number = %d\n",oneBits);
  if(oneBits%2==0)
  {
    printf("Even-Parity\t%d\n",pairs);
  }
  else
  {
    printf("Odd-Parity\t%d\n",pairs);
  }
  return 0;
}

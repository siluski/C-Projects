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
  unsigned short front,tail;
  int tailCount = 15;
  int headCount = 0;
  while(tailCount>=0&&headCount<16)
  {
    front = get(value,headCount);
    tail = get(value,tailCount);
    if(front!=tail)
    {
      printf("Not-Palindrome\n");
      return 0;
    }
    tailCount--;
    headCount++;
  }
  printf("Is-Palindrome\n");
  return 0;
}

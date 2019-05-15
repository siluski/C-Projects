#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
struct line
{
  unsigned long tag;
  int validBit;
  unsigned long useCounter;
};
unsigned long tagCalculator(unsigned long value,int setIndexSize, int offSetSize)
{
  unsigned long tag = 0;
  tag = value>>(setIndexSize+offSetSize);
  return tag;
}
unsigned long setIndexCalculator(unsigned long value, int setIndexSize, int offSetSize)
{
  unsigned long setIndex = 0;
  setIndex = value>>offSetSize;
  unsigned long number = pow(2,setIndexSize)-1;
  setIndex = setIndex&number;
  return setIndex;
}

unsigned long offSetCalculator(unsigned long value, unsigned long offSetSize)
{
  unsigned long offSet = 0;
  unsigned long mask = pow(2,offSetSize)-1;
  offSet = value&mask;
  return offSet;
}

unsigned long getNWayAssociativity(char* word,int lengthOfString)
{
  int i,j,lengthOfAssoc;
  j = 0;
  lengthOfAssoc = 0;
  for(i = 6; i<lengthOfString; i++)
  {
    lengthOfAssoc++;
  }
  char assoc[lengthOfAssoc];
  for(i = 6; i<lengthOfString; i++)
  {
    assoc[j]=word[i];
    j++;
  }
  return atol(assoc);
}

int main(int argc, char*argv[])
{
  printf("\n");
  unsigned long cacheSize = atoi(argv[1]);
  unsigned long log2OfCacheSize = log2(cacheSize);
  if(pow(2,log2OfCacheSize)!=cacheSize)
  {
    printf("Error, cache size not a power of 2\n");
    return 0;
  }
  unsigned long associativity = 0;
  printf("Cache size = %ld\n",cacheSize);
  char *typeOfAssociativity = argv[2];
  int lengthOfString = strlen(argv[2]);
  int blockSize = atoi(argv[4]);
  if(strcmp(typeOfAssociativity,"direct")!=0){
  if(lengthOfString>5)
  {
    associativity = getNWayAssociativity(typeOfAssociativity,lengthOfString);
    //printf("associativity = %d\n", associativity);
  }
  else
  {
    associativity = cacheSize/blockSize;
  }
}
else
{
  associativity = 1;
}
unsigned long log2OfAssociativity = log2(associativity);
if(pow(2,log2OfAssociativity)!=associativity)
{
  printf("Error, associativity not a power of 2, or invalid\n");
  return 0;
}
if(strcmp(argv[3],"lru")!=0)
{
  printf("Error, eviction policy must be entered as lru\n");
  return 0;
}

  //unsigned long value = 164311776;
  unsigned long i;
  unsigned long numOfSets = 0;
  unsigned long setIndexSize=0;
  unsigned long offSetSize=0;
  unsigned long setIndex=0;
  unsigned long offSet = 0;
  unsigned long tag = 0;

  if(strcmp(typeOfAssociativity,"assoc")!=0)
  {
  numOfSets = cacheSize/(associativity*blockSize);
  setIndexSize = log(numOfSets)/log(2);
  }
  printf("Number Of Sets is = %ld\n",numOfSets);
  offSetSize = log(blockSize)/log(2);
  printf("OffSet Size is = %ld\n",offSetSize);
  printf("SetIndex Size is = %ld\n",setIndexSize);

  int tagSize = 48 - (offSetSize + setIndexSize);
  printf("Size of tag is = %d\n",tagSize);
  printf("\n");
  printf("\n");
  struct line** cache = (struct line**)calloc((numOfSets+1),sizeof(struct line*));
  for(i = 0; i<numOfSets+1; i++)
  {
    cache[i]=(struct line*)calloc(associativity,sizeof(struct line));
  }

  FILE *traceFile = fopen(argv[5],"r");
  unsigned long address=0;
  char action;
  unsigned long junk = 0;
  unsigned long hits = 0;
  unsigned long misses = 0;
  unsigned long memoryReads = 0;
  unsigned long memoryWrites = 0;
  //unsigned long line = 0;
  while(fscanf(traceFile,"%lx:\t%c\t%lx\n",&junk,&action,&address)==3)
    {
    //line++;
    //printf("Current line is = %ld\n",line);
    //fscanf(traceFile,"%lx:\t%c\t%lx",&junk,&action,&address);
    //printf("Address = %ld\n",address);
    //printf("Action = %c\n",action);
    setIndex = setIndexCalculator(address,setIndexSize,offSetSize);
    //printf("set index = %ld\n",setIndex);
    tag = tagCalculator(address, setIndexSize,offSetSize);
    //printf("current tag = %ld\n",tag);
    unsigned long hitCheck = -1;

    for(i = 0; i<associativity; i+=1)
    {
      if(cache[setIndex][i].validBit==1)
      {
        if(cache[setIndex][i].tag==tag)
        {
          //printf("HIT\n");
          hitCheck = i;
          hits+=1;
          if(action == 'W')
          {
            memoryWrites+=1;
          }
          unsigned long j;
          cache[setIndex][hitCheck].useCounter=1;
          //printf("currently incrementing uses\n");
          for(j = 0; j<associativity; j+=1)
          {
            if(cache[setIndex][j].validBit==1)
            {
              if(j!=hitCheck)
              {
                //printf("tag = %ld\n",tag);
                cache[setIndex][j].useCounter+=1;
                //printf("current tag useCounter = %d\n", cache[setIndex][j].useCounter);
              }
            }
          }
        }
      }
      }
      if(hitCheck==-1)
      {
      //printf("MISS\n");
      misses+=1;
      if(action == 'R')
      {
          memoryReads+=1;
      }
        else
        {
          memoryReads+=1;
          memoryWrites+=1;
        }
          unsigned long j;
          unsigned long writeCheck = -1;

          for(j=0; j<associativity;j+=1)
          {
            if(cache[setIndex][j].validBit==0)
            {
              writeCheck = j;
              cache[setIndex][j].tag = tag;
              cache[setIndex][j].validBit = 1;
              break;
            }
          }
          if(writeCheck == -1)
          {
            // Implement LRU
            //printf("Evicting\n");
            unsigned long evictIndex = 0;
            unsigned long leastRecentlyUsed = cache[setIndex][0].useCounter;
            for(j = 0; j<associativity; j+=1)
            {
              if(cache[setIndex][j].useCounter>leastRecentlyUsed)
              {
                leastRecentlyUsed = cache[setIndex][j].useCounter;
                evictIndex = j;
              }
            }
            cache[setIndex][evictIndex].tag = tag;
            cache[setIndex][evictIndex].useCounter=1;
            writeCheck = evictIndex;
          }
          for(j = 0; j<associativity; j+=1)
          {
            if(cache[setIndex][j].validBit==1)
            {
              if(j!=writeCheck)
              {
                cache[setIndex][j].useCounter++;
              }
            }
          }
        }
      }
    /*for(i=0; i<numOfSets;i+=1)
    {
      unsigned long j;
      printf("row %ld\t",i);
        for(j=0; j<associativity; j+=1)
        {
          printf("%ld\t",cache[i][j].tag);
        }
        printf("\n");
    }*/
    for(i=0; i<numOfSets;i+=1)
    {
      free(cache[i]);
    }
    free(cache);
    struct line** cache2 = (struct line**)calloc((numOfSets+1),sizeof(struct line*));
    for(i = 0; i<numOfSets+1; i++)
    {
      cache2[i]=(struct line*)calloc(associativity,sizeof(struct line));
    }
    printf("no-prefetch\n");
    printf("reads = %ld\n",memoryReads);
    printf("writes = %ld\n",memoryWrites);
    printf("hits = %ld\n",hits);
    printf("misses = %ld\n",misses);
    printf("\n");
    printf("\n");


    rewind(traceFile);
    unsigned long memoryReads2= 0;
    unsigned long  memoryWrites2=0;
    unsigned long hits2 = 0;
    unsigned long misses2=0;

    while(fscanf(traceFile,"%lx:\t%c\t%lx\n",&junk,&action,&address)==3)
      {
      //line++;
      //printf("Current line is = %ld\n",line);
      //fscanf(traceFile,"%lx:\t%c\t%lx",&junk,&action,&address);
      //printf("Address = %ld\n",address);
      //printf("Action = %c\n",action);
      setIndex = setIndexCalculator(address,setIndexSize,offSetSize);
      //printf("set index = %ld\n",setIndex);
      tag = tagCalculator(address, setIndexSize,offSetSize);
      //printf("current tag = %ld\n",tag);
      unsigned long hitCheck = -1;

      for(i = 0; i<associativity; i+=1)
      {
        if(cache2[setIndex][i].validBit==1)
        {
          if(cache2[setIndex][i].tag==tag)
          {
            //printf("HIT\n");
            hitCheck = i;
            hits2+=1;
            if(action == 'W')
            {
              memoryWrites2+=1;
            }
            unsigned long j;
            cache2[setIndex][hitCheck].useCounter=1;
            //printf("currently incrementing uses\n");
            for(j = 0; j<associativity; j+=1)
            {
              if(cache2[setIndex][j].validBit==1)
              {
                if(j!=hitCheck)
                {
                  //printf("tag = %ld\n",tag);
                  cache2[setIndex][j].useCounter+=1;
                  //printf("current tag useCounter = %d\n", cache[setIndex][j].useCounter);
                }
              }
            }
          }
        }
        }
        if(hitCheck==-1)
        {
        //printf("MISS\n");
        misses2+=1;
        if(action == 'R')
        {
            memoryReads2+=1;
        }
          else
          {
            memoryReads2+=1;
            memoryWrites2+=1;
          }
            unsigned long j;
            unsigned long writeCheck = -1;

            for(j=0; j<associativity;j+=1)
            {
              if(cache2[setIndex][j].validBit==0)
              {
                writeCheck = j;
                cache2[setIndex][j].tag = tag;
                cache2[setIndex][j].validBit = 1;
                break;
              }
            }
            if(writeCheck == -1)
            {
              // Implement LRU
              //printf("Evicting\n");
              unsigned long evictIndex = 0;
              unsigned long leastRecentlyUsed = cache2[setIndex][0].useCounter;
              for(j = 0; j<associativity; j+=1)
              {
                if(cache2[setIndex][j].useCounter>leastRecentlyUsed)
                {
                  leastRecentlyUsed = cache2[setIndex][j].useCounter;
                  evictIndex = j;
                }
              }
              cache2[setIndex][evictIndex].tag = tag;
              cache2[setIndex][evictIndex].useCounter=1;
              writeCheck = evictIndex;
            }
            for(j = 0; j<associativity; j+=1)
            {
              if(cache2[setIndex][j].validBit==1)
              {
                if(j!=writeCheck)
                {
                  cache2[setIndex][j].useCounter++;
                }
              }
            }
            unsigned long prefetchCheck = -1;
            unsigned long prefetchStillNotHere = -1;
            unsigned long prefetch = address+blockSize;
            unsigned long prefetchTag = tagCalculator(prefetch,setIndexSize,offSetSize);
            unsigned long prefetchSetIndex = setIndexCalculator(prefetch,setIndexSize,offSetSize);
            for(j = 0; j<associativity; j++)
            {
              if(cache2[prefetchSetIndex][j].tag==prefetchTag)
              {
                prefetchCheck = j;
                break;
              }
            }
            if(prefetchCheck==-1)
            {
              memoryReads2++;
              for(j=0; j<associativity; j++)
              {
                if(cache2[prefetchSetIndex][j].validBit==0)
                {
                  cache2[prefetchSetIndex][j].validBit=1;
                  cache2[prefetchSetIndex][j].tag = prefetchTag;
                  prefetchStillNotHere = j;
                  break;
                }
              }
              if(prefetchStillNotHere ==-1)
              {
                unsigned long prefetchEvictIndex = 0;
                unsigned long prefetchLeastRecentlyUsed = cache2[prefetchSetIndex][0].useCounter;
                for(j = 0; j<associativity; j+=1)
                {
                  if(cache2[prefetchSetIndex][j].useCounter>prefetchLeastRecentlyUsed)
                  {
                    prefetchLeastRecentlyUsed = cache2[prefetchSetIndex][j].useCounter;
                    prefetchEvictIndex = j;
                  }
                }
                cache2[prefetchSetIndex][prefetchEvictIndex].tag = prefetchTag;
                cache2[prefetchSetIndex][prefetchEvictIndex].useCounter=1;
                for(j = 0; j<associativity; j+=1)
                {
                  if(cache2[prefetchSetIndex][j].validBit==1)
                  {
                    if(j!=prefetchEvictIndex)
                    {
                      cache2[prefetchSetIndex][j].useCounter++;
                    }
                  }
                }
              }
            }
          }
        }
        fclose(traceFile);
        for(i=0; i<numOfSets;i+=1)
        {
          free(cache2[i]);
        }

        free(cache2);
        printf("with-prefetch\n");
        printf("reads = %ld\n",memoryReads2);
        printf("writes = %ld\n",memoryWrites2);
        printf("hits = %ld\n",hits2);
        printf("misses = %ld\n",misses2);
        return 0;
  }

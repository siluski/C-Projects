#include<stdlib.h>
#include<stdio.h>
int main(int argc, char* argv[])
{
  FILE *fp = fopen(argv[1],"r");
  int i,j,k,row1,column1, row2, column2;
  fscanf(fp,"%d\t%d",&row1,&column1);
  //int a1[rows][columns];
  int** a1 = (int**)malloc(row1*sizeof(int*));
  for(i = 0; i<row1; i++)
  {
    a1[i]=(int*)malloc(column1*sizeof(int));
  }
  for(i=0;i<row1;i++){
      for(j=0;j<column1;j++)
      {
          fscanf(fp,"%d\t",&a1[i][j]);
      }
  }
  fscanf(fp,"%d\t%d",&row2,&column2);
  //int a2[rows][columns];
  int** a2 = (int**)malloc(row2*sizeof(int*));
  for(i = 0; i<row2; i++)
  {
    a2[i]=(int*)malloc(column2*sizeof(int));
  }
  for(i=0;i<row2;i++){
      for(j=0;j<column2;j++)
      {
          fscanf(fp,"%d\t",&a2[i][j]);
      }
  }
  //int a1[2][2] = {{1,2},{3,4}}
  //int a2[2][2] = {{1,2},{3,4}};
  //int row1 = sizeof(a1) / sizeof(a1[0]);
  //int column1 = sizeof(a1[0])/sizeof(a1[0][0]);
  //int row2 = sizeof(a2) / sizeof(a2[0]);
  //int column2 = sizeof(a2[0])/sizeof(a2[0][0]);
  if(column1!=row2)
  {
    printf("bad-matrices\n");
    for(i=0; i<row1;i++)
    {
        //printf("freeing memory\n");
        free(a1[i]);
    }
    for(i=0;i<row2;i++)
    {
      free(a2[i]);
    }
    free(a1);
    free(a2);
    fclose(fp);

    return 0;
  }
  //int result[row1][column2];
  int** result = (int**)malloc(row1*sizeof(int*));
  for(i=0; i<row1;i++){
    result[i]=(int*)malloc(column2*sizeof(int));
  }
  //int resultRow = sizeof(result)/sizeof(result[0]);
  //int resultColumn = sizeof(result[0])/sizeof(result[0][0]);
  //printf("%d\n%d\n",row,column);
  for(i = 0; i<row1; i++)
  {
    for(j = 0; j<column2; j++)
    {
      result[i][j] = 0;
      //*(result+i*column2+j) = 0;
      for(k = 0; k<column1; k++)
      {
        //printf("%d * %d\n",(*(a1+i)+k), (*(a2+k)+j));
        result[i][j]+= a1[i][k]*a2[k][j];
      }
    }
  }
  for(i = 0; i<row1; i++)
  {
    for(j = 0; j<column2; j++)
    {
      printf("%d\t", result[i][j]);
    }
    printf("\n");
  }
  for(i=0; i<row1;i++)
  {
      //printf("freeing memory\n");
      free(a1[i]);
  }
  for(i=0;i<row2;i++)
  {
    free(a2[i]);
  }
  for(i=0;i<row1;i++)
  {
    free(result[i]);
  }
  //free(a1);
  //free(a2);
  //free(result);
  free(a1);
  free(a2);
  free(result);
  fclose(fp);
  return 0;
}

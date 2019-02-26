#include<stdio.h>
#include<stdlib.h>
struct Node{
  int data;
  struct Node* next;
};
void insert(struct Node** front, struct Node* new)
{
  new -> next = *front;
  *front = new;
}
struct Node* createNode(int data)
{
  struct Node* new;
  new = (struct Node*)malloc(sizeof(struct Node));
  new->data = data;
  new -> next = NULL;
  return new;
  //free(new);
}
int main(int argc, char* argv[])
  {
    struct Node* array[10000];
    int i,cell;
    int collisions = 0;
    int searches = 0;
    for(i=0; i<10000; i++)
    {
      array[i] = NULL;
    }
    FILE* fp = fopen(argv[1],"r");
    //printf("size of file: %d",(int)sizeof(fp));
    struct Node* new;
    //struct Node* ptr = (struct Node*)malloc(sizeof(struct Node*));
    struct Node* ptr;
    while(!feof(fp))
    {
      int x;
      char c;
      fscanf(fp,"%c\t%d\n",&c,&x);
      cell = x%10000;
      if(cell<0)
      {
        //printf("Current cell: %d\n",cell);
        cell+=10000;
        //printf("Current cell: %d\n",cell);
      }
      if(c=='i'){
      new = createNode(x);
      if(array[cell]!=NULL)
      {
        collisions++;
      }
      //printf("Inserting: %d\n",x);
      insert(&array[cell],new);
      //printf("Still working\n");
    }
    else if(c=='s')
    {
      //cell = x%10000;
      ptr = array[cell];
      while(ptr!=NULL&&ptr->data!=x)
      {
        ptr = ptr->next;
      }
      if(ptr!=NULL)
      {
        searches++;
      }
      //free(ptr);
      //ptr = NULL;
    }
    //free(ptr);
    }
    //free(ptr);
    printf("%d\n",collisions);
    printf("%d\n",searches);
    //struct Node* current = (struct Node*)malloc(sizeof(struct Node*));
    //struct Node* previous = (struct Node*)malloc(sizeof(struct Node*));
    struct Node* current;
    struct Node* previous;
    for(i = 0; i<10000; i++)
    {
      if(array[i]!=NULL){
      previous = array[i];
      //printf("currently freeing memory...\n");
      while(previous!=NULL)
      {
        //printf("currently freeing: %d\n",previous->data);
        current = previous->next;
        free(previous);
        previous = current;
      }
      //current = previous;
      //free(current);
      //printf("memory has been freed moving on!\n");
    }
    }
    free(current);
    free(previous);
    fclose(fp);
    return 0;
  }

#include<stdlib.h>
#include<stdio.h>
struct BSTnode{
  int data;
  struct BSTnode* left;
  struct BSTnode* right;
};
struct BSTnode* makeNode(int x)
{
  struct BSTnode* new;
  new = (struct BSTnode*)malloc(sizeof(struct BSTnode));
  new -> data = x;
  new -> left = NULL;
  new -> right = NULL;
  return new;
}
struct BSTnode* insert(struct BSTnode* root, int new)
{
  if(root == NULL)
  {
    return makeNode(new);
  }
  struct BSTnode *current = root;
  struct BSTnode *previous = NULL;
  struct BSTnode* newNode = makeNode(new);
  while(current!=NULL)
  {
    previous = current;
    if(current->data>new)
    {
      current = current -> left;
    }
    else if(current->data<new)
    {
      current = current -> right;
    }
    else
    {
      return current;
    }
  }
  if(previous == NULL)
  {
    previous = newNode;
  }
  else if(previous->data>new)
  {
    previous ->left = newNode;
  }
  else if(previous->data<new)
  {
    previous ->right = newNode;
  }
  return previous;
}
void print(struct BSTnode* root)
{
  if(root==NULL)
  {
    return;
  }
  print(root->left);
  printf("%d\t",root->data);
  print(root->right);
}
void freeMemory(struct BSTnode* root)
{
  if(root==NULL)
  {
    return;
  }
  freeMemory(root->left);
  freeMemory(root->right);
  free(root);
}
int main(int argc, char* argv[])
{
  FILE* fp = fopen(argv[1],"r");
  if(fp==NULL){printf("error");return 0;}
  int size = 0;
  while(!feof(fp))
  {
    char c;
    c = fgetc(fp);
    if(c=='\n'){ size++;}
  }
  //printf("%d size\n",size);
  rewind(fp);
  int count = 0;
  int a[size];
  //printf("no fault yet\n");
  while(!feof(fp)){
    int x;
    char c;
    fscanf(fp,"%c\t%d\n",&c,&x);
    if(c=='i'){
    //printf("value being added: %d\n",x);
    a[count]=x;
    count++;
    }
    //printf("current value: %d\n",a[count]);
  }
  //printf("no fault yet\n");
  //int a[11] = {5,5,5,5,5,5,5,5,5,5,5};
  struct BSTnode* root = NULL;
  root = insert(root,a[0]);
  int i;
  for(i = 1; i<size;i++)
  {
    //printf("inserting %d\n", a[i]);
    insert(root,a[i]);
  }
  print(root);
  freeMemory(root);
  root = NULL;
  printf("\n");
  fclose(fp);
  //printf("root data: %d\n", root->data);
}

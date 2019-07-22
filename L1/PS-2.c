#include <stdio.h>
#include <stdlib.h>

typedef struct deque {
    int* ptr;
    int rear,front;
    int size;
} deque;

void newDeque(deque *p);
void insertFront(deque *p, int n);
void insertBack(deque *p, int n);
void deleteFront(deque *p);
void deleteBack(deque *p);
int get(deque *p, int i);
int search(deque *p, int n);
void printList(deque *p);
void empty(deque *p);

void main() {
  deque que;
  newDeque(&que);
  printf("\n1.InsertFront\n2.InsertBack\n3.DeleteRear\n4.DeleteFront\n5.Get Element\n6.Search element\n7.Print deque\n8.Empty deque\n\nEnter ur choice");
  printf("\nenter -1 to exit\n");

  int f;  

  while(1){
    
    scanf("%d",&f);
    // printf("%d\n",f);
    switch(f) {
      case 1: printf("operation: insert at front end\n");
              printf("enter interger\n");
              int n;
              scanf("%d",&n);
              insertFront(&que,n);
              printf("operation completed\n");
              break;
      case 2: printf("operation: insert at rear end\n");
              printf("enter interger\n");
              int num;
              scanf("%d",&num);
              insertBack(&que,num);
              printf("operation completed\n");
              break;
      case 3: printf("operation: deletion at front end\n");
              deleteFront(&que);
              printf("operation completed\n");
              break;
      case 4: printf("operation: deletion at rear end\n");
              deleteBack(&que);
              printf("operation completed\n");
              break;
      case 5: printf("operation: get element\n");
              printf("enter index\n");
              int i;
              scanf("%d",&i);
              int ans=get(&que,i);
              if(ans==-1)
                printf("error:index greater than size\n");
              else
                printf("%d\n",ans); 
              printf("operation completed\n");
              break;
      case 6: printf("enter number \n");
              int number;
              scanf("%d",&number);
              int answer=search(&que,n);
              if(answer==-1)
                printf("element does not exist in deque\n");
              else
                printf("%d\n",answer); 
              printf("operation completed\n");
              break;
      case 7: printList(&que);
              break;
      case 8: empty(&que);
              break;
      default: printf("operation does not exist\n");
    }
    if(f==-1) break;
  }
}

void newDeque(deque *p){
  p->rear = -1;
  p->front = -1;
  p->size=0;
}

void insertFront(deque *p, int n) {
  if(p->rear==-1&&p->front==-1){
    p->ptr=(int*)(calloc(1,sizeof(int)));
    p->ptr[0]=n;
    p->rear=p->rear+1;
    p->front=p->front+1;
    p->size++;
  }
  else if(p->rear+1==p->size){
    p->ptr=realloc(p->ptr,p->size*2*sizeof(int));
    p->size=p->size*2;
    for(int i=p->rear+1;i>0;i--){
      p->ptr[i]=p->ptr[i-1];
    }
    p->ptr[0]=n;
    p->rear=p->rear+1;
  }
  else {
    for(int i=p->rear+1;i>0;i--){
      p->ptr[i]=p->ptr[i-1];
    }
    p->ptr[0]=n;
    p->rear=p->rear+1;
  }
}

void insertBack(deque *p, int n){
    // printf("%d",p->rear);
    // printf("%d",n);
  if(p->rear==-1&&p->front==-1){
    p->ptr=(int*)(malloc(1*sizeof(int)));
    int *k=p->ptr;
    k[0]=n;
    printf("%d",k[0]);
    p->rear=p->rear+1;
    p->front=p->front+1;
    p->size++;
  }
  else if(p->rear+1==p->size){
    p->ptr=realloc(p->ptr,p->size*2*sizeof(int));
    p->size=p->size*2;
    p->rear=p->rear+1;
    p->ptr[p->rear]=n;
  }
  else {
    p->rear=p->rear+1;
    p->ptr[p->rear]=n; 
  }
}

void deleteFront(deque *p)
{
  if(p->rear==-1&&p->front==-1)
    printf("operation not valid");
  else if(p->size==1){
    p->rear=-1;
    p->front=-1;
    free(p->ptr);
    p->size=0;
  }
  else {
    for(int i=0;i<p->rear;i++)
      p->ptr[i]=p->ptr[i+1];
    p->ptr[p->rear]=0;
    p->rear=p->rear-1;
    if((p->size/2)>p->rear){
      p->ptr=realloc(p->ptr,(p->rear+1)*sizeof(int));
      p->size=p->rear+1;
    }
  }  
}

void deleteBack(deque *p){
  if(p->rear==-1&&p->front==-1)
    printf("operation not valid");
  else if(p->size==1){
    p->rear=-1;
    p->front=-1;
    free(p->ptr);
    p->size=0;
  } 
  else {
    p->ptr[p->rear]=0;
    p->rear=p->rear-1;
    if((p->size/2)>p->rear){
      p->ptr=realloc(p->ptr,(p->rear+1)*sizeof(int));
      p->size=p->rear+1;
    } 
  }
}

int get(deque  *p, int i){
  if(i>=p->size)
    return -1;
  else
    return p->ptr[i];
}

int search(deque *p, int n){
  int index=-1;
  for(int i=0;i<=p->rear;i++){
    if(p->ptr[i]==n)
        index=i;
  }
  return index;
}

void printList(deque *p){
    printf("List is given as");
    printf("valid entries are till %d",p->size);
    for(int i=0;i<p->size;i++)
      printf("%d\n",p->ptr[i]);
}

void empty(deque *p){
  free(p->ptr);
  p->rear=-1;
  p->front=-1;
}
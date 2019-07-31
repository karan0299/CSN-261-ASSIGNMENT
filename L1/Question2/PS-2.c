/** 
 *  @file	PS-2.c
 *  @brief	brief explanation of PS-2.c from xn
 @author Karanpreet Singh
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//! struct deque with given data fields
typedef struct deque {
  //! array to store value
  int* ptr; 
  //! point to first and last value of array
  int rear,front;
  //! gives the current size of array 
  int size;
} deque;

//! initialize the deque
void newDeque(deque *p);

//! insert at front  of deque
void insertFront(deque *p, int n);

//! insert at last last of deque
void insertBack(deque *p, int n);

//! delete from front of deque 
void deleteFront(deque *p);

//! delete from last of deque
void deleteBack(deque *p);

//! get the element at position i of the deque
int get(deque *p, int i);

//! search for number if exists or not in deque
int search(deque *p, int n);

//! print the deque
void printList(deque *p);

//! empty the deque , deleting all elements
void empty(deque *p);


/**
 @brief this main func
 @ return nothing
 */

void main() {
  //! declare the deque
  deque que;
  newDeque(&que);
  //! to mark start and end of cpu clock
  clock_t start, end; 
  //! store the time taken by cpu to perform operation
  double cpu_time;
  //! choice for operation in switch menu
  int f;    
  while(1){  
    printf("\n\n1.InsertFront\n2.InsertBack\n3.DeleteRear\n4.DeleteFront\n5.Get Element\n6.Search element\n7.Print deque\n8.Empty deque\n\nEnter ur choice");
    printf("\nenter -1 to exit\n");
    scanf("%d",&f);
    switch(f) {
      case 1: //! insert at front  of deque
              printf("operation: insert at front end\n");
              printf("enter interger\n");
              int n;
              scanf("%d",&n);
              start = clock ();
              insertFront(&que,n);
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 2: //! insert at last last of deque
              printf("operation: insert at rear end\n");
              printf("enter interger\n");
              int num;
              scanf("%d",&num);
              start = clock ();
              insertBack(&que,num);
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 3: //! delete from front of deque 
              printf("operation: deletion at front end\n");
              start = clock ();
              deleteFront(&que);
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 4: //! delete from last of deque
              printf("operation: deletion at rear end\n");
              start = clock ();
              deleteBack(&que);
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 5: //! get the element at position i of the deque
              printf("operation: get element\n");
              printf("enter index\n");
              int i;
              scanf("%d",&i);
              start = clock ();
              int ans=get(&que,i);
              if(ans==-1)
                printf("error:index greater than size\n");
              else
                printf("%d\n",ans); 
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 6: //! search for number if exists or not in deque
              printf("enter number \n");
              int number;
              scanf("%d",&number);
              start = clock ();
              int answer=search(&que,number);
              if(answer==-1)
                printf("element does not exist in deque\n");
              else
                printf("%d\n",answer); 
              printf("operation completed\n");
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 7: //! print the deque
              start = clock ();
              printList(&que);
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
              break;

      case 8: //! empty the deque , deleting all elements
              start = clock ();
              empty(&que);
              end = clock();
              cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
              printf("cpu time used %f\n", cpu_time);
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
    printf("operation not valid\\n");
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
    printf("operation not valid\n");
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
    if(p->ptr[i]==n){
        index=i;
        break;
    }
  }
  return index;
}

void printList(deque *p){
    printf("List is given as \n");
    printf("%d entries are made \n",p->rear+1 );
    for(int i=0;i<p->size;i++)
      printf("%d\n",p->ptr[i]);
}

void empty(deque *p){
  free(p->ptr);
  p->rear=-1;
  p->front=-1;
}
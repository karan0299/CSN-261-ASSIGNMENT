#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

void removeRed(int **red,int **blue,int **green){
    for(int i=0;i<953;i++){
          for(int j=0;j<1268;j++){
               if(red[i][j]>blue[i][j]&&red[i][j]>green[i][j])
                    red[i][j]=0;
          }
    }
}

void removeBlue(int **red,int **blue,int **green){
    for(int i=0;i<953;i++){
          for(int j=0;j<1268;j++){
               if(blue[i][j]>red[i][j]&&blue[i][j]>green[i][j])
                    blue[i][j]=0;
          }
    }
}
void removeGreen(int **red,int **blue,int **green){
    for(int i=0;i<953;i++){
          for(int j=0;j<1268;j++){
               if(green[i][j]>blue[i][j]&&green[i][j]>red[i][j])
                    green[i][j]=0;
          }
    }
}

void preserveRed(int **red,int **blue,int **green){
    removeBlue(red,blue,green);
    removeGreen(red,blue,green);
}

void preserveBlue(int **red,int **blue,int **green){
    removeRed(red,blue,green);
    removeGreen(red,blue,green);
}

void preserveGreen(int **red,int **blue,int **green){
    removeBlue(red,blue,green);
    removeRed(red,blue,green);
}

void pixelValue(int x, int y, int **red,int **blue,int **green){
    printf("pixel value at give point is\n");
    printf("RGB(%d,%d,%d)",red[x][y],green[x][y],blue[x][y]);
}

void inputFile(int** arr, char* ch){
    FILE *f= fopen(ch,"r");
    char buff[6000];
    int i=0;
    int j=0;
    while(fgets(buff,6000,f)){ 
        char *token=strtok(buff,",");
        j=0;
        while(token){
               int num1= atoi(token);
               arr[i][j]=num1;
               token=strtok(NULL,",");
               j++;
          }
        i++;
    }
}

void main() {
    int **red = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    red[i] = (int*)malloc(1268 * sizeof(int));
    int **blue = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    blue[i] = (int*)malloc(1268 * sizeof(int));
    int **green = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    green[i] = (int*)malloc(1268 * sizeof(int));

    inputFile(red,"./SCQ3/Q3_Input/Red.dat");
    inputFile(green,"./SCQ3/Q3_Input/Green.dat");
    inputFile(blue,"./SCQ3/Q3_Input/Blue.dat"); 

     clock_t start, end;
     double cpu_time;

    int op;
    while(1){
        printf("\n1.Remove red shade\n2.Remove green shade\n3.Remove blue shade\n4.Preserve red\n5.Preserve Blue\n6.Preserve Green\n7.Print current pixel value\n\nEnter ur choice");
        printf("\nenter -1 to exit\n");
        scanf("%d",&op);
        switch(op) {
            case 1: 
                    start = clock ();
                    removeRed(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 2: 
                    start = clock ();
                    removeGreen(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 3:     
                    start = clock ();
                    removeBlue(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break; 
                    
            case 4: 
                    start = clock ();
                    preserveRed(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 5: 
                    start = clock ();
                    preserveBlue(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 6: 
                    start = clock ();
                    preserveGreen(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 7: 
                    printf("Enter the coordinates ,  0<=x<953 , 0<=y<1268");
                    int x,y;
                    scanf("%d",&x);
                    scanf("%d",&y);
                    start = clock ();
                    pixelValue(x,y,red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;
                    
            default: printf("invalid operation");                       
        }
        if(op==-1)
            break;
    }
}
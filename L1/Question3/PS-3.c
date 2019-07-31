/** 
 *  @file	PS-3.c
 *  @brief	brief explanation of PS-3.c from xn
 @author Karanpreet Singh
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

//! remove red shade from the image
void removeRed(int **red,int **blue,int **green);

//! remove Blue shade from the image
void removeBlue(int **red,int **blue,int **green);

//! remove Green shade from the image
void removeGreen(int **red,int **blue,int **green);

//! preserve only red shade in the image
void preserveRed(int **red,int **blue,int **green);

//! preserve only Blue shade in the image
void preserveBlue(int **red,int **blue,int **green);

//! preserve only Green shade in the image
void preserveGreen(int **red,int **blue,int **green);

//! print current value of RGB in pixel at given point 
void pixelValue(int x, int y, int **red,int **blue,int **green);

//! read the file given in form of array and store in respective arrays
void inputFile(int** arr, char* ch);

/**
 @brief this main func
 @ return nothing
 */

void main() {
    // ! 2D array to store red pixel values
    int **red = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    red[i] = (int*)malloc(1268 * sizeof(int));

    // ! 2D array to store blue pixel values
    int **blue = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    blue[i] = (int*)malloc(1268 * sizeof(int));

    // ! 2D array to store green pixel values
    int **green = (int**)malloc(953 * sizeof(int*));
    for (int i=0; i<953; ++i)
    green[i] = (int*)malloc(1268 * sizeof(int));

    inputFile(red,"./SCQ3/Q3_Input/Red.dat");
    inputFile(green,"./SCQ3/Q3_Input/Green.dat");
    inputFile(blue,"./SCQ3/Q3_Input/Blue.dat"); 

    //! to mark start and end of cpu clock
    clock_t start, end;
    //! store the time taken by cpu to perform operation 
    double cpu_time;
    //! choice for operation in switch menu
    int op; 
    while(1){
        printf("\n1.Remove red shade\n2.Remove green shade\n3.Remove blue shade\n4.Preserve red\n5.Preserve Blue\n6.Preserve Green\n7.Print current pixel value\n\nEnter ur choice");
        printf("\nenter -1 to exit\n");
        scanf("%d",&op);
        switch(op) {
            case 1: //! remove Green shade from the image
                    start = clock ();
                    removeRed(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f\n", cpu_time);
                    break;

            case 2: //! remove red shade from the image
                    start = clock ();
                    removeGreen(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f\n", cpu_time);
                    break;

            case 3: //! remove Blue shade from the image    
                    start = clock ();
                    removeBlue(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f\n", cpu_time);
                    break; 
                    
            case 4: //! preserve only Red shade in the image
                    start = clock ();
                    preserveRed(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 5: //! preserve only Blue shade in the image
                    start = clock ();
                    preserveBlue(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f", cpu_time);
                    break;

            case 6: //! preserve only Green shade in the image
                    start = clock ();
                    preserveGreen(red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f\n", cpu_time);
                    break;

            case 7: //! print current value of RGB in pixel at given point 
                    printf("Enter the coordinates ,  0<=x<953 , 0<=y<1268\n");
                    int x,y;
                    scanf("%d",&x);
                    scanf("%d",&y);
                    start = clock ();
                    pixelValue(x,y,red,blue,green);
                    end = clock();
                    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
                    printf("cpu time used %f\n", cpu_time);
                    break;

            default: printf("invalid operation\n");                       
        }
        if(op==-1)
            break;
    }
}

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
    printf("RGB(%d,%d,%d)\n",red[x][y],green[x][y],blue[x][y]);
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


#include <stdio.h>
#include <stdlib.h>
#include<string.h>


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
                    blue[i][j]=0;
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

     FILE *f1= fopen("./SCQ3/Q3_Input/Red.dat","r");
     FILE *f2= fopen("./SCQ3/Q3_Input/Blue.dat","r");
     FILE *f3= fopen("./SCQ3/Q3_Input/Green.dat","r");
     char buff[6000];
     int i=0;
     int j=0;
    while(fgets(buff,6000,f1)){ 
      // printf("sxdcfghnj");
        char *token=strtok(buff,",");
         j=0;
      while(token){
           // printf("sdffczxf");
         int num1= atoi(token);
        // printf("%d\n",num1);
         red[i][j]=num1;
         token=strtok(NULL,",");
         j++;
        }
        i++;
   }
   i=0;
   while(fgets(buff,6000,f2)) {
        // printf("sxdcfghnj");
        char *token2=strtok(buff,",");
       // printf("%s\n",token2);
         j=0;
      while(token2){
           // printf("sdffczxf");
         int num= atoi(token2);
         printf("%d\n",num);
         blue[i][j]=num;
         token2=strtok(NULL,",");
         j++;
        }
        //free(token2);
        i++;
   }

     i=0;
   while(fgets(buff,6000,f3)) {
        // printf("sxdcfghnj");
        char *token3=strtok(buff,",");
        //printf("%s\n",token3);
         j=0;
      while(token3){
         int num3= atoi(token3);
         printf("%d\n",num3);
         green[i][j]=num3;
         token3=strtok(NULL,",");
         j++;
        }
        i++;
   }
  
int op;
     printf("Enter option");
     scanf("%d",&op);
     switch(op) {
          case 1: removeRed(red,blue,green);
                  break;
          case 2: removeGreen(red,blue,green);
                  break;  
          case 3: removeBlue(red,blue,green);
                  break; 
          case 4: preserveRed(red,blue,green);
                  break;
          case 5: preserveBlue(red,blue,green);
                  break; 
          case 6: preserveGreen(red,blue,green);
                  break;
          default: printf("invalid operation");                       
     }
     FILE *fptr;
    fptr = fopen("check.dat","w");
    for(int k=0;k<953;k++){
        for(int m=0;m<1268;m++)
          fprintf(fptr,"%d,",red[k][m]);
        fprintf(fptr,"\n");
    }
    fclose(fptr);
}
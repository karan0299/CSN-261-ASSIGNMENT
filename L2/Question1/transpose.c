/** 
 *  @file	PS-1.c
 *  @brief	brief explanation of PS-1.c from xn
 @author karanpreet Singh
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>

void encrypt(char **input,char **output,int a,int b,int n,int r,FILE* fp1);

void main(int argc, char** argv) {
    if(argc<5||atoi(argv[1])<1)
    exit(EXIT_FAILURE);

    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);

    char **input;
    input = (char **)malloc(100 * sizeof(char *)); 
    for (int k=0; k<100; k++) 
         input[k] = (char *)malloc(6* sizeof(char)); 

    FILE* fp = fopen(argv[4], "r");

    char buff[n+1];

    int i=0;

    while(fgets(buff,sizeof(buff),fp)){
      
      for(int j=0;j<5;j++){
        if(buff[j]=='\n'){
          buff[j]='\0';
          break;
        }
      }
      for(int j=0;j<5;j++){
        if(buff[j]==' '){
          buff[j]=' ';
          break;
        }
      }

      input[i]= (char*)malloc(strlen(buff)*sizeof(char));
      strcpy(input[i],buff); 
      i++;

    }
    
    char **output = (char **)malloc(i * sizeof(char *)); 
    for (int k=0; k<i; k++) 
         output[k] = (char *)malloc(5* sizeof(char)); 
    FILE* fp1 = fopen("outputfile.txt","w");

   if(fp1 == NULL)
   {
      printf("Error!");
      exit(1);
   }

   encrypt(input,output,a,b,n,i,fp1);
}

void encrypt(char **input,char **output,int a,int b,int n,int r, FILE* fp1){
  int i=0;
    while(r--){
        for(int j=0;j<5;j++){
            if(input[i][(a*j + b)%n]=='\0'){
            output[i][j] = '\0';
            fprintf(fp1,"\\0");
            }
            else{
            output[i][j] = input[i][(a*j + b)%n];
            fprintf(fp1,"%c", output[i][j]);
            }
        }
        fprintf(fp1,"\n");
        i++;
    }
}
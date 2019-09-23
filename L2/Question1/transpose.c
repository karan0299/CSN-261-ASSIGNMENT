/** 
*@file transpose.c
*@brief this header file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 04/08/19
*/

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>

/**
*This method will be used to encrypted the input file based on encryption key provided
*@author Karanpreet Singh
*@param input holds the data which is to be encrypted
*@param output array in which encrypted data is stored
*@param a one parameter of encryption key
*@param b another parameter of encryption key
*@param n another paramneter of encryption key
*@param r contains number of 5 length words
*@param fp1 pointer to file in which encrypted data is written
*@date 04/08/19
*/
void encrypt(char **input,char **output,int a,int b,int n,int r,FILE* fp1);

/**
*This method will be used to check if gcd of two numbers is unity or not
*@author Karanpreet Singh
*@param n Number 1
*@param a Number 2
*@date 04/08/19
*/
bool gcd(int n,int a);

/**
*This method will be used to control the flow of program 
*@author Karanpreet Singh
*@param argc Contains number of command line arguments given
*@param argv array which holds all the commandline arguments
*@date 04/08/19
*/

int main(int argc, char** argv) {
    
     /// to mark start and end of cpu clock
    clock_t start, end;
    /// store the time taken by cpu to perform operation 
    double cpu_time;

    start = clock ();

    /// non zero exit if arguments are less than 5 or value of n is less than 1
    if(argc<5||atoi(argv[1])<1){
        printf("invalid arguments");
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    
    /// checks if gcd of a and n is 1
    if(!gcd(n,a)){
        printf("Error: Decryption Key does not exist for the pair n and a , choose the value such that a and n are coprime ");
        return (-1);
    }

    /// input char array holds the arguments to be encrypted
    char **input;
    input = (char **)malloc(100 * sizeof(char *)); 
    for (int k=0; k<100; k++) 
         input[k] = (char *)malloc(6* sizeof(char)); 

    FILE* fp = fopen(argv[4], "r");
    
    if(fp == NULL) {
      printf("Error!");
      exit(1);
    }

    char buff[n+1];

    int i=0;

    while(fgets(buff,sizeof(buff),fp)) {  
      
      for(int j=0;j<5;j++){
        if(buff[j]=='\n'){
          buff[j]='-';
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

    if(fp1 == NULL) {
      printf("Error!");
      exit(1);
    }

    encrypt(input,output,a,b,n,i,fp1);


    end = clock();
    
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTotal CPU time taken is %f \n",cpu_time);

    return(0);
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

bool gcd(int n, int a){
    for(int i=2;i<=a;i++){
        if(a%i==0&&n%i==0)
            return false;
    }
    return true;
}
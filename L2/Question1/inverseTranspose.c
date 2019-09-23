/** 
*@file inverseTranspose.c
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
*This method will be used to decrypted the input file based on decryption key provided
*@author Karanpreet Singh
*@param input holds the data which is to be decrypted
*@param a_inverse one ot the parameter of decryption key
*@param b another parameter of decryption key
*@param n another paramneter of decryption key
*@param r contains number of 5 length words
*@param fp2 pointer to file in which decrypted data is written
*@date 04/08/19
*/
void decrypt(char **input,int a_inverse,int b,int n,int r,FILE* fp2);

/**
*This method will be used to
*@author Karanpreet Singh
*@param 
*@param 
*@date 04/08/19
*/
int inverse(int a,int n);

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

    /// non zero exit if arguments are less than 5 or value of n is less than 1
    if(argc<5||atoi(argv[1])<1)
    exit(EXIT_FAILURE);

    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    
    /// checks if gcd of a and n is 1
    if(!gcd(n,a)){
        printf("Error: Decryption Key does not exist , some data encrypted is lost ");
        return (-1);
    }

    char **input = (char **)malloc(100 * sizeof(char *)); 
    for (int k=0; k<100; k++) 
         input[k] = (char *)malloc(6* sizeof(char)); 

    FILE* fp = fopen(argv[4], "r");

    char buff[2*n+1];

    int i=0;

    while(fgets(buff,sizeof(buff),fp)){
        int m=0;
        for(int k=0;k<strlen(buff);k++){
            if(buff[k]=='0')
            continue;
            input[i][m++] = buff[k]; 
        } 
        //printf("%s",input[i]);
        i++;
    }
    
    int a_inverse = inverse(a,n);

    FILE * fp2 = fopen("decryptedoutputfile.txt","w");
    
    decrypt(input,a_inverse,b,n,i,fp2);

    end = clock();
    
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTotal CPU time taken is %f \n",cpu_time);
    
    return(0);
}

void decrypt(char **input,int a_inverse,int b,int n,int r,FILE* fp2){
    int i=0;
    while(r--){
        for(int j=0;j<5;j++){
            int m= j-b;
            while(m<0){
                m=m+n;
            }
            if(input[i][a_inverse*m%n]=='\\'){
            continue;
            }
            else if(input[i][a_inverse*m%n]=='-')
            fprintf(fp2,"\n");
            else{
            fprintf(fp2,"%c", input[i][a_inverse*m%n]);
            }
        }
        i++;
    }
}

int inverse(int a,int n){
    int i=0;
    while(1){
       if((n*i+1)%a==0) 
       return (n*i+1)/a;
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
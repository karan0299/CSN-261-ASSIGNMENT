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

void decrypt(char **input,int a_inverse,int b,int n,int r,FILE* fp2);
int inverse(int a,int n);


void main(int argc, char** argv) {
    int n = atoi(argv[1]);
    int a = atoi(argv[2]);
    int b = atoi(argv[3]);
    
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
      printf("%s",input[i]);
      i++;

    }
    
    int a_inverse = inverse(a,n);
    printf("%d",a_inverse);
    FILE * fp2 = fopen("decryptedoutputfile.txt","w");
    
    decrypt(input,a_inverse,b,n,i,fp2);

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
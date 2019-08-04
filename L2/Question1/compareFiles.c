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

void compareFiles(FILE *fp1, FILE *fp2) 
{ 

    char ch1 = getc(fp1); 
    char ch2 = getc(fp2); 
  
    int error = 0, pos = 0;
  
    while (ch1 != EOF && ch2 != EOF) 
    { 
        pos++;  

        if (ch1 != ch2) 
        { 
            error++; 
            printf("Error"
               " Position : %d \n", pos); 
        } 
  
        ch1 = getc(fp1); 
        ch2 = getc(fp2); 
    } 
  
    printf("Total Errors detected: %d\t", error); 
} 
  

void main() 
{ 

    FILE *fp1 = fopen("inputfile.txt", "r"); 
    FILE *fp2 = fopen("decryptedoutputfile.txt", "r"); 
  
    if (fp1 == NULL || fp2 == NULL) 
    { 
       printf("Error : Files not open"); 
       exit(0); 
    } 
  
    compareFiles(fp1, fp2); 
  
    fclose(fp1); 
    fclose(fp2); 
 
}
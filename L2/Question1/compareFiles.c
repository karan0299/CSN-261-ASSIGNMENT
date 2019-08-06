/** 
*@file compareFiles.c
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
*This method will be used to check if two files are equivalent or not
*@author Karanpreet Singh
*@param fp1 Pointer to original input file
*@param fp2 Pointer to decryptedoutputFile
*@date 04/08/19
*/

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
     /// to mark start and end of cpu clock
    clock_t start, end;
    /// store the time taken by cpu to perform operation 
    double cpu_time;

    start = clock ();
    /// Pointer to original input file
    FILE *fp1 = fopen("inputfile.txt", "r"); 

    /// Pointer to decryptedoutputFile
    FILE *fp2 = fopen("decryptedoutputfile.txt", "r"); 
  
    if (fp1 == NULL || fp2 == NULL) 
    { 
       printf("Error : Files not open"); 
       exit(0); 
    } 
  
    compareFiles(fp1, fp2); 
    
    fclose(fp1); 
    fclose(fp2); 

    end = clock();
    
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\nTotal CPU time taken is %f \n",cpu_time);
 
}
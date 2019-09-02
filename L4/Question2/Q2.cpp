/** 
*@file Q2.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 02/09/19
*/
#include <iostream>
#include <cstring>
#include <chrono>
using namespace std;
using namespace std::chrono; 

/// keep the count of all possible solutions
int count= 0;

/**
*This method will be used to check if a queen can be placed on arr[row][col]
*@author Karanpreet Singh
*@param arr pointer to the array that respresents the board
*@param row gives the row
*@param col gives the column
*@param N gives the size of the baord
*@date 02/09/19
*/
bool checkSafe(int** arr, int row, int col, int N)
{
	for (int i = 0; i < row; i++)
		if (arr[i][col] == 1)
			return false;

	for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
		if (arr[i][j] == 1)
			return false;

	for (int i = row, j = col; i >= 0 && j < N; i--, j++)
		if (arr[i][j] == 1)
			return false;

	return true;
}

/**
*This method is recursive utility function to solve N Queen problem 
*@author Karanpreet Singh
*@param arr pointer to the array that respresents the board
*@param row gives the row
*@param N gives the size of the baord
*@date 02/09/19
*/
void nQueen(int** arr, int row, int N)
{
	if (row == N)
	{
        count++;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++)
				cout << arr[i][j] << " ";
			cout << endl;
		}
		cout << endl;
		
		return;
	}

	for (int i = 0; i < N; i++) 
	{
		if (checkSafe(arr, row, i,N)) 
		{
			arr[row][i] = 1;

			nQueen(arr, row + 1,N);

			arr[row][i] = 0;
		}
	}
}

int main()
{

    int N;
    cout<<"Enter the value of n"<<endl;
    cin>>N;

	auto start = high_resolution_clock::now();

	int** a = new int*[N];
    for(int i = 0; i < N; ++i)
    a[i] = new int[N];

	nQueen(a, 0,N);

    cout<<"Total number of possible solutions are "<<count<<endl;

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "CPU Time taken"<< duration.count() << " microseconds" << endl;
	return 0;
}
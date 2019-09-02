/** 
*@file Q3.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 2/09/19
*/
#include <bits/stdc++.h> 
#include <chrono>
using namespace std; 
using namespace std::chrono; 

/// stores the higher index of the longest subarray
int high=-1;

/// stores the lower index of longest subarray
int low=-1;

/**
*This method is used to get longest subarray having given sum
*@author Karanpreet Singh
*@param numbers vector containing the array elements
*@param n number of elements int the array
*@param sum given sum
*@date 02/09/19
*/
int getLongestSubarray(vector<int> numbers ,int n, int sum) 
{ 
	unordered_map<int, int>  map_sum_index; 
	int cummu_sum = 0, maximumLength = 0; 

	for (int i = 0; i < n; i++) { 

		cummu_sum += numbers.at(i); 

		if (cummu_sum == sum){ 
			maximumLength = i + 1;
			low=0;
			high=i; 
		}

		if (map_sum_index.find(cummu_sum) == map_sum_index.end()) 
			map_sum_index[cummu_sum] = i; 
 
		if (map_sum_index.find(cummu_sum - sum) != map_sum_index.end()) { 
			if (maximumLength < (i - map_sum_index[cummu_sum - sum])){ 
				maximumLength = i - map_sum_index[cummu_sum - sum];
				low=map_sum_index[cummu_sum - sum]+1;
				high=i; 
			}
		} 
	} 

	return maximumLength; 
} 

int main() 
{ 
	int n;
    cout<<"Enter the value of N";
    cin>>n;
    vector<int> numbers;
    cout<<"Enter the array values\n";
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        numbers.push_back(num);
    }
	int sum;
    cout<<"Enter the value of sum\n"; 
	cin>>sum;

	auto start = high_resolution_clock::now();

	int length = getLongestSubarray(numbers, n, sum);
	if(length==0){
		cout<<"Not found\n";
	}
	else {
		cout<<"length of longest subarray is "<<length<<endl;
		cout<<"index from "<<low<<" to "<<high<<endl;
	}

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "CPU Time taken"<< duration.count() << " microseconds" << endl;
	return 0; 
} 

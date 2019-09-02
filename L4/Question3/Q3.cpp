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
using namespace std; 

int high=-1;
int low=-1;

int getLongestSubarray(vector<int> numbers ,int n, int k) 
{ 
	unordered_map<int, int>  map_sum_index; 
	int cummu_sum = 0, maximumLength = 0; 

	for (int i = 0; i < n; i++) { 

		cummu_sum += numbers.at(i); 

		if (cummu_sum == k){ 
			maximumLength = i + 1;
			low=0;
			high=i; 
		}

		if (map_sum_index.find(cummu_sum) == map_sum_index.end()) 
			map_sum_index[cummu_sum] = i; 
 
		if (map_sum_index.find(cummu_sum - k) != map_sum_index.end()) { 
			if (maximumLength < (i - map_sum_index[cummu_sum - k])){ 
				maximumLength = i - map_sum_index[cummu_sum - k];
				low=map_sum_index[cummu_sum - k]+1;
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
	int length = getLongestSubarray(numbers, n, sum);
	if(length==0){
		cout<<"Not found\n";
	}
	else {
		cout<<"length of longest subarray is "<<length<<endl;
		cout<<"index from "<<low<<" to "<<high<<endl;
	}
	return 0; 
} 

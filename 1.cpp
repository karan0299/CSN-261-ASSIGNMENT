/** 
*@file 1.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Leshna Balara
*/

#include <bits/stdc++.h>
using namespace std;


struct node
{
	node *right,*next;
	int value;
};



node *xorlist;
void print(){

	node* temp1 = xorlist,*temp2;
	cout << endl << "Print Linkedlist" << endl;
	while(temp1!=NULL){
		cout << temp1->value << " -> ";
		temp2 = temp1->right;
		while(temp2!=NULL){
			cout << temp2->value << " ";
			temp2 = temp2->right;
		}
		temp1 = temp1->next;
		cout << endl;
	}
}

node * insert1(int totalxor,int i){

	node *temp1=xorlist,*snode;
	while(temp1!=NULL){
		if (temp1->value == totalxor)
		{
			snode=temp1;
			break;
		}

		if (temp1->next ==NULL)
		{
			temp1->next = new node();
			temp1 = temp1->next;
			temp1->value = totalxor;
			snode = temp1;
			break;
		}

		if (temp1->next->value > totalxor)
		{
			node *temp = new node();
			temp->value = totalxor;
			temp->next = temp1->next;
			temp1->next = temp;
			snode = temp;
			break;
		}
		temp1 = temp1->next;
	}

	node *lst = snode;

	while(lst->right != NULL)
		lst = lst->right;

	lst->right = new node();
	lst = lst->right;
	lst->value = i;
	return snode;
}

int findMax(node *f){

	int val = f->value;

	while(f!=NULL){
		val = max(val,f->value);
		f = f->right;
	}
	return val;
}

int main(){

	int n;
	cin >> n;
	int totalxor = 0;
	
	node *v,*cv;
	v = new node();
	cv = v;	
	
	xorlist = new node();
	xorlist->value = 0;
	xorlist->right = new node();
	xorlist->right->value = -1;

	node * snodes[n];

	for ( i = 0; i < n; ++i)
	{
		int p;
		cin >> p;
		totalxor = totalxor^p;
		cv->value = p;
		cv->next = new node();
		cv = cv->next;
		snodes[i] = insert1(totalxor,i);
	}	

	int answer = 0;

	node* temp1 = xorlist,*temp2;
	while(temp1!=NULL){
		temp2 = temp1->right;
		int sum1 = temp2->value;
		temp2 = temp2->right;
		int j=1;
		while(temp2!=NULL){
			answer += (  (temp2->value)*j - sum1 - j);
			sum1 += temp2->value;
			temp2 = temp2->right;
			j++;
		}
		temp1 = temp1->next;
	}
	cout << answer << endl;
	temp1 = xorlist;
	temp2 = temp1->right;
	temp1->right = temp2->right;
	node * temp3=temp2->right;
	int maxno,ff,ll1;
	if (temp3!=NULL)
	{
		maxno = findMax(temp3);
		ff = temp2->value+1,ll1 = temp3->value;
		for (int i1 = ff+1; i1 <= maxno; ++i1)
		{
			temp3 = temp2->right;
			while(temp3!=NULL){
				if (temp3->value >= i1)
				{
					cout << "(" << ff+1 << "," << i1+1 << "," << temp3->value+1 << ")" << endl;
				}
				temp3=temp3->right;
			} 
		}
	}

	

	for (int i = 0; i < n; ++i)
	{
		temp1 = snodes[i];
		temp2 = temp1->right;
		temp1->right = temp2->right;
		temp3 = temp2->right;

		if (temp3==NULL)
		{
			continue;
		}

		int maxno = findMax(temp3);
		int ff = temp2->value+1,ll1 = temp3->value;
		for (int i1 = ff+1; i1 <= maxno; ++i1)
		{
			temp3 = temp2->right;
			while(temp3!=NULL){
				if (temp3->value >= i1)
				{
					cout << "(" << ff+1 << "," << i1+1 << "," << temp3->value+1 << ")" << endl;
				}
				temp3=temp3->right;
			} 
		}
	}

	return 0;
}
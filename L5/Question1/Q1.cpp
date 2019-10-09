/** 
*@file Q1.cpp
*@brief this  file will contain all required 
*definitions and basic utilities functions.
*
*@author Karanpreet Singh
*
*@date 29/09/19
*/

#include <iostream> 
#include <iterator> 
#include <map> 
  
using namespace std;

 //! function to implement mutiplication and addition
        /*!
        \param  pow_cof1 mapping for polynomial one
        \param  pow_cof2 mapping for polynomial two
        */
void menu(map<int,int> pow_cof1,map<int,int> pow_cof2){
    int opt=1;
    while(opt==1||opt==2){
        cout<<"Enter 1 for multiplication , 2 for Addition "<<endl;
        cin>>opt;
        switch (opt) {
            case 1 : {
                map<int,int> pow_cof_mul;
                for (auto itr = pow_cof1.begin(); itr != pow_cof1.end(); itr++) {
                    int pow1 = itr->first;
                    int cof1 = itr->second;
                    for (auto itr2 = pow_cof2.begin(); itr2 != pow_cof2.end(); itr2++){
                        int pow2 = itr2->first;
                        int powr= pow1+pow2;
                        int cof2 = itr2->second;
                        int cofr = cof1*cof2;
                        if(pow_cof_mul.find(powr)==pow_cof_mul.end()){
                            pow_cof_mul[powr] = cofr;
                        }
                        else {
                            pow_cof_mul[powr] = pow_cof_mul.at(powr) + cofr;
                        }
                    }
                }
                 cout<<"Cofficient"<<"\t"<<"Power"<<endl;
                for(auto itr = pow_cof_mul.begin(); itr != pow_cof_mul.end();itr++){
                    cout<<itr->second<<"\t\t"<<itr->first<<endl;
                }
                break;
            } 

        case 2:{  
                map<int,int> pow_cof_add;
                for (auto itr = pow_cof1.begin(); itr != pow_cof1.end(); itr++) { 
                    int pow = itr->first;
                    int cof = itr->second;
                    pow_cof_add[pow] = cof;
                }
                for (auto itr = pow_cof2.begin(); itr != pow_cof2.end(); itr++) { 
                    int pow = itr->first;
                    int cof = itr->second;
                    if(pow_cof_add.find(pow)==pow_cof_add.end()){
                        pow_cof_add[pow] = cof;
                    }
                    else {
                        pow_cof_add[pow] = pow_cof_add.at(pow) + cof;
                    }
                }
                cout<<"Cofficient"<<"\t"<<"Power"<<endl;
                for(auto itr =pow_cof_add.begin(); itr != pow_cof_add.end();itr++){
                    cout<<itr->second<<"\t\t"<<itr->first<<endl;
                }
                break;
        }
            defaut: exit(1);
        }

        cout<<"--------------------------------------------------------------------------"<<endl;
    }
}
  
int main() 
{ 
    cout<<"Enter number of terms in expression1\n";
    int n1;//! number of terms in expression1
    cin>>n1;
    map<int,int> pow_cof1;//!  mapping from power to cofficients for polynomial one
    cout<<"Cofficient	Power"<<endl;
    for(int i=0;i<n1;i++){
        int pow;
   
        int cof;
        cin>>cof;
        cin>>pow;
        pow_cof1[pow]=cof;
    }

    cout<<"Enter number of terms in expression2\n";
    int n2;//!  number of terms in expression 2
    cin>>n2;//! mapping from power to cofficients for polynomial 2
    cout<<"Cofficient	Power"<<endl;
    map<int,int> pow_cof2;
    for(int i=0;i<n2;i++){
        int pow;
        int cof;
        cin>>cof;
        cin>>pow;
        pow_cof2[pow]=cof;
    }

    menu(pow_cof1,pow_cof2);

    return 0;
}

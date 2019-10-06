/*
 * Driver.cpp
 *
 *  Created on: ??�/??�/????
 *      Author: ENG.HamaDa
 */

#include <iostream>
#include "ChainHashTable.h"


using namespace std;

unsigned int hasing(const int &data ,  unsigned int &size) {
    return (int) data%size;
}

int main(){
	ChainHashTable<int> ahmed(hasing , 10);
	ahmed.insert(15);

	vector<int> a;
	cout<<ahmed.insert(5)<<endl;
	cout<<ahmed.insert(1)<<endl;
	cout<<ahmed.insert(2)<<endl;
	cout<<ahmed.insert(12)<<endl;
	ChainHashTable<int> ra(ahmed);


	ahmed.dump();
	ra.dump();
	cout<<"assign operator"<<endl;
	ChainHashTable<int> f(hasing , 12);
	f=ahmed;
	f.dump();


	return 0;
}

#include "Vector_HM.h"
#include <iostream>
int main() 
{

	Vector_HM<int> a;
	
	a.push_back(7);

	cout << a.at(0);
	  
	Vector_HM<int> b(5,25 );
	  
	 
	a = b;
	
	for (auto i : a)
		cout << i << ' ';
	
	//checked !	

	a.emplace_back(23);
	
	for (auto i : a)
		cout << i << ' ';

	auto it = a.emplace(a.begin() + 1, 100);

	cout << endl;
	for (auto i : a)
		cout << i << ' ';


	// move semantics - checked !	





	return 0;

}
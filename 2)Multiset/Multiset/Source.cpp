#include <limits>
#include <iostream>
#include <vector>
#include "MultiSet.h"
int main()
{
	/*
	
	std::cout << "LAB #2 wizard greets you !\n";
	StatMultiSet<int> m1;

	m1.addNum(2);
	m1.showAll();

	StatMultiSet<int> m2;

	 
	std::vector<int> somedata;somedata.push_back(4),somedata.push_back(11),somedata.push_back(60);


	
	try {
		m2.addNum(somedata);
	 // dialog window!!!1 + choice    m2.addNum("abc");
	}
	catch (const std::invalid_argument& ia) {
		std::cerr << "Invalid argument: " << ia.what() << '\n';
	}
	
	

	m2.showAll();
	
	std::cout << m2.getAvg();


	m2.addNum(10);
	m2.showAll();

	std::cout << m2.CountLower(88)<< "\n";

	std::cout << m2.CountAbove(85) << "\n";
	std::cout << m2.CountAbove(85) << "\n";

	/*
	std::string s;
	std::cin >> s;
	if (s.compare("int") != 0)
		std::cout << "IIINNNTTT\n";

		*/
	execute();
	 
}
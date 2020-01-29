#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility> 
#include <algorithm>
#include <omp.h>
using namespace std;

class Factor {
public:
	Factor(uint64_t  number);
	void Blend();
	 
	string Get();
	bool is_done();
private:
	vector<uint64_t> primes;
	 string outp;
	uint64_t number;
	bool done;
};
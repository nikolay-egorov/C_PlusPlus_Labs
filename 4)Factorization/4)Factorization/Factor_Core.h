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
	void Blend(uint64_t n);

	void Read_From(string in, string out);
	void Add(uint64_t number);
	void Get(uint64_t number);
	bool is_done();
private:
	vector<uint64_t> last_factoring;
	vector<pair<uint64_t, uint64_t>> temp_ans;
	map <uint64_t, vector<uint64_t>> FMap;
	ifstream fin;
	ofstream fout;
	bool done;
};
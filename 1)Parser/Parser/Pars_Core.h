#pragma once
#include <fstream>
#include <iostream>
#include <string> 
#include <map>
#include <utility>

using namespace std;

class Pars_Core
{
public:
	Pars_Core(const string& f_name);
	~Pars_Core();
	bool section_true(const char* section_name) const;
	bool param_true(const char * section_name, const char * par_name) const;



	void Init();
	int GetValue_i(const char* section, const char* par) const;
	double GetValue_d(const char* section, const char* par) const; 
	string GetValue_s(const char* section, const char* par) const;
	void Print() const;
	void Raise();




private:
	multimap<string, pair <string, string>> IniPar;
	string f_name;

};

void execute();
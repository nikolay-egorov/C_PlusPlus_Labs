#include "Factor_Core.h"
#include "EXCP_BAD_Args.h"
#include "EXCP_NO_FILE.h"



 

void Factor::Blend(uint64_t n)
{
	/*
	for ( uint64_t i = 2; i*i <= number; i++) {
		if (number % i == 0) {
			temp_ans.push_back(make_pair(0, i));
			while (number % i == 0) {
				number /= i;
				temp_ans[temp_ans.size() - 1].first--;
				 
			}
		}
	}
	if (number > 1) {
		temp_ans.push_back(make_pair(-1, number));
	}
	sort(temp_ans.begin(), temp_ans.end());

	*/

	uint64_t tmp = n;
	while (n % 2 == 0)
	{
		last_factoring.push_back(2);
		n >>= 1;
	}
	for (int i = 3; i <= sqrt(n); i = i + 2)
	{

		while (n%i == 0)
		{
			last_factoring.push_back(i);
			n = n / i;
		}
	}
	if (n > 2)
		last_factoring.push_back(n);

	done = true;

}

void Factor::Read_From(string in, string out)
{
	 
	uint64_t number;
	fin.open(in);
	fout.open(out);
	

		if (fin.good()) {
			while (fin >> number) {
	
				Blend(number);

				Add(number);
				Get(number);
				
			}
			fin.close();
			fout.close();
		}
	else
		throw EXCP_NO_FILE();
	 

}

void Factor::Add(uint64_t number)
{
	 
	//GMap.insert(make_pair(number, temp_ans));
	FMap.insert(make_pair(number, last_factoring));
	last_factoring.clear();
}

void Factor::Get(uint64_t number)
{
	fout << "Factorization of " << number << " is: ";
	int i;
	for (i = 0; i < (FMap[number].size() - 1); i++)
		fout << FMap[number][i] << " * ";
	fout << FMap[number][i];
	fout << endl;
	 
}

bool Factor::is_done()
{
	return done;
}



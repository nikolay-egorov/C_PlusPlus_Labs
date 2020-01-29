#include "Factor.h"

 
Factor::Factor(uint64_t number)
{
	this->number = number;

}

void Factor::Blend()
{
	uint64_t tmp = number;
	while (tmp % 2 == 0)
	{
		primes.push_back(2);
		tmp >>= 1;
	}
	for (int i = 3; i <= sqrt(tmp); i = i + 2)
	{

		while (tmp%i == 0)
		{
			primes.push_back(i);
			tmp = tmp / i;
		}
	}
	if (tmp > 2)
		primes.push_back(tmp);
	
	done = true;

	 

}

string Factor::Get()
{
	 
	if (number == 0)
		return outp = "0 = 0";
	string log = to_string(number) + " = ";
	//refacto
	auto size = primes.size();
	for (uint32_t i = 0; i < size; ++i) {
		log += std::to_string(primes[i])  + (i == size - 1 ? "" : " * ");
	}
	
	return log;
}

bool Factor::is_done()
{
	return done;
}

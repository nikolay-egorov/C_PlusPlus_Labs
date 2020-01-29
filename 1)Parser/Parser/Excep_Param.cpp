#include "Excep_Param.h"





void Excep_Param::bad_par(const string section_name, const string parameter)
{
	cout << "Couple " << section_name << " - " << parameter << " is not existing in this world\n";
}



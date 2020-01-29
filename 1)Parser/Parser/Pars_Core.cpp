#include "Pars_Core.h"
#include "Excep_Param.h"
#include "EXCPN_f_format.h"
#include "EXCPN_no_File.h"

Pars_Core::Pars_Core(const string& f_name)
{
	this->f_name = f_name;

}


Pars_Core::~Pars_Core()
{


}

bool Pars_Core::section_true(const char * section_name) const
{
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();
	while (it != IniPar.end()) {
		if (it->first == section_name) return true;
		else
			++it;
	}
	return (false);
}

bool Pars_Core::param_true(const char * section_name,const char * par_name) const
{
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();
	while (it != IniPar.end()) {
		if (it->first == section_name && it->second.first == par_name) return true;
		else 
			++it;

	}
	return false;
}

void Pars_Core::Init()
{
	ifstream file(f_name, std::ifstream::in);
	string str, str_name_section, name_par, par, ras;
	pair <string, string> parametr;
	while (getline(file, str)) {
		if (str[0] == '[') {
			str_name_section = str;
			str_name_section.erase(str_name_section.begin() + 0);
			str_name_section.erase(str_name_section.end() - 1);
		}
		else {
			if ((((str[0] >= 0) && (str[0] <= 9)) || ((str[0] >= 'A') && (str[0] <= 'Z')) || ((str[0] >= 'a') && (str[0] <= 'z')))) {
				int i = 0;
				name_par = "";
				par = "";
				while ((str[i] != '=') && (i < str.length()) && (str[i] != 32)) {
					name_par = name_par + str[i];
					i++;
				}
				while (((str[i] == 32) || (str[i] == '=')) && (i < str.length())) {
					i++;
				}
				while ((str[i] != ';') && (i < str.length()) && (str[i] != 32)) {
					par = par + str[i];
					i++;
				}
			}
		}
		if ((name_par != "") && (par != "")) {
			parametr.first = name_par;
			parametr.second = par;
			IniPar.insert(make_pair(str_name_section, parametr));
			name_par = "";
			par = "";
		}
	}
	Print();
	Raise();





}

int Pars_Core::GetValue_i(const char * section, const char * par) const
{
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();
	string str = "";
	if ((section_true(section) == false) || (param_true(section, par) == false))
		throw Excep_Param();
	else {
		while (it != IniPar.end()) {
			if ((it->first == section) && ((it->second).first == par)) {
				str = (it->second).second;
				int s_treasure = atoi(str.c_str());
				return (s_treasure);
			}
			else
				++it;
		}
	}
}

double Pars_Core::GetValue_d(const char * section, const char * par) const
{
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();
	string str = "";
	if ((section_true(section) == false) || (param_true(section, par) == false))
		throw Excep_Param();
	else {
		while (it != IniPar.end()) {
			if ((it->first == section) && ((it->second).first == par)) {
				str = (it->second).second;
				double d_treasure = atof(str.c_str());
				return (d_treasure);
			}
			else
				++it;
		}
	}
}

string Pars_Core::GetValue_s(const char * section, const char * par) const
{
	
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();
	string str = "";
	if ((section_true(section) == false) || (param_true(section, par) == false))
		throw Excep_Param();
	else {
		while (it != IniPar.end()) {
			if ((it->first == section) && ((it->second).first == par)) {
				str = (it->second).second;
				return (str);
			}
			else
				++it;
		}
	}

}

void Pars_Core::Print() const
{
	multimap <string, pair <string, string>>::const_iterator it = IniPar.begin();

	cout << "Section\t" << "Parameter - " << "Value " << endl;

	while (it != IniPar.end()) {
		cout << it->first << "\t" << (it->second).first << " - " << (it->second).second << endl;
		++it;
	}

}

void Pars_Core::Raise()
{
	cout << "Choose your destiny,mortal ! \n\n1) Get integer value\n2) Get double value\n3) Get string value\n4) Exit\n";
	int choose;
	string section, parameter;
	bool on = true;
	while (on) {
		cout << "Choice = ";
		cin >> choose;
		switch (choose) {
		case 1: {
			cout << "Enter section and parameter to proceed ";
			cin >> section >> parameter;
			try {
				cout << GetValue_i(section.c_str(), parameter.c_str()) << endl;
			}
			catch (Excep_Param Para) {
				Para.bad_par(section, parameter);
			}
			break;
		}
		case 2: {
			cout << "Enter section and parameter to proceed ";
			cin >> section >> parameter;
			try {
				cout << GetValue_d(section.c_str(), parameter.c_str()) << endl;
			}
			catch (Excep_Param Para) {
				Para.bad_par(section, parameter);
			}
			break;
		}
		case 3: {
			cout << "Enter section and parameter to proceed ";
			cin >> section >> parameter;
			try {
				cout << GetValue_s(section.c_str(), parameter.c_str()) << endl;
			}
			catch (Excep_Param Para) {
				Para.bad_par(section, parameter);
			}
			break;
		}
		case 4: {
			on = false;
			break;
		}
		}
	}




}

void execute()
{
	string str_file_name, name_sect, name_par, f_format;
	int fg = 1;
	while (fg == 1) {
		cout << "Please enter the file name (e.g. - input_files\\03.ini) - ";
		cin >> str_file_name;
		try {
			f_format = str_file_name.substr(str_file_name.length() - 3, 3);
			if (f_format != "ini")
				throw EXCPN_f_format();
			else {
				ifstream file(str_file_name, std::ifstream::in);
				if (file.good()) {
					fg = 0;
					Pars_Core parser = Pars_Core(str_file_name);
					parser.Init();
				}
				else
					throw EXCPN_no_File();
			}
		}
		catch (EXCPN_f_format BF) {
			BF.bad_format();
		}
		catch (EXCPN_no_File NF) {
			NF.miss(str_file_name);
		}
	}


}

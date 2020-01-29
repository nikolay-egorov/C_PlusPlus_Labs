#include "MultiSet.h"
#include "EXCP_f.h"
void execute() {
	
	std::string section;
	
	bool on = true;



	while (on) {
		
		std::cout<<"Welcome to Lab 2 world!\nType in data format would you like to use (e.g. - int||float||double)\n\n";
		std::cin >> section;

		try {
			if ((section.compare("integer") == 0) || (section.compare("int") == 0)) {
				on = false;
					StatMultiSet<int> a;
					a.Raise();

			}
				
			else if (section.compare("float") == 0){
				on = false;
				StatMultiSet<float> a; a.Raise();
				}
					
			else if (section.compare("double") == 0) {
				on = false;
				StatMultiSet<double> a; a.Raise();
			}
			else {
				throw Excep_f();
			}
				
			  
			}

		catch (Excep_f F_F) {
			F_F.bad_f();
			
		}


		}

		
		 
	  //  std::system("cls");
	}















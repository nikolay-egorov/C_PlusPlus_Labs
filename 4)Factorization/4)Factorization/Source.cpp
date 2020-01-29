#include "Factor_Core.h"
#include "EXCP_BAD_Args.h"
#include "EXCP_NO_FILE.h"



int main( ) {
	Factor F;
	string in, out;
	cin >> in >> out;
	try {
		F.Read_From(in,out);
	}
	catch (EXCP_NO_FILE File) {
		File.not_found();
	}
	catch (EXCP_BAD_Args Arg) {
		Arg.bad();
	}
	return 0;
}
#include "EXCPN_NO_FILE.h"
#include "Thread_pool.h"


int main() {
	
	string in = "b.txt", out = "out.txt";
	int n = 5;
	//	cin>> n;
	try {
		Thread_pool F(in, out, n);
	}
	catch (EXCPN_NO_FILE Mind) {
		Mind.not_found();
	}

	return 0;
}
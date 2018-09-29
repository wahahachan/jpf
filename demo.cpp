#include <iostream>

#include "jpf/jpf.h"

using namespace std;

int main() {
	
	cout << jpf::jsnprintf(50, "Hello %s\n", "World");
	cout << jpf::jsnprintf(62, "%60s\n", "Use whatever formating string that you get used to!");

	
	string BobsInfo = jpf::jsnprintf(500, "Name\t: %s\nAge\t: %2d\nIncome\t: $%9.2f",
								"Bob", 		// He is a friend of Alice
								30, 		// Get older and older 
								23456.78901 // A long floating number
								);

	cout << BobsInfo << endl;

	return 0;
}

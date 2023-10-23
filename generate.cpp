// Connor McKenna
// (CECS 325-01)
// Program 4 - Sorting Contest using pThreads
// Due Date (10/23/2023)
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.

#include <iostream>
#include <fstream>
#include <string>

using std::cout;
using std::endl; 
using std::stoi;
using std::ofstream;
using std::ios;

int main(int argc, char *argv[]){
	
	if (argc < 4) {
		cout << "Please enter only 3 parameters:" << endl;
		cout << "P1: Total count of numbers." << endl;
		cout << "P2: Minimum Value." <<endl;
		cout << "P3: Maximum Value." << endl;
		cout << "Ex: %generate 10000000 1000000 999999"<< endl;
	        exit(EXIT_SUCCESS);	
	}
	
	for (int i = 0; i < argc; i++) {
		cout << "argv[" << i << "]:" <<  argv[i] << endl;
	}

	int count = stoi(argv[1]);
	int min   = stoi(argv[2]);
	int max   = stoi(argv[3]);

	ofstream fileOut;
	srand(time(NULL));
	fileOut.open("numbers.dat", ios::out | ios::trunc);
	for(int i =0; i < count; i++) {
		fileOut << (rand() % (max - min + 1) + min) << endl;
	}
	fileOut.close();
	return 0;
}


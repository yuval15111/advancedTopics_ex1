#include <iostream>
#include <fstream>
#include "FileHandler.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Error";
	}
	ifstream mazeFileInput(argv[1]);
	
	if (!mazeFileInput.good()) {
		cout << "Error opening file." << endl;

		// Should replace with define EXIT_FAILURE
		return -1;
	}
	ofstream mazeFileOutput(argv[2]);
}

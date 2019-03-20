#include "MainAux.h"
#include "FileHandler.h"

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Error";
	}
	ifstream inputFileStream(argv[1]);
	
	if (!inputFileStream.good()) {
		cout << "Error opening file." << endl;
		// Should replace with define EXIT_FAILURE
		return -1;
	}
	ofstream outputFileStream(argv[2]);
	FileHandler fileH(inputFileStream, outputFileStream);
	Maze * maze = fileH.parseInput();
	maze->printBoard();
	int x = 3;
}

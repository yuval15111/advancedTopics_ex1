//#include "MainAux.h"
#include "FileHandler.h"

int main(int argc, char* argv[]) {
	FileHandler fileH(argc, argv);
	
	Maze * maze = fileH.parseInput();
	maze->printBoard();
	int x = 3;
}

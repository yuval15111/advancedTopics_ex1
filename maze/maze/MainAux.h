#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Maze.h"
class MainAux {
	inline void printWinMessage() { cout << "Succeeded in " << numOfSteps << " steps" << endl; };
	inline void printLostMessage() { cout << "Failed to solve maze in " << numOfSteps << " steps" << endl; };
};

#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Maze.h"

using namespace std;

class FileHandler {
private:
	ifstream& m_fin;
	ofstream& m_fout;
public:
	FileHandler(ifstream& fin, ofstream& fout) : m_fin(fin), m_fout(fout) {};
	~FileHandler();
	Maze parseInput();

	string getName(ifstream & fin, string line);

	int getMaxSteps(ifstream & fin, string line);

	int getRowsNum(ifstream & fin, string line);

	int getColsNum(ifstream & fin, string line);

	MazeBoard getBoard(ifstream & fin, string line);

};
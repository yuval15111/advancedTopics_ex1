#include <cstdlib>
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

	int getIntValue(ifstream & fin, string line, const char * input);

	vector<string> split(string str, char delimiter);

	MazeBoard getBoard(ifstream & fin, string line, int rows, int cols);

};
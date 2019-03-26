#include "MainAux.h"
#include <regex>

using namespace std;



class FileHandler {
private:
	ifstream& m_fin;
	ofstream& m_fout;
public:
	FileHandler(ifstream& fin, ofstream& fout) : m_fin(fin), m_fout(fout) {};
	~FileHandler();
	Maze * parseInput();

	string getName(ifstream & fin);

	size_t getIntValue(ifstream & fin, const char * input);

	vector<string> split(string str, char delimiter);

	MazeBoard getBoard(ifstream & fin, size_t rows, size_t cols, size_t playerLocation[2], ParsingErrorType * error);

};
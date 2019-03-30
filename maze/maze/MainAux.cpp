#include "MainAux.h"

void Coord::set(size_t i, size_t j) {
	row = i;
	col = j;
}

bool operator<(const Coord& a, const Coord& b)
{
	if (a.row < b.row) return true;
	else if (a.row == b.row) return a.col < b.col;
	else return false;
}

Action operator!(const Action& a) {
	switch (a) {
	case Action::UP:
		return Action::DOWN;
	case Action::DOWN:
		return Action::UP;
	case Action::LEFT:
		return Action::RIGHT;
	case Action::RIGHT:
		return Action::LEFT;
	default:
		return a;
	}
}


void printWinMessage(const int numOfSteps) { 
	cout << "Succeeded in " << numOfSteps << " steps" << endl; 
}

void printLostMessage(const int numOfSteps) { 
	cout << "Failed to solve maze in " << numOfSteps << " steps" << endl;
}

void handleMissingInputError() {
	cout << "Missing maze file argument in command line" << endl;
}

void handleMissingOutputError() {
	cout << "Missing output file argument in command line" << endl;
}

void handleBadInputAddressError(const string & str)
{
	cout << "Command line argument for maze: " << str << " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
}

void handleBadOutputAddressError(const string & str)
{
	cout << "Command line argument for output file: " << str << " points to a bad path or to a file that already exists" << endl;
}

void handleMaxStepsError(const string & str)
{
	cout << "expected in line 2 - MaxSteps = <num>" << endl;
	cout << "got : " << str << endl;
}

void handleRowsError(const string & str)
{
	cout << "expected in line 3 - Rows = <num>" << endl;
	cout << "got : " << str << endl;
}

void handleColsError(const string & str)
{
	cout << "expected in line 4 - Cols = <num>" << endl;
	cout << "got : " << str << endl;
}

void handleMissingPlayerCharError(const string & str)
{
	cout << "Missing @ in maze" << endl;
}

void handleMissingEndCharError(const string & str)
{
	cout << "Missing $ in maze" << endl;
}

void handleMoreThanOnePlayerCharError(const string & str)
{
	cout << "More than one @ in maze" << endl;
}

void handleMoreThanOneEndCharError(const string & str)
{
	cout << "More than one $ in maze" << endl;
}

void handleWrongCharError(const string & str)
{
	if (str[0] == 9)
		cout << "Wrong character in maze: TAB in row " << (int)str[1] << ", col " << (int)str[2] << endl;
	else
		cout << "Wrong character in maze: " << str[0] << " in row " << (int)str[1] << ", col " << (int)str[2] << endl;
}

bool checkErrors(Errors & e) {
	bool noErrors = e.list.size() == 0;
	for (ErrorList::iterator it = e.list.begin(); it != e.list.end(); ++it) {
		Func f = e.fmap[it->first];
		string str = it->second;
		f(str);
	}
	e.list.clear();
	return noErrors;
}


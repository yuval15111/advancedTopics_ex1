#include "MainAux.h"

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

void printWinMessage(const size_t numOfSteps) {
	cout << "Succeeded in " << numOfSteps << " steps" << endl; 
}

void printLostMessage(const size_t numOfSteps) {
	cout << "Failed to solve maze in " << numOfSteps << " steps" << endl;
}

void handleMissingInputError(const string * str) {
	cout << "Missing maze file argument in command line" << endl;
}

void handleMissingOutputError(const string * str) {
	cout << "Missing output file argument in command line" << endl;
}

void handleBadInputAddressError(const string * str)
{
	cout << "Command line argument for maze: " << str << " doesn't lead to a maze file or leads to a file that cannot be opened" << endl;
}

void handleBadOutputAddressError(const string * str)
{
	cout << "Command line argument for output file: " << str << " points to a bad path or to a file that already exists" << endl;
}

void handleMaxStepsError(const string * str)
{
	cout << "expected in line 2 - MaxSteps = <num>" << endl;
	cout << "got : " << *str << endl;
}

void handleRowsError(const string * str)
{
	cout << "expected in line 3 - Rows = <num>" << endl;
	cout << "got : " << *str << endl;
}

void handleColsError(const string * str)
{
	cout << "expected in line 4 - Cols = <num>" << endl;
	cout << "got : " << *str << endl;
}

void handleMissingPlayerCharError(const string * str)
{
	cout << "Missing @ in maze" << endl;
}

void handleMissingEndCharError(const string * str)
{
	cout << "Missing $ in maze" << endl;
}

void handleMoreThanOnePlayerCharError(const string * str)
{
	cout << "More than one @ in maze" << endl;
}

void handleMoreThanOneEndCharError(const string * str)
{
	cout << "More than one $ in maze" << endl;
}

void handleWrongCharError(const string * str)
{
	if ((*str)[0] == 9)
		cout << "Wrong character in maze: TAB in row " << (int)(*str)[1] << ", col " << (int)(*str)[2] << endl;
	else
		cout << "Wrong character in maze: " << str[0] << " in row " << (int)(*str)[1] << ", col " << (int)(*str)[2] << endl;
}

vector<string> split(string str, char delimiter) {
	vector<string> v = {};
	size_t currSpaceIndex = 0, lastSpaceIndex = -1;
	while ((currSpaceIndex = str.find(delimiter, lastSpaceIndex + 1)) != std::string::npos) {
		if (currSpaceIndex != 0) {
			v.push_back(str.substr(lastSpaceIndex + 1, currSpaceIndex - lastSpaceIndex - 1));
			lastSpaceIndex = currSpaceIndex;
		}
	}
	v.push_back(str.substr(lastSpaceIndex + 1));
	return v;
}

void updateCoordinate(Coordinate & c, const size_t i, const size_t j) {
	c.first = i;
	c.second = j;
}

#include "FileHandler.h"

int main(int argc, char* argv[]) {
	FileHandler fileH(argc, argv);
	cout << "Finished c'tor" << endl;
	if (!fileH.noErrors()) return EXIT_FAILURE;	// IO Errors - can't parse!
	fileH.parseInput();
	Manager * manager = fileH.getManager();
	vector<char> actionLst = manager->play();
	fileH.pushActionsToOutputFile(actionLst);
}
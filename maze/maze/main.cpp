#include "FileHandler.h"

int main(int argc, char* argv[]) {
	FileHandler fileH(argc, argv);
	if (!fileH.noErrors()) return EXIT_FAILURE;	// IO Errors - can't parse!
	fileH.parseInput();
	Manager * manager = fileH.getManager();
	if (manager == nullptr) return EXIT_FAILURE;	// Parsing Errors - can't parse!
	vector<char> actionLst = manager->play();
	fileH.pushActionsToOutputFile(actionLst);
}
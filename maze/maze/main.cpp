#include "FileHandler.h"

int main(int argc, char* argv[]) {

	/* ================================= FILES VALIDATION AND PARSING ================================= */

	FileHandler fileH(argc, argv);
	if (!fileH.noErrors()) return EXIT_FAILURE;						// IO Errors - can't parse!
	Manager * manager = fileH.parseInput();
	if (manager == nullptr)	return EXIT_FAILURE;					// Parsing Errors - can't play!

	/* ========================================== GAME FLOW ========================================== */

	Player * player = manager->createPlayer();						// PLAYER: LET'S GO!
	for (size_t i = 1; i <= manager->getMaxSteps(); ++i) {
		Action action = player->move();								// PLAYER: THIS IS MY MOVE!
		fileH.pushActionToOutputFile(getActionChar(action));
		if (action == Action::BOOKMARK)	manager->bookmark();
		else {
			manager->execute(action);								// MANAGER: OK, LET ME WRITE THAT DOWN...
			if (manager->playerHitsEndChar()) {
				printWinMessage(i);									// MANAGER: OMG YOU DID IT! I ALWAYS BELIEVED IN YOU
				fileH.pushActionToOutputFile('!');
				return EXIT_SUCCESS;								// PLAYER: YAY!
			}
			if (manager->playerHitsWallChar()) {
				player->hitWall();									// PLAYER: OUCH!!
				manager->execute(action, true); 					// MANAGER: SORRY PAL, TRY AGAIN
			}
			if (manager->playerHitsBookmark()) {					// MANAGER: YOU'RE RIGHT... HERE! <POINTING AT MAP>
				player->hitBookmark();								// PLAYER: OHHH I REMEMBER THAT PLACE!
			}
		}
		manager->printBoard();
	}
	fileH.pushActionToOutputFile('X');
	printLostMessage(manager->getMaxSteps());							// MANAGER: YOU SHOULD TRY HARDER NEXT TIME. CYA!
}
//#include "MainAux.h"
#include "FileHandler.h"
#include "Player.h"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		handleMissingInputError();
	}
	else if (argc == 2) {
		handleMissingOutputError();
	}
	else {
		FileHandler fileH(argv);
		Errors errors = fileH.getErrors();
		if (checkErrors(errors)) {
			Maze * maze = fileH.parseInput();
			if (maze != nullptr) {
				Player * player = new Player();
				for (size_t i = 0; i < maze->m_maxSteps; ++i) {
					Action action = player->move();
					maze->execute(action);
					char c = maze->getCoordValue(maze->getPlayerLocation());
					if (c == END_CHAR) {
						// printWinMessage(i);
						// break;
					}
					if (c == WALL_CHAR) {
						player->hitWall(action);
						maze->execute(action, true); //undo
						// should implement undo for player as well
					}
					//if (maze->getPlayerLocation() == "bookmark" && action != Action::BOOKMARK) {
						// player->hitbookmark();
					//}
					maze->printBoard();
				}
				// We lost in the maze
				//if (!maze->hasReachedDestination()) {
					//printLostMessage(maze->m_maxSteps);
				//}
				//maze->printBoard();
			}
		}
		int x = 3;
	}
}
State checkStateInMaze(Player* player, Maze * maze) {
	 //if (player.m_currentLocation == player.bookmark) return BOOKMARK;
	// else if (maze.currentLocation)
	return State::END;
}

//#include "MainAux.h"
#include "FileHandler.h"
#include "Player.h"

int main(int argc, char* argv[]) {
	FileHandler fileH(argc, argv);
	Maze * maze = fileH.parseInput();
	Player * player = new Player();
	for (size_t i = 0; i < maze->m_maxSteps; ++i) {
		//Action a = player.move();
		if (maze->hasReachedDestination()) {
			printWinMessage(i);
			break;
		}

	}

	// We lost in the maze
	if (!maze->hasReachedDestination()) {
		printLostMessage(maze->m_maxSteps);
	}

	maze->printBoard();
	int x = 3;
}
State checkStateInMaze(Player* player, Maze * maze) {
	 //if (player.m_currentLocation == player.bookmark) return BOOKMARK;
	// else if (maze.currentLocation)
}

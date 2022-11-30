#include "Game.h"
void Game::MainLoop(void) {
	while (!IsFinished())
		MainLoopIteration();
}
void Game::MainLoopIteration(void) {
	Render();
	Input();
	ProgressAnimations();
	AI();
	Physics();
	CollisionChecking();
	UserCode(); // hook for custom code at end
	CommitDestructions();
}
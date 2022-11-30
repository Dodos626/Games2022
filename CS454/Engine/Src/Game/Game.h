#pragma once
#ifndef GAMEINCLUDE
#define GAMEINCLUDE

#include <functional>

class Game { // app::Game namespace, the mother application
public:
	using Action = std::function<void(void)>;
	using Pred = std::function<bool(void)>;
private:
	Action render, anim, input, ai, physics, destruct, collisions, user;
	Pred done;
	void Invoke(const Action& f) { if (f) f(); }
public:
	//setters
	void SetRender(const Action& f) { render = f; }
	void SetAnim(const Action& f) { anim = f; }
	void SetInput(const Action& f) { input = f; }
	void SetAI(const Action& f) { ai = f; }
	void SetPhysics(const Action& f) { physics = f; }
	void SetDestruct(const Action& f) { destruct = f; }
	void SetCollisions(const Action& f) { collisions = f; }
	void SetUser(const Action& f) { user = f; }
	
	void Render(void) { Invoke(render); }
	void ProgressAnimations(void) { Invoke(anim); }
	void Input(void) { Invoke(input); }
	void AI(void) { Invoke(ai); }
	void Physics(void) { Invoke(physics); }
	void CollisionChecking(void) { Invoke(collisions); }
	void CommitDestructions(void) { Invoke(destruct); }
	void UserCode(void) { Invoke(user); }
	bool IsFinished(void) const { return !done(); }

	//loops
	void MainLoop(void);
	void MainLoopIteration(void);
};

#endif
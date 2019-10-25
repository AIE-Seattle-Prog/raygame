#pragma once

#include <vector>

#include "physics.h"

class game
{
	float accumulatedFixedTime;

	std::vector<physObject> physObjects;

public:
	game();

	void init();
	void tick();
	void tickPhys();
	void draw() const;
	void exit();

	bool shouldClose() const;
	bool shouldPhysics() const;

	float targetFixedStep;
	float physicsScale;
};
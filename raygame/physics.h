#pragma once

#include "glm/vec2.hpp"
#include "shapes.h"

class physObject
{
public:
	glm::vec2 pos;
	glm::vec2 vel;

	glm::vec2 forces;

	physObject();

	float mass;
	float drag;

	shape collider;

	void tickPhys(float delta);
	void draw() const;

	// Add a continuous force with respect to mass
	void addForce(glm::vec2 force);
	// Add an instantaneous force with respect to mass
	void addImpulse(glm::vec2 impulse);

	// Accelerates the object w/o respect to mass
	void addAccel(glm::vec2 accel);
	// Adds an instantaneous force w/o respect to mass
	void addVelocityChange(glm::vec2 delta);
};
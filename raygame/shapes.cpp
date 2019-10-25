#include "shapes.h"

#include "glm/glm.hpp"

bool checkCircleCircle(glm::vec2 posA, circle circleA, glm::vec2 posB, circle circleB)
{
	// get the distance
	float dist = glm::length(posA - posB);
	// get the sum of the radii
	float sum = circleA.radius + circleB.radius;

	return dist < sum;
}

bool checkAABBAABB(glm::vec2 posA, aabb aabbA, glm::vec2 posB, aabb aabbB)
{
	return posA.x - aabbA.halfExtents.x < posB.x + aabbB.halfExtents.x &&  // l r
		   posA.x + aabbA.halfExtents.x > posB.x - aabbB.halfExtents.x &&  // r l
		   posA.y - aabbA.halfExtents.y < posB.y + aabbB.halfExtents.y &&  // t b
		   posA.y + aabbA.halfExtents.y > posB.y - aabbB.halfExtents.y;    // b t
}

bool checkCircleAABB(glm::vec2 posA, circle circ, glm::vec2 posB, aabb ab)
{
	float distX = posA.x - glm::clamp(posA.x, posB.x - ab.halfExtents.x, posB.x + ab.halfExtents.x);
	float distY = posA.y - glm::clamp(posA.y, posB.y - ab.halfExtents.y, posB.y + ab.halfExtents.y);

	return (distX * distX + distY * distY) < (circ.radius * circ.radius);
}

bool checkCircleX(glm::vec2 posA, circle lhs, glm::vec2 posB, shape rhs)
{
	return rhs.match([posA, lhs, posB](circle s) { return checkCircleCircle(posA, lhs, posB, s); },
                	 [posA, lhs, posB](aabb s)   { return checkCircleAABB(posA, lhs, posB, s); });
}

bool checkAABBX(glm::vec2 posA, aabb lhs, glm::vec2 posB, shape rhs)
{
	return rhs.match([posA, lhs, posB](circle s) { return checkCircleAABB(posA, s, posB, lhs); },
		             [posA, lhs, posB](aabb s) { return checkAABBAABB(posA, lhs, posB, s); });
}
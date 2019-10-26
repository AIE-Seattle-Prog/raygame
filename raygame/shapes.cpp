#include "shapes.h"

#include "glm/glm.hpp"

#include "physics.h"

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

void resolvePhysBodies(physObject& lhs, physObject& rhs)
{
	glm::vec2 resImpulses[2];

	glm::vec2 normal = { 0,0 };
	float pen = 0.0f;

	normal = lhs.collider.match([lhs, rhs, &pen](circle c)	{
																float dist = glm::length(lhs.pos - rhs.pos);
																float sum = lhs.collider.get<circle>().radius + rhs.collider.get<circle>().radius;

																pen = sum - dist;

																return glm::normalize(lhs.pos - rhs.pos);
															},
		                        [lhs, rhs, &pen](aabb a) { return glm::vec2(); });

	resolveCollision(lhs.pos, lhs.vel, lhs.mass, rhs.pos, rhs.vel, rhs.mass, 1, normal, resImpulses);

	lhs.pos += normal * pen;
	rhs.pos -= normal * pen;

	lhs.vel = resImpulses[0];
	rhs.vel = resImpulses[1];
}

void resolveCollision(glm::vec2 posA, glm::vec2 velA, float massA,
	                  glm::vec2 posB, glm::vec2 velB, float massB,
	                  float elasticity, glm::vec2 normal, glm::vec2 * dst)
{
	glm::vec2 relVel = velA - velB;
	float impulseMag = glm::dot(-(1.0f + elasticity) * relVel, normal) /
					   glm::dot(normal, normal * (1 / massA + 1 / massB));

	dst[0] = velA + (impulseMag / massA) * normal;
	dst[1] = velB - (impulseMag / massB) * normal;
}

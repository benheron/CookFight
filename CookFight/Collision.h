#pragma once

#include <math.h>
#include <cmath>
#include <algorithm> 
#include "BoundingBox.h"

//edge in 2D
struct FaceQuery {
	FaceQuery(float largDist, int faceIndex) : largDist(largDist), faceIndex(faceIndex) {}
	float largDist;
	int faceIndex;
	float largeDistAllowedAxes;
};

struct PenDir
{
	float penetration;
	glm::vec3 dir;
	glm::vec3 colNorm;
};

/**
@brief A collection of collision functions
*/
namespace Collision
{
	bool boxBoxCollision(BoundingBox *a, BoundingBox* b);

	bool SATIntersection(BoundingBox *a, BoundingBox* b);

	bool SATSupport(BoundingBox *a, BoundingBox* b, PenDir &pdA, PenDir &pdB);



	const float PI = 3.14159265359;

	FaceQuery leastPenetration(BoundingBox *a, BoundingBox* b);

	float distanceEdgePoint(const Edge &e, const glm::vec3 &p);


	float cross2D(glm::vec3 a, glm::vec3 b);


	bool SATSupportAxes(BoundingBox *a, BoundingBox* b, PenDir &pdA, PenDir &pdB, std::vector<glm::vec3> vTests);


	FaceQuery leastPenetrationAxes(BoundingBox *a, BoundingBox* b, std::vector<glm::vec3> vTests, bool reverseVec);


	bool testAxes(glm::vec3 v, std::vector<glm::vec3> vTests);



}



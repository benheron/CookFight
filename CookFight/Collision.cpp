#include "Collision.h"

bool Collision::boxBoxCollision(BoundingBox *a, BoundingBox* b)
{
	glm::vec3 aMin = a->getVMin();
	glm::vec3 aMax = a->getVMax();

	glm::vec3 bMin = b->getVMin();
	glm::vec3 bMax = b->getVMax();

	if (aMax.x > bMin.x &&
		aMin.x < bMax.x &&
		aMax.y > bMin.y &&
		aMin.y < bMax.y )
	{

		return true;
	}

	return false;
}




bool Collision::SATIntersection(BoundingBox *a, BoundingBox* b)
{
	

	for (int i = 0; i < a->getNumEdges(); i++)
	{

		glm::vec3 n = a->getEdge(i).normal;
		Interval ia = a->getInterval(n);
		Interval ib = b->getInterval(n);

		if (ia.maxVal < ib.minVal ||
			ib.maxVal < ia.minVal)
		{
			return false;
		}
	}



	for (int i = 0; i < b->getNumEdges(); i++)
	{

		glm::vec3 n = b->getEdge(i).normal;
		Interval ia = a->getInterval(n);
		Interval ib = b->getInterval(n);

		if (ia.maxVal < ib.minVal ||
			ib.maxVal < ia.minVal)
		{
			return false;
		}
	}

	return true;
}





bool Collision::SATSupport(BoundingBox *a, BoundingBox* b, PenDir &pdA, PenDir &pdB)
{
	FaceQuery fq1 = leastPenetration(a, b);
	if (fq1.largDist > 0.0f)
	{
		return false;
	}


	FaceQuery fq2 = leastPenetration(b, a);
	if (fq2.largDist > 0.0f)
	{
		return false;
	}

	pdA.dir = a->getEdge(fq1.faceIndex).normal;
	pdA.penetration = -fq1.largDist;
	
	
	pdB.dir = b->getEdge(fq2.faceIndex).normal;
	pdB.penetration = -fq2.largDist;

	

	

	return true;
}


FaceQuery Collision::leastPenetration(BoundingBox *a, BoundingBox* b)
{
	float bestDistance = -FLT_MAX;
	int bestIndex;


	for (int i = 0; i < a->getNumEdges(); i++)
	{
		glm::vec3 n = a->getEdge(i).normal;

		//get support point
		glm::vec3 supB = b->getSupport(-n);


		float d = distanceEdgePoint(a->getEdge(i), supB);

		if (d > bestDistance)
		{
			bestDistance = d;
			bestIndex = i;
		}
	}

	return FaceQuery(bestDistance, bestIndex);
}











float Collision::distanceEdgePoint(const Edge &e, const glm::vec3 &p)
{
	float y2y1 = e.dir.y;
	float x2x1 = e.dir.x;


	//float y2y1 = e.end.y - e.start.y;
	//float x2x1 = e.end.x - e.start.x;


	float top = (y2y1*p.x) - (x2x1*p.y) + (e.end.x*e.start.y) - (e.end.y*e.start.x);
	float bot = sqrt(y2y1*y2y1 + x2x1*x2x1);



	return top / bot;
}


float Collision::cross2D(glm::vec3 a, glm::vec3 b)
{
	return a.x*b.y - a.y*b.x;
}







bool Collision::SATSupportAxes(BoundingBox *a, BoundingBox* b, PenDir &pdA, PenDir &pdB, std::vector<glm::vec3> vTests)
{
	FaceQuery fq1 = leastPenetrationAxes(a, b, vTests, true);
	if (fq1.largDist > 0.0f)
	{
		return false;
	}


	FaceQuery fq2 = leastPenetrationAxes(b, a, vTests, false);
	if (fq2.largDist > 0.0f)
	{
		return false;
	}

	
	pdA.dir = a->getEdge(fq1.faceIndex).normal;
	pdA.penetration = -fq1.largeDistAllowedAxes;


	pdB.dir = b->getEdge(fq2.faceIndex).normal;
	pdB.penetration = -fq2.largeDistAllowedAxes;
	

	return true;
}


FaceQuery Collision::leastPenetrationAxes(BoundingBox *a, BoundingBox* b, std::vector<glm::vec3> vTests, bool reverseVec)
{
	float largestDist = -FLT_MAX;
	float bestDistance = -FLT_MAX;
	int bestIndex;
	bool ignoreAnAxis = false;

	if (reverseVec)
	{
		for (int i = 0; i < vTests.size(); i++)
		{
			vTests[i].x = -vTests[i].x;
			vTests[i].y = -vTests[i].y;
			vTests[i].z = 0;
		}
	}

	for (int i = 0; i < a->getNumEdges(); i++)
	{
		glm::vec3 n = a->getEdge(i).normal;

		bool ignoreAxis = false;

		if (testAxes(n, vTests))
		{
			ignoreAxis = true;
			ignoreAnAxis = true;
		}

		//get support point
		glm::vec3 supB = b->getSupport(-n);


		float d = distanceEdgePoint(a->getEdge(i), supB);

		if (d > bestDistance)
		{
			
			if (ignoreAxis)
			{
				bestDistance = d;
			}
			else 
			{
				largestDist = d;
				bestIndex = i;
			}
			bestIndex = i;
		}
	}


	if (ignoreAnAxis)
	{
		int f = 0;
	}

	FaceQuery fq = FaceQuery(bestDistance, bestIndex);
	fq.largeDistAllowedAxes = largestDist;
	return FaceQuery(bestDistance, bestIndex);
}


bool Collision::testAxes(glm::vec3 v, std::vector<glm::vec3> vTests)
{
	for (int i = 0; i < vTests.size(); i++)
	{
		if (v == vTests[i])
		{
			return false;
		}
	}
	return true;
}
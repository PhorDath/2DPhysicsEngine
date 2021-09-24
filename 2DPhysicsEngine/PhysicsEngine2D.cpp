#include "PhysicsEngine2D.h"

/*
		This function detects the orientation of a triple of 3 points.
		It is done by calculating the slope between the points.
		The possibilities are:
			0 - collinear
			1 - clockwise
			2 - counterclockwise

		source: https://www.geeksforgeeks.org/orientation-3-ordered-points/
	*/
int pe2d::orientation(float x1, float y1, float x2, float y2, float x3, float y3) {
	float slope1 = (y2 - y1) * (x3 - x2);
	float slope2 = (x2 - x1) * (y3 - y2);

	if (slope1 == slope2) {
		// collinear
		return 0;
	}
	else if (slope1 < slope2) {
		// clockwise
		return 1;
	}
	else if (slope1 > slope2) {
		// counterclockwise
		return 2;
	}
}

int pe2d::orientation(vertex v1, vertex v2, vertex v3)
{
	return orientation(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
}

// Given three colinear points p, q, r, the function checks if
// point q lies on line segment 'pr'
bool pe2d::onSegment(float x1, float y1, float x2, float y2, float x3, float y3)
{
	if (x2 <= std::max(x1, x3) && x2 >= std::min(x1, x3) && y2 <= std::max(y1, y3) && y2 >= std::min(y1, y3))
		return true;

	return false;
}

bool pe2d::onSegment(vertex v1, vertex v2, vertex v3)
{
	return onSegment(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
}

/*
	This function will check if two lines determined by points (A, B) and (C, D) intersect each other.
	source: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
*/
bool pe2d::lineIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) { // point A, point B, point C, point D) {
	int orientation_ABC = orientation(x1, y1, x2, y2, x3, y3);
	int orientation_ABD = orientation(x1, y1, x2, y2, x4, y4);

	int orientation_CDA = orientation(x3, y3, x4, y4, x1, y1);
	int orientation_CDB = orientation(x3, y3, x4, y4, x2, y2);

	// general case
	if (orientation_ABC != orientation_ABD && orientation_CDA != orientation_CDB) {
		return true;
	}

	// special cases
	if (orientation_ABC == 0 && onSegment(x1, y1, x3, y3, x2, y2))
		return true;

	if (orientation_ABD == 0 && onSegment(x1, y1, x4, y4, x2, y2))
		return true;

	if (orientation_CDA == 0 && onSegment(x3, y3, x1, y1, x4, y4))
		return true;

	if (orientation_CDB == 0 && onSegment(x3, y3, x2, y2, x4, y4))
		return true;

	return false;

}

bool pe2d::lineIntersect(vertex v1, vertex v2, vertex v3, vertex v4)
{
	return lineIntersect(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, v4.x, v4.y);
}

int pe2d::countIntersections(polygon pol, vertex poi) {
	bool isInside = false;
	int count = 0;
	int i = 0;
	do {
		int next = (i + 1) % pol.size();

		bool intersection = lineIntersect(pol[i].x, pol[i].y, pol[next].x, pol[next].y, poi.x, poi.y, INT_MAX, poi.y);
		if (intersection == true) {
			// if colinear
			if (orientation(pol[i].x, pol[i].y, poi.x, poi.y, pol[next].x, pol[next].y) == 0) {
				isInside = onSegment(pol[i].x, pol[i].y, poi.x, poi.y, pol[next].x, pol[next].y);
			}
			count++;
		}
		i = next;
	} while (i != 0);

	return count;
}

float pe2d::triangleArea(vertex p1, vertex p2, vertex p3) {
	return 0.5 * abs(p1.x * p2.y + p1.y * p3.x + p2.x * p3.y - p1.y * p2.x - p1.x * p3.y - p2.y * p3.x);
}

bool pe2d::pointInPolygon(polygon pol, vertex poi) {
	int n = pol.size();

	if (n < 3) {

	}
	else if (n == 2) {
		// if the polygon is composed by three it represents a triangle, so we can use an alternative algorithm

		// calculate the triangle's area
		// the formula is area = 1/2 * det(polygon)
		int area = triangleArea(pol[0], pol[1], pol[2]);
		int area1 = triangleArea(poi, pol[0], pol[1]);
		int area2 = triangleArea(poi, pol[0], pol[2]);
		int area3 = triangleArea(poi, pol[1], pol[2]);

		if (area1 + area2 + area3 == area) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		// https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/

		bool isInside = false;
		int count = 0;
		int i = 0;
		do {
			int next = (i + 1) % n;

			bool intersection = lineIntersect(pol[i].x, pol[i].y, pol[next].x, pol[next].y, poi.x, poi.y, INT_MAX, poi.y);
			if (intersection == true) {
				// if colinear
				if (orientation(pol[i].x, pol[i].y, poi.x, poi.y, pol[next].x, pol[next].y) == 0) {
					isInside = onSegment(pol[i].x, pol[i].y, poi.x, poi.y, pol[next].x, pol[next].y);
					if (isInside) {
						break;
					}
				}
				if (isInside) {
					break;
				}
				count++;
			}
			if (isInside) {
				break;
			}
			i = next;
		} while (i != 0);

		if (isInside || count % 2 == 1) {
			return true;
		}
		else {
			return false;
		}
	}
}

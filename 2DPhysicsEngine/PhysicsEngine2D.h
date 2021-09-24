#pragma once

#include <vector>

namespace pe2d {
	struct vertex {
		float x, y;

		vertex() {
			this->x = 0.0;
			this->y = 0.0;
		};

		vertex(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};

	typedef std::vector<vertex> polygon;

	/*
		This function detects the orientation of a triple of 3 points.
		It is done by calculating the slope between the points.
		The possibilities are:
			0 - collinear
			1 - clockwise
			2 - counterclockwise

		source: https://www.geeksforgeeks.org/orientation-3-ordered-points/
	*/
	static int orientation(float x1, float y1, float x2, float y2, float x3, float y3);
	static int orientation(vertex v1, vertex v2, vertex v3);

	// Given three colinear points p, q, r, the function checks if
	// point q lies on line segment 'pr'
	bool onSegment(float x1, float y1, float x2, float y2, float x3, float y3);
	bool onSegment(vertex v1, vertex v2, vertex v3);

	/*
		This function will check if two lines determined by points (A, B) and (C, D) intersect each other.
		source: https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
	*/
	bool lineIntersect(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	bool lineIntersect(vertex v1, vertex v2, vertex v3, vertex v4);

	int countIntersections(polygon pol, vertex poi);

	float triangleArea(vertex p1, vertex p2, vertex p3);

	bool pointInPolygon(polygon pol, vertex poi);
}




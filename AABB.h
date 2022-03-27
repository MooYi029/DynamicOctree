#pragma once

#ifndef AABB_H
#define AABB_H
#include "octree.h"
#include "octree_node.h"


class AABB {
public:
	Point min;
	Point max;

	AABB() {};
	AABB(Point min, Point max) {
		this->min = min;
		this->max = max;
	};
	AABB(Octree_Struct root) {
		double x = root->center.x;
		double y = root->center.y;
		double z = root->center.z;
		double len = root->length;
		this->min = Point(x - len, y - len, z - len);
		this->max = Point(x + len, y + len, z + len);
	};

	bool isInserted(const AABB& aabb) {
		return ((min.x >= aabb.min.x && min.x <= aabb.max.x) || (aabb.min.x >= min.x && aabb.min.x <= max.x)) &&
			((min.y >= aabb.min.y && min.y <= aabb.max.y) || (aabb.min.y >= min.y && aabb.min.y <= max.y)) &&
			((min.z >= aabb.min.z && min.z <= aabb.max.z) || (aabb.min.z >= min.z && aabb.min.z <= max.z));
	}

};
#endif


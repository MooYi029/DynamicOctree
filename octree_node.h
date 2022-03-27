#pragma once
#include "Point3.h"

typedef struct Octree_Node {           // 八叉树结点
	int level;                         //该节点在八叉树中的深度，根节点为0
	double length;                     //八叉树边长的一半
	Point center;                      //八叉树结点中心位置

	Octree_Node* child[8];             //8个孩子节点
	Octree_Node* parent;               //父节点
	int childNum;                      //记录孩子节点的数量

	void init(Octree_Node* parent, double length, int level) {      //初始化八叉树节点（父节点，格子宽度，深度）                         
		this->parent = parent;
		this->childNum = 0;
		for (int i = 0; i < 8; i++) {
			child[i] = NULL;
		}
		center.setPoint(0, 0, 0);
		this->level = level;
		this->length = length;
	}
	void setCenter(double x, double y, double z) {
		center.setPoint(x, y, z);
	}

	void destory() {
		this->parent = NULL;
		for (int i = 0; i < 8; i++) {
			child[i] = NULL;
		}
	}
}Octree_Node, * Octree_Struct;

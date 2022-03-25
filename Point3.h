#pragma once
#ifndef POINT3_H
#define POINT3_H

struct Point { //点云结构体
	double x;
	double y;
	double z;
	void setPoint(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	Point(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

typedef struct Octree_Node {           // 八叉树结点
	int level;                         //该节点在八叉树中的深度，根节点为0
	double length;                     //八叉树边长的一半
	Point center;                      //八叉树结点中心位置

	Octree_Node* child[8];             //8个孩子节点
	Octree_Node* parent;               //父节点
	bool deleted;                      //标志该结点是否被删除
	bool splited;
	int childNum;                      //记录孩子节点的数量

	void init(Octree_Node* parent, double length, int level) {      //初始化八叉树节点（父节点，格子宽度，深度）                         
		this->parent = parent;
		this->deleted = false;
		this->splited = false;
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

#endif
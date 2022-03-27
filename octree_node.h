#pragma once
#include "Point3.h"

typedef struct Octree_Node {           // �˲������
	int level;                         //�ýڵ��ڰ˲����е���ȣ����ڵ�Ϊ0
	double length;                     //�˲����߳���һ��
	Point center;                      //�˲����������λ��

	Octree_Node* child[8];             //8�����ӽڵ�
	Octree_Node* parent;               //���ڵ�
	int childNum;                      //��¼���ӽڵ������

	void init(Octree_Node* parent, double length, int level) {      //��ʼ���˲����ڵ㣨���ڵ㣬���ӿ�ȣ���ȣ�                         
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

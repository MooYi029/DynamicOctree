#pragma once
#ifndef POINT3_H
#define POINT3_H

struct Point { //���ƽṹ��
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

typedef struct Octree_Node {           // �˲������
	int level;                         //�ýڵ��ڰ˲����е���ȣ����ڵ�Ϊ0
	double length;                     //�˲����߳���һ��
	Point center;                      //�˲����������λ��

	Octree_Node* child[8];             //8�����ӽڵ�
	Octree_Node* parent;               //���ڵ�
	bool deleted;                      //��־�ý���Ƿ�ɾ��
	bool splited;
	int childNum;                      //��¼���ӽڵ������

	void init(Octree_Node* parent, double length, int level) {      //��ʼ���˲����ڵ㣨���ڵ㣬���ӿ�ȣ���ȣ�                         
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
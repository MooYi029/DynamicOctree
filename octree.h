#pragma once
#ifndef OCTREE_H
#define OCTREE_H
#include <iostream>
#include <vector>
#include <math.h>
#include <iostream>
#include<stack>
#include "Point3.h"
#include "AABB.h"


class Octree {
public:
	Octree_Struct root;                    //�˲���root�ڵ�
	double octLength;                      // �˲������ȣ�Ҷ�ӽ��ĳ��ȵ�һ��
	int maxLevel;

	std::vector<Octree_Struct> voxel;

	Octree() {}
	Octree(double octLength) {
		this->octLength = octLength;
	}
	~Octree() {
		std::cout << "delete Octree" << std::endl;
		destory(root);
	}

	// ������ʼ����1x1x1 1��voxel 
	void creatCubeIniVoxels(double len) {
		root = new Octree_Node();
		root->init(NULL, len, 0);
		voxel.push_back(root);
			//std::cout <<  "��" << i << "��: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
	}

	// ������ʼ����2x2x2 8��voxel ���൱��һ�η��ѡ�
	void creatCubeIniVoxels2(double len) {
		root = new Octree_Node();
		root->init(NULL, len, -1);
		creat(root);
		for (int i = 0; i < 8; i++) {
			voxel.push_back(root->child[i]);
			//std::cout <<  "��" << i << "��: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
		}
	}

	// ������ʼ����4x4x4 64��voxel ���൱�����η��ѡ�
	void creatCubeIniVoxels3(double len) {
		root = new Octree_Node();
		root->init(NULL, len, -2);
		creat(root);
		for (int i = 0; i < 8; i++) {
			creat(root->child[i]);
			for (int j = 0; j < 8; j++) {
				voxel.push_back(root->child[i]->child[j]);
			}			
			//std::cout <<  "��" << i << "��: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
		}
	}

	// ��������
	void creatToolIniVoxels(double x_scope, double y_scope, double z_scope, double pre) {
		root = new Octree_Node();
		for (double x = -x_scope; x <= x_scope; x += pre) {
			for (double y = -y_scope; y <= y_scope; y += pre) {
				for (double z = -z_scope; z <= z_scope; z += pre) {
					Octree_Struct temp = new Octree_Node();
					temp->init(NULL, pre/2, 0);
					temp->center.setPoint(x, y, z);
					voxel.push_back(temp);
				}
			}
		}
	}

	// �ж��Ƿ�ΪҶ�ӽ��
	static bool isLeaf(Octree_Struct const octree) {
		if (octree == NULL)
			return false;
		for (int i = 0; i < 8; i++) {
			if (octree->child[i] != NULL)
				return false;
		}
		return true;
	}

	// ����8�����ӽڵ�
	void creat(Octree_Struct octree) {
		octree->childNum = 8;
		octree->splited = true;
		for (int i = 0; i < 8; i++) {
			octree->child[i] = new Octree_Node();
			octree->child[i]->init(octree, octree->length / 2, octree->level + 1);

			if (i == 0 || i == 1 || i == 4 || i == 5)
				octree->child[i]->center.y = octree->center.y + octree->length / 2;
			if (i == 2 || i == 3 || i == 6 || i == 7)
				octree->child[i]->center.y = octree->center.y - octree->length / 2;
			if (i == 0 || i == 2 || i == 4 || i == 6)
				octree->child[i]->center.x = octree->center.x + octree->length / 2;
			if (i == 1 || i == 3 || i == 5 || i == 7)
				octree->child[i]->center.x = octree->center.x - octree->length / 2;
			if (i == 0 || i == 1 || i == 2 || i == 3)
				octree->child[i]->center.z = octree->center.z + octree->length / 2;
			if (i == 4 || i == 5 || i == 6 || i == 7)
				octree->child[i]->center.z = octree->center.z - octree->length / 2;
		}
	}

	void mergeDelet(Octree_Struct node) {
		if (node && node->childNum == 0 ) {
			if (!node->parent) {     // û�и���㣨Ϊ���ڵ㣩ɾ��
				destory(node);
			}
			else{
				Octree_Struct tmp = node->parent; 
				tmp->childNum--;         // ���׽ڵ�ĺ��ӽڵ��һ

				for (int i = 0; i < 8; i++) {     // ɾ���ý��
					if (tmp->child[i] == node) {
						tmp->child[i] = NULL;
						node->parent = NULL;
						delete node;
						break;
					}
				}
				mergeDelet(tmp);   // �ݹ����Ϻϲ�ɾ��
			}
		}
	}

	// ���ߺ͹�����������
	void remove(Octree& tool, int deep = 8) {
		clock_t startTime, endTime;
		startTime = clock();

		std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
		// �����������н��
		for (; it != tool.voxel.end(); it++) {
			AABB tool_aabb(*it);

			// ����������8��voxel
			std::vector<Octree_Struct>::iterator it_voxel = voxel.begin();
			for (; it_voxel != voxel.end(); it_voxel++) {
				Octree_Struct node = (*it_voxel);
				AABB aabb(node);
				if (node == NULL || !aabb.isInserted(tool_aabb)) {
					continue;
				}

				std::stack<Octree_Struct> sstack;
				sstack.push(node);

				while (!sstack.empty()) {
					node = sstack.top();
					sstack.pop();

					if (tool_aabb.isInserted(AABB(node))) { //��Χ���ཻ
						if (isLeaf(node)) {  // Ҷ�ӽ��
							if (node->level < deep ) {  // ϸ�ִ�������
								creat(node);
								for (int i = 0; i < 8; i++) {
									sstack.push(node->child[i]);
								}
							}
							else {    //  ϸ�ִ���������ΪҶ�ӽ����ɾ���Ľ��
								node->deleted = true;
								node->parent->childNum--;

								mergeDelet(node->parent);


								//ɾ�����
								for (int i = 0; i < 8; i++) {
									if (node->parent->child[i] == node) {
										node->parent->child[i] = NULL;
										node->parent = NULL;
										node->deleted = true;
										break;
									}
								}
								delete node;

								
							}
						}
						else {  // ��Ҷ�ӽ��,���ӽڵ���ջ
							for (int i = 0; i < 8; i++) {
								if (node->child[i])
									sstack.push(node->child[i]);
							}
						}
					}
					else{ // ��Χ�в��ཻ
						continue;
					}
				}

			}
		}

		endTime = clock();
		std::cout << "��������ķѵ�ʱ�䣺 " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	}
	

	// old version
	void remove3(Octree& tool, int deep = 8) {
		std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
		// �����������н��
		for (; it != tool.voxel.end(); it++) {
			AABB tool_aabb(*it);

			// ����������8��voxel
			std::vector<Octree_Struct>::iterator it_voxel = voxel.begin();
			for (; it_voxel != voxel.end(); it_voxel++) {
				Octree_Struct node = (*it_voxel);
				AABB aabb(node);
				if (node == NULL || !aabb.isInserted(tool_aabb)) {
					continue;
				}

				std::stack<Octree_Struct> sstack;
				sstack.push(node);

				while (!sstack.empty()) {
					node = sstack.top();
					sstack.pop();

					if (tool_aabb.isInserted(AABB(node))) { //��Χ���ཻ
						if (isLeaf(node)) {  // Ҷ�ӽ��
							if (node->level < deep) {  // ϸ�ִ�������
								
								creat(node);
								for (int i = 0; i < 8; i++) {
									sstack.push(node->child[i]);
								}
							}
							else {    //  ϸ�ִ���������ΪҶ�ӽ����ɾ���Ľ��
								node->deleted = true;
							}
						}
						else {  // ��Ҷ�ӽ��,���ӽڵ���ջ
							for (int i = 0; i < 8; i++) {
								if (node->child[i])
									sstack.push(node->child[i]);
							}
						}
					}
					else { // ��Χ�в��ཻ
						continue;
					}
				}

			}
		}
	}

	// �ͷŰ˲������
	void destory(Octree_Struct octree) {
		for (int i = 0; i < 8; i++) {
			if (octree->child[i] != NULL) {
				destory(octree->child[i]);
				octree->child[i]->parent = NULL;
				delete octree->child[i];
			}
		}
		if (octree->parent == NULL) {
			delete octree;
		}
	}

	void remove2(Octree &tool, int deep) {
		//std::cout << "[begin remove]" << std::endl;
		std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
		for (; it != tool.voxel.end(); it++) {
			AABB tool_aabb((*it));   // ÿ�����߽���Χ��

			std::vector<Octree_Struct>::iterator it_voxel = voxel.begin();
			for (; it_voxel != voxel.end(); it_voxel++) {
				
				Octree_Struct workpiece_node = (*it_voxel);     //���ظ��ڵ�
				AABB workpiece_node_aabb(workpiece_node);       //���ɹ�������Χ��

				if (workpiece_node == NULL || !workpiece_node_aabb.isInserted(tool_aabb))
					continue;

				std::stack<Octree_Struct> node_stack;   // ���ջ
				std::stack<AABB> aabb_stack;            //��Χ�е�ջ	
				node_stack.push(workpiece_node);
				aabb_stack.push(workpiece_node_aabb);

				while (!node_stack.empty()) {
					workpiece_node = node_stack.top();
					workpiece_node_aabb = aabb_stack.top();
					node_stack.pop(); aabb_stack.pop();

					if (workpiece_node_aabb.isInserted(tool_aabb)) {  //�Ƿ��ཻ
						if (isLeaf(workpiece_node)) {  //  �����Ҷ�ӽ�㣬��ϸ�ִ�����
							if (workpiece_node->level < deep) {   // ϸ�ֶȲ���
								creat(workpiece_node);//ϸ�� ��ջ
								for (int i = 0; i < 8; i++) {
									node_stack.push(workpiece_node->child[i]);
									aabb_stack.push(AABB(workpiece_node->child[i]));									
								}
							}
							else { // ϸ�ֶȹ���
								for (int k = 0; k < 8; k++) {  //ɾ���ý��
									if (workpiece_node->parent!=NULL && workpiece_node->parent->child[k] == workpiece_node) {
										workpiece_node->parent->child[k] = NULL;
										workpiece_node->parent = NULL;
										//std::cout << "Num " << k << "  " << workpiece_node->parent->child[k] << std::endl;
										delete workpiece_node;
										break;
									}
								}
							}
						}
						else {   //�������Ҷ�ӽ�㣬��ջ
							for (int i = 0; i < 8; i++) {
								if (workpiece_node->child[i] != NULL) {
									node_stack.push(workpiece_node->child[i]);
									aabb_stack.push(AABB(workpiece_node->child[i]));
								}
							}
						}

					}
					else { //���ཻ

					}
				}
			}
		}
		//std::cout << "[finish remove]" << std::endl;
	}
};

// OCTREE_H
#endif 




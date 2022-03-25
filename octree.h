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
	Octree_Struct root;                    //八叉树root节点
	double octLength;                      // 八叉树精度（叶子结点的长度的一半
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

	// 工件初始化，1x1x1 1个voxel 
	void creatCubeIniVoxels(double len) {
		root = new Octree_Node();
		root->init(NULL, len, 0);
		voxel.push_back(root);
			//std::cout <<  "【" << i << "】: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
	}

	// 工件初始化，2x2x2 8个voxel 【相当于一次分裂】
	void creatCubeIniVoxels2(double len) {
		root = new Octree_Node();
		root->init(NULL, len, -1);
		creat(root);
		for (int i = 0; i < 8; i++) {
			voxel.push_back(root->child[i]);
			//std::cout <<  "【" << i << "】: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
		}
	}

	// 工件初始化，4x4x4 64个voxel 【相当于两次分裂】
	void creatCubeIniVoxels3(double len) {
		root = new Octree_Node();
		root->init(NULL, len, -2);
		creat(root);
		for (int i = 0; i < 8; i++) {
			creat(root->child[i]);
			for (int j = 0; j < 8; j++) {
				voxel.push_back(root->child[i]->child[j]);
			}			
			//std::cout <<  "【" << i << "】: center(" << temp->center.x << "," << temp->center.y << "," << temp->center.z <<")  level :" << temp->level << std::endl;
		}
	}

	// 创建刀具
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

	// 判断是否为叶子结点
	static bool isLeaf(Octree_Struct const octree) {
		if (octree == NULL)
			return false;
		for (int i = 0; i < 8; i++) {
			if (octree->child[i] != NULL)
				return false;
		}
		return true;
	}

	// 创建8个孩子节点
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
			if (!node->parent) {     // 没有父结点（为根节点）删除
				destory(node);
			}
			else{
				Octree_Struct tmp = node->parent; 
				tmp->childNum--;         // 父亲节点的孩子节点减一

				for (int i = 0; i < 8; i++) {     // 删除该结点
					if (tmp->child[i] == node) {
						tmp->child[i] = NULL;
						node->parent = NULL;
						delete node;
						break;
					}
				}
				mergeDelet(tmp);   // 递归向上合并删除
			}
		}
	}

	// 刀具和工件布尔运算
	void remove(Octree& tool, int deep = 8) {
		clock_t startTime, endTime;
		startTime = clock();

		std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
		// 遍历刀具所有结点
		for (; it != tool.voxel.end(); it++) {
			AABB tool_aabb(*it);

			// 遍历工件的8个voxel
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

					if (tool_aabb.isInserted(AABB(node))) { //包围盒相交
						if (isLeaf(node)) {  // 叶子结点
							if (node->level < deep ) {  // 细分次数不够
								creat(node);
								for (int i = 0; i < 8; i++) {
									sstack.push(node->child[i]);
								}
							}
							else {    //  细分次数够了且为叶子结点则删除改结点
								node->deleted = true;
								node->parent->childNum--;

								mergeDelet(node->parent);


								//删除结点
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
						else {  // 非叶子结点,则子节点入栈
							for (int i = 0; i < 8; i++) {
								if (node->child[i])
									sstack.push(node->child[i]);
							}
						}
					}
					else{ // 包围盒不相交
						continue;
					}
				}

			}
		}

		endTime = clock();
		std::cout << "布尔运算耗费的时间： " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << std::endl;
	}
	

	// old version
	void remove3(Octree& tool, int deep = 8) {
		std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
		// 遍历刀具所有结点
		for (; it != tool.voxel.end(); it++) {
			AABB tool_aabb(*it);

			// 遍历工件的8个voxel
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

					if (tool_aabb.isInserted(AABB(node))) { //包围盒相交
						if (isLeaf(node)) {  // 叶子结点
							if (node->level < deep) {  // 细分次数不够
								
								creat(node);
								for (int i = 0; i < 8; i++) {
									sstack.push(node->child[i]);
								}
							}
							else {    //  细分次数够了且为叶子结点则删除改结点
								node->deleted = true;
							}
						}
						else {  // 非叶子结点,则子节点入栈
							for (int i = 0; i < 8; i++) {
								if (node->child[i])
									sstack.push(node->child[i]);
							}
						}
					}
					else { // 包围盒不相交
						continue;
					}
				}

			}
		}
	}

	// 释放八叉树结点
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
			AABB tool_aabb((*it));   // 每个刀具结点包围盒

			std::vector<Octree_Struct>::iterator it_voxel = voxel.begin();
			for (; it_voxel != voxel.end(); it_voxel++) {
				
				Octree_Struct workpiece_node = (*it_voxel);     //体素根节点
				AABB workpiece_node_aabb(workpiece_node);       //生成工件结点包围盒

				if (workpiece_node == NULL || !workpiece_node_aabb.isInserted(tool_aabb))
					continue;

				std::stack<Octree_Struct> node_stack;   // 结点栈
				std::stack<AABB> aabb_stack;            //包围盒的栈	
				node_stack.push(workpiece_node);
				aabb_stack.push(workpiece_node_aabb);

				while (!node_stack.empty()) {
					workpiece_node = node_stack.top();
					workpiece_node_aabb = aabb_stack.top();
					node_stack.pop(); aabb_stack.pop();

					if (workpiece_node_aabb.isInserted(tool_aabb)) {  //是否相交
						if (isLeaf(workpiece_node)) {  //  如果是叶子结点，，细分次数？
							if (workpiece_node->level < deep) {   // 细分度不够
								creat(workpiece_node);//细分 入栈
								for (int i = 0; i < 8; i++) {
									node_stack.push(workpiece_node->child[i]);
									aabb_stack.push(AABB(workpiece_node->child[i]));									
								}
							}
							else { // 细分度够了
								for (int k = 0; k < 8; k++) {  //删除该结点
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
						else {   //如果不是叶子结点，入栈
							for (int i = 0; i < 8; i++) {
								if (workpiece_node->child[i] != NULL) {
									node_stack.push(workpiece_node->child[i]);
									aabb_stack.push(AABB(workpiece_node->child[i]));
								}
							}
						}

					}
					else { //不相交

					}
				}
			}
		}
		//std::cout << "[finish remove]" << std::endl;
	}
};

// OCTREE_H
#endif 




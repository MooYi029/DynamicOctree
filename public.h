#pragma once
#ifndef PUBLIC_H
#define PUBLIC_H
#include "octree.h"

//void moveTool(Octree_Struct root, double z_scope, double y_scope = 0, double x_scope = 0) {
//    if (root == NULL)
//        return;
//
//    double x = root->center.x + x_scope;
//    double y = root->center.y + y_scope;
//    double z = root->center.z + z_scope;
//    root->setCenter(x, y, z);
//
//    for (int i = 0; i < 8; i++) {
//        if (root->nodes[i] != NULL) {
//            moveTool(root->nodes[i], z_scope, y_scope, x_scope);
//        }
//    }
//}

void moveTool(std::vector<Octree_Struct> voxel, double x_scope, double y_scope , double z_scope ) {
    std::vector<Octree_Struct>::iterator it = voxel.begin();
    for (; it != voxel.end(); it++) {
        double x = (*it)->center.x + x_scope;
        double y = (*it)->center.y + y_scope;
        double z = (*it)->center.z + z_scope;
        (*it)->setCenter(x, y, z);
    }
}

/////铣削仿真 
//	///paths为多条轨迹，最内层vector只有三个值，即点坐标的三个分量，中间层存储着轨迹点序列，最外层存储轨迹列表
//	///tool 为刀具信息，暂时先用球头刀，也就是可以取出道具半径
//void MillingSimulation(const std::vector<std::vector<std::vector<double>>>& paths, const Tool& tool);
//
/////获取铣削后的模型数据,stl记录返回值
/////STLData数据为模型的三角网格数据，由一个点列表和面索引列表组成
//struct STLData
//{
//	std::vector<std::vector<double>> points;//最内层vector只有三个值，即点坐标的三个分量，中间层存储着轨迹点序列
//	std::vector<int> faceList;//面索引列表，每三个代表一个三角形
//}
//
//void GetMillingModel(STLData& stl);
#endif
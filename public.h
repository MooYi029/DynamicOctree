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

#endif
#include "DynamicOctreeDemo.h"
#include "public.h"

DynamicOctreeDemo::DynamicOctreeDemo(QWidget* parent) {
    setSurfaceType(QWindow::OpenGLSurface);

    QSurfaceFormat format;
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
    format.setVersion(2, 1);
    setFormat(format);
    context = new QOpenGLContext;
    context->setFormat(format);
    context->create();
    context->makeCurrent(this);
    openGLFunctions = context->functions();

    rotation = 0;
    translatez = 1;

    workpiece.creatCubeIniVoxels3(2);
    tool.creatToolIniVoxels(0.05, 0.05, 1, 0.05);
    moveTool(tool.voxel, 0, 0, 3.5);
    //moveTool(tool.voxel, 0, -1.8, 3.5);

    //moveTool(tool.voxel, 0, 0, -1.5);

    // for (int i = 0; i < 600; i++) {
    //    workpiece.remove(tool);                      // 刀具与工件布尔运算
    //    moveTool(tool.voxel, -0.0025, 0.005, 0);     //移动刀具   
    // }
    //       
    // moveTool(tool.voxel, 1.5, -3, 0);               //移动刀具 
    // 
    // for (int i = 0; i < 600; i++) {
    //     workpiece.remove(tool);                      // 刀具与工件布尔运算
    //     moveTool(tool.voxel, 0.0025, 0.005, 0);      //移动刀具 
    // }

}


DynamicOctreeDemo::~DynamicOctreeDemo() {
}

void DynamicOctreeDemo::UpdateAnimation() {
    rotation += 10;
    this->update();
}

// 画线条
void DynamicOctreeDemo::drawCubeLine(Octree_Struct octree, int drawDepth) {
    if (octree->level > drawDepth) {
        for (int i = 0; i < 8; i++) {
            if (octree->child[i] != NULL) {
                drawCubeLine(octree->child[i], drawDepth);
            }
        }
    }
    else {
        double x = octree->center.x;
        double y = octree->center.y;
        double z = octree->center.z;
        double length = octree->length;

        Point p1(x + length, y + length, z + length);
        Point p2(x - length, y + length, z + length);
        Point p3(x - length, y - length, z + length);
        Point p4(x + length, y - length, z + length);

        Point p5(x + length, y + length, z - length);
        Point p6(x - length, y + length, z - length);
        Point p7(x - length, y - length, z - length);
        Point p8(x + length, y - length, z - length);

        //画线
        //top
        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glVertex3f(p4.x, p4.y, p4.z);
        glVertex3f(p4.x, p4.y, p4.z);
        glVertex3f(p1.x, p1.y, p1.z);
        //bottom
        glVertex3f(p5.x, p5.y, p5.z);
        glVertex3f(p6.x, p6.y, p6.z);
        glVertex3f(p6.x, p6.y, p6.z);
        glVertex3f(p7.x, p7.y, p7.z);
        glVertex3f(p7.x, p7.y, p7.z);
        glVertex3f(p8.x, p8.y, p8.z);
        glVertex3f(p8.x, p8.y, p8.z);
        glVertex3f(p5.x, p5.y, p5.z);

        glVertex3f(p1.x, p1.y, p1.z);
        glVertex3f(p5.x, p5.y, p5.z);
        glVertex3f(p2.x, p2.y, p2.z);
        glVertex3f(p6.x, p6.y, p6.z);
        glVertex3f(p3.x, p3.y, p3.z);
        glVertex3f(p7.x, p7.y, p7.z);
        glVertex3f(p4.x, p4.y, p4.z);
        glVertex3f(p8.x, p8.y, p8.z);
    }
}


void DynamicOctreeDemo::drawCubeLine(Octree_Struct octree) {
    if (!Octree::isLeaf(octree)){
        for (int i = 0; i < 8; i++) {
            if (octree->child[i] != NULL) {
                drawCubeLine(octree->child[i]);
            }
        }
    }
    else {
        
            double x = octree->center.x;
            double y = octree->center.y;
            double z = octree->center.z;
            //std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
            double length = octree->length;

            Point p1(x + length, y + length, z + length);
            Point p2(x - length, y + length, z + length);
            Point p3(x - length, y - length, z + length);
            Point p4(x + length, y - length, z + length);

            Point p5(x + length, y + length, z - length);
            Point p6(x - length, y + length, z - length);
            Point p7(x - length, y - length, z - length);
            Point p8(x + length, y - length, z - length);

            //画线
            //top
            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p4.x, p4.y, p4.z);
            glVertex3f(p4.x, p4.y, p4.z);
            glVertex3f(p1.x, p1.y, p1.z);
            //bottom
            glVertex3f(p5.x, p5.y, p5.z);
            glVertex3f(p6.x, p6.y, p6.z);
            glVertex3f(p6.x, p6.y, p6.z);
            glVertex3f(p7.x, p7.y, p7.z);
            glVertex3f(p7.x, p7.y, p7.z);
            glVertex3f(p8.x, p8.y, p8.z);
            glVertex3f(p8.x, p8.y, p8.z);
            glVertex3f(p5.x, p5.y, p5.z);

            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p5.x, p5.y, p5.z);
            glVertex3f(p2.x, p2.y, p2.z);
            glVertex3f(p6.x, p6.y, p6.z);
            glVertex3f(p3.x, p3.y, p3.z);
            glVertex3f(p7.x, p7.y, p7.z);
            glVertex3f(p4.x, p4.y, p4.z);
            glVertex3f(p8.x, p8.y, p8.z);
        }
        
    
}

void DynamicOctreeDemo::effectiveDrawCubeLine(Octree_Struct octree) {
    if (!Octree::isLeaf(octree)) {
        for (int i = 0; i < 8; i++) {
            if (octree->child[i] != NULL) {
                drawCubeLine(octree->child[i]);
            }
        }
    }
    else {
        if (!octree->deleted) {
            double x = octree->center.x;
            double y = octree->center.y;
            double z = octree->center.z;
            //std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
            double length = octree->length;

            Point p1(x + length, y + length, z + length);
            Point p2(x - length, y + length, z + length);
            Point p3(x - length, y - length, z + length);
            Point p4(x + length, y - length, z + length);

            Point p5(x + length, y + length, z - length);
            Point p6(x - length, y + length, z - length);
            Point p7(x - length, y - length, z - length);
            Point p8(x + length, y - length, z - length);

            Octree_Struct parent = octree->parent;
            int num = 0;
            for (int i = 0; i < 8; i++) {
                if (parent->child[i] == octree) {
                    num = i;
                    break;
                }
            } 

            switch (num) {
            case 0 :
                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);

                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p5.x, p5.y, p5.z);

                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p4.x, p4.y, p4.z);


                if (parent->child[1]->deleted) {                
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);

                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[2]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p4.x, p4.y, p4.z);

                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                
                if (parent->child[4]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);

                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                
                if (parent->child[1]->deleted && parent->child[2]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }
                if (parent->child[1]->deleted && parent->child[4]->deleted) {
                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }

                if (parent->child[2]->deleted && parent->child[4]->deleted) {
                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                break;
            case 1:              
                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p6.x, p6.y, p6.z);

                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p1.x, p1.y, p1.z);

                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p3.x, p3.y, p3.z);


                if (parent->child[0]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);

                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                }

                if (parent->child[3]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p3.x, p3.y, p3.z);

                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);

                }

                if (parent->child[5]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);

                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                    
                }

                if (parent->child[0]->deleted && parent->child[3]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                if (parent->child[0]->deleted && parent->child[5]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[3]->deleted && parent->child[5]->deleted) {
                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                break;
            case 2:
                glVertex3f(p4.x, p4.y, p4.z);
                glVertex3f(p1.x, p1.y, p1.z);
                
                glVertex3f(p4.x, p4.y, p4.z);
                glVertex3f(p3.x, p3.y, p3.z);  

                glVertex3f(p4.x, p4.y, p4.z);
                glVertex3f(p8.x, p8.y, p8.z);

                if (parent->child[0]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p2.x, p2.y, p2.z);

                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);
                }

                if (parent->child[3]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                    
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }

                if (parent->child[6]->deleted) {
                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p8.x, p8.y, p8.z);

                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[0]->deleted && parent->child[3]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }
                if (parent->child[0]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[3]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }
                break;
            case 3:
                glVertex3f(p2.x, p2.y, p2.z);
                glVertex3f(p3.x, p3.y, p3.z);

                glVertex3f(p3.x, p3.y, p3.z);
                glVertex3f(p4.x, p4.y, p4.z);

                glVertex3f(p3.x, p3.y, p3.z);
                glVertex3f(p7.x, p7.y, p7.z);

                if (parent->child[1]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[2]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[7]->deleted) {
                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[1]->deleted && parent->child[2]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);
                }
                if (parent->child[1]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[2]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                break;
            case 4:
                glVertex3f(p5.x, p5.y, p5.z);
                glVertex3f(p1.x, p1.y, p1.z);

                glVertex3f(p5.x, p5.y, p5.z);
                glVertex3f(p6.x, p6.y, p6.z);

                glVertex3f(p5.x, p5.y, p5.z);
                glVertex3f(p8.x, p8.y, p8.z);

                if (parent->child[0]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p1.x, p1.y, p1.z);

                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                }

                if (parent->child[5]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);

                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }

                if (parent->child[6]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);

                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[0]->deleted && parent->child[5]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                }

                if (parent->child[0]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                }

                if (parent->child[5]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);
                }
                break;
            case 5:
                glVertex3f(p6.x, p6.y, p6.z);
                glVertex3f(p2.x, p2.y, p2.z);

                glVertex3f(p6.x, p6.y, p6.z);
                glVertex3f(p5.x, p5.y, p5.z);

                glVertex3f(p6.x, p6.y, p6.z);
                glVertex3f(p7.x, p7.y, p7.z);

                if (parent->child[1]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p2.x, p2.y, p2.z);

                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                }

                if (parent->child[4]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);

                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[7]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);

                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }

                if (parent->child[1]->deleted && parent->child[4]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p1.x, p1.y, p1.z);
                }
                if (parent->child[1]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                }
                if (parent->child[4]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p8.x, p8.y, p8.z);
                }
                break;
            case 6:
                glVertex3f(p8.x, p8.y, p8.z);
                glVertex3f(p5.x, p5.y, p5.z);

                glVertex3f(p8.x, p8.y, p8.z);
                glVertex3f(p4.x, p4.y, p4.z);

                glVertex3f(p8.x, p8.y, p8.z);
                glVertex3f(p7.x, p7.y, p7.z);

                if (parent->child[2]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p4.x, p4.y, p4.z);

                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                }

                if (parent->child[4]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);

                    glVertex3f(p5.x, p5.y, p5.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[7]->deleted) {
                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p7.x, p7.y, p7.z);

                    glVertex3f(p7.x, p7.y, p7.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }

                if (parent->child[2]->deleted && parent->child[4]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p1.x, p1.y, p1.z);
                }
                if (parent->child[2]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);
                }

                if (parent->child[4]->deleted && parent->child[7]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);
                }
                break;
            case 7:
                glVertex3f(p7.x, p7.y, p7.z);
                glVertex3f(p6.x, p6.y, p6.z);

                glVertex3f(p7.x, p7.y, p7.z);
                glVertex3f(p8.x, p8.y, p8.z);
                
                glVertex3f(p7.x, p7.y, p7.z);
                glVertex3f(p3.x, p3.y, p3.z);

                if (parent->child[3]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p3.x, p3.y, p3.z);

                    glVertex3f(p3.x, p3.y, p3.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                }

                if (parent->child[5]->deleted) {
                    glVertex3f(p2.x, p2.y, p2.z);
                    glVertex3f(p6.x, p6.y, p6.z);

                    glVertex3f(p6.x, p6.y, p6.z);
                    glVertex3f(p5.x, p5.y, p5.z);
                }

                if (parent->child[6]->deleted) {
                    glVertex3f(p4.x, p4.y, p4.z);
                    glVertex3f(p8.x, p8.y, p8.z);

                    glVertex3f(p8.x, p8.y, p8.z);
                    glVertex3f(p5.x, p5.y, p5.z);
                }

                if (parent->child[3]->deleted && parent->child[5]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p2.x, p2.y, p2.z);
                }
                if (parent->child[3]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p4.x, p4.y, p4.z);
                }

                if (parent->child[5]->deleted && parent->child[6]->deleted) {
                    glVertex3f(p1.x, p1.y, p1.z);
                    glVertex3f(p5.x, p5.y, p5.z);
                }
                break;
            default:
                std::cout << "default" << std::endl;
                break;
            }
            
            

            ////画线
            ////top
            //glVertex3f(p1.x, p1.y, p1.z);
            //glVertex3f(p2.x, p2.y, p2.z);
            //glVertex3f(p2.x, p2.y, p2.z);
            //glVertex3f(p3.x, p3.y, p3.z);
            //glVertex3f(p3.x, p3.y, p3.z);
            //glVertex3f(p4.x, p4.y, p4.z);
            //glVertex3f(p4.x, p4.y, p4.z);
            //glVertex3f(p1.x, p1.y, p1.z);
            ////bottom
            //glVertex3f(p5.x, p5.y, p5.z);
            //glVertex3f(p6.x, p6.y, p6.z);
            //glVertex3f(p6.x, p6.y, p6.z);
            //glVertex3f(p7.x, p7.y, p7.z);
            //glVertex3f(p7.x, p7.y, p7.z);
            //glVertex3f(p8.x, p8.y, p8.z);
            //glVertex3f(p8.x, p8.y, p8.z);
            //glVertex3f(p5.x, p5.y, p5.z);

            //glVertex3f(p1.x, p1.y, p1.z);
            //glVertex3f(p5.x, p5.y, p5.z);
            //glVertex3f(p2.x, p2.y, p2.z);
            //glVertex3f(p6.x, p6.y, p6.z);
            //glVertex3f(p3.x, p3.y, p3.z);
            //glVertex3f(p7.x, p7.y, p7.z);
            //glVertex3f(p4.x, p4.y, p4.z);
            //glVertex3f(p8.x, p8.y, p8.z);
        }

    }
}

// 画面
void DynamicOctreeDemo::drawCubeFace(Octree_Struct octree, int drawDepth) {
    if (octree->level > drawDepth) {
        for (int i = 0; i < 8; i++) {
            if (octree->child[i] != NULL) {
                drawCubeFace(octree->child[i], drawDepth);
            }
        }
    }
    else {
        double x = octree->center.x;
        double y = octree->center.y;
        double z = octree->center.z;
        double length = octree->length;
        Point p[8];
        p[0].setPoint(x + length, y + length, z + length);
        p[1].setPoint(x - length, y + length, z + length);
        p[2].setPoint(x - length, y - length, z + length);
        p[3].setPoint(x + length, y - length, z + length);

        p[4].setPoint(x + length, y + length, z - length);
        p[5].setPoint(x - length, y + length, z - length);
        p[6].setPoint(x - length, y - length, z - length);
        p[7].setPoint(x + length, y - length, z - length);
        int cubeIndexs[6][4] = { {3,2,1,0}, //上表面
                                {4,5,6,7},  //下表面
                                {0,1,5,4},  //后表面
                                {1,2,6,5},  //左表面
                                {2,3,7,6},  //前表面
                                {3,0,4,7} };//右表面 

        for (int i = 0; i < 6; i++) {
            glBegin(GL_POLYGON);
            for (int j = 0; j < 4; j++) {
                if (i == 0 || i == 1)
                    glColor3ub(145u, 145u, 145u);
                else if (i == 2 || i == 4)
                    glColor3ub(189u, 189u, 189u);
                else
                    glColor3ub(91u, 91u, 91u);
                glVertex3f(p[cubeIndexs[i][j]].x, p[cubeIndexs[i][j]].y, p[cubeIndexs[i][j]].z);
            }
            glEnd();
        }

    }
}

void DynamicOctreeDemo::drawCubeFace(Octree_Struct octree) {
    if (!Octree::isLeaf(octree)) {
        for (int i = 0; i < 8; i++) {
            if (octree->child[i] != NULL) {
                drawCubeFace(octree->child[i]);
            }
        }
    }
    else {
        
            double x = octree->center.x;
            double y = octree->center.y;
            double z = octree->center.z;
            double length = octree->length;
            Point p[8];
            p[0].setPoint(x + length, y + length, z + length);
            p[1].setPoint(x - length, y + length, z + length);
            p[2].setPoint(x - length, y - length, z + length);
            p[3].setPoint(x + length, y - length, z + length);

            p[4].setPoint(x + length, y + length, z - length);
            p[5].setPoint(x - length, y + length, z - length);
            p[6].setPoint(x - length, y - length, z - length);
            p[7].setPoint(x + length, y - length, z - length);
            int cubeIndexs[6][4] = { {3,2,1,0}, //上表面
                                    {4,5,6,7},  //下表面
                                    {0,1,5,4},  //后表面
                                    {1,2,6,5},  //左表面
                                    {2,3,7,6},  //前表面
                                    {3,0,4,7} };//右表面 

            for (int i = 0; i < 6; i++) {
                glBegin(GL_POLYGON);
                for (int j = 0; j < 4; j++) {
                    if (i == 0 || i == 1)
                        glColor3ub(145u, 145u, 145u);
                    else if (i == 2 || i == 4)
                        glColor3ub(189u, 189u, 189u);
                    else
                        glColor3ub(91u, 91u, 91u);
                    glVertex3f(p[cubeIndexs[i][j]].x, p[cubeIndexs[i][j]].y, p[cubeIndexs[i][j]].z);
                }
                glEnd();
            }
          
    }
}

void DynamicOctreeDemo::on_FileButton_clicked() {
}

void DynamicOctreeDemo::initializeGL() {
    glEnable(GL_DEPTH_TEST);
    resizeGL(this->width(), this->height());
}

void DynamicOctreeDemo::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    qreal aspectradio = qreal(w) / qreal(h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(20, aspectradio, 0.1, 400000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DynamicOctreeDemo::paintGL() {
    double r = translatez;

    glClearColor(1, 1, 1, 1.0f);// 背景颜色
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    gluLookAt(r * cos(3.14 * (moveRad_y / 180)), r * sin(3.14 * (moveRad_x / 180)), r * sin(3.14 * (moveRad_y / 180)), 0, 0, 0, 0, 1.0, 0);

    /*if (showPoint == true) {
        glPointSize(2.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0f, 0.0f, 0.0f);
        for (std::vector<Point>::iterator it = workpiece.pointCloud.begin(); it != workpiece.pointCloud.end(); it++) {
            glVertex3f((*it).x, (*it).y, (*it).z);
        }
        glEnd();
    }*/

    glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
    if (showCube == true) {
        std::vector<Octree_Struct>::iterator it = workpiece.voxel.begin();
        for (; it != workpiece.voxel.end(); it++) {
            drawCubeFace(*it);
        }
    }
    //画Tool
    if (showTool == true) {
        std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
            for (; it != tool.voxel.end(); it++) {
                drawCubeFace(*it);
            }
    }
    

    glLineWidth(0.4f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.8f, 0.0f);
    if (showToolLine == true) {
        std::vector<Octree_Struct>::iterator it = tool.voxel.begin();
        for (; it != tool.voxel.end(); it++) {
            drawCubeLine(*it);
        }
    }
    if (showAllCubeLine == true) {
        for (int i = 1; i < workpiece.root->level; i++) {
            drawCubeLine(workpiece.root, i);
        }
    }
    else {
        if (showCubeLine == true) {
            std::vector<Octree_Struct>::iterator it = workpiece.voxel.begin();
            for (; it != workpiece.voxel.end(); it++) {
                drawCubeLine(*it);
            }
            
        }
    }
    glEnd();
    glFlush();
}

void DynamicOctreeDemo::resizeEvent(QResizeEvent* event) {
    resizeGL(this->width(), this->height());
    this->update();
}

void DynamicOctreeDemo::paintEvent(QPaintEvent* event) {
    paintGL();
}

void DynamicOctreeDemo::wheelEvent(QWheelEvent* event) {
    if (event->delta() > 0) {
        translatez /= 1.1;
    }
    else if (event->delta() < 0) {
        translatez *= 1.1;
    }
    this->update();
}

void DynamicOctreeDemo::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        lPressed = true;
    }
    else if (event->button() == Qt::RightButton) {
        rPressed = true;
    }
    pressPoint = event->pos();
}

void DynamicOctreeDemo::mouseMoveEvent(QMouseEvent* event) {
    if (lPressed == true) {
        movePoint = event->pos();
        moveRad_y += (movePoint.x() - pressPoint.x()) / moveRate;
        moveRad_x += (movePoint.y() - pressPoint.y()) / moveRate;
        pressPoint = movePoint;

        if (moveRad_x > 90)moveRad_x = 90;
        if (moveRad_x < -90)moveRad_x = -90;

        this->update();
    }
    if (rPressed == true) {
        movePoint = event->pos();
        moveLength_x += (double)(movePoint.x() - pressPoint.x()) / 10;
        moveLength_y += (double)(movePoint.y() - pressPoint.y()) / 10;
        pressPoint = movePoint;
        this->update();
    }
}

void DynamicOctreeDemo::mouseReleaseEvent(QMouseEvent* event) {
    lPressed = false;
    rPressed = false;
}

void DynamicOctreeDemo::keyPressEvent(QKeyEvent* event) {
    switch (event->key())
    {
    case Qt::Key_Plus:
        if (showDepth + 1 <= workpiece.root->level) {
            showDepth += 1;
            update();
        }
        break;
    case Qt::Key_Minus:
        if (showDepth - 1 >= 1) {
            showDepth -= 1;
            update();
        }
        break;
    case Qt::Key_0:
        showPoint = !showPoint;
        update();
        break;
    case Qt::Key_1:
        showCube = !showCube;
        update();
        break;
    case Qt::Key_2:
        showCubeLine = !showCubeLine;
        update();
        break;
    case Qt::Key_3:
        showAllCubeLine = !showAllCubeLine;
        update();
        break;
    case Qt::Key_4:
        showTool = !showTool;
        update();
        break;
    case Qt::Key_5:
        showToolLine = !showToolLine;
        update();
        break;
    case Qt::Key_7:
        moveTool(tool.voxel, 0, 0, -0.5); workpiece.remove(tool);        
        update();        
        break;
    case Qt::Key_8:
        moveTool(tool.voxel, 0, 0, 0.5); workpiece.remove(tool);
        update();
        break;
    case Qt::Key_A:
        moveTool(tool.voxel, -0.1, 0, 0); workpiece.remove(tool);
        update();
        break;
    case Qt::Key_D:
        moveTool(tool.voxel, 0.1, 0, 0); workpiece.remove(tool);
        update();
        break;
    case Qt::Key_W:
        moveTool(tool.voxel, 0, 0.1, 0); workpiece.remove(tool);
        update();
        break;
    case Qt::Key_S:
        moveTool(tool.voxel, 0, -0.1, 0); workpiece.remove(tool);
        update();
        break;
    case Qt::Key_F:
        workpiece.remove(tool);
        update();
        break;
    /*case Qt::Key_7:
        for (int i = 0; i < 600; i++) {
            workpiece.remove(tool);
            moveTool(tool.voxel, -0.0025, 0.005, 0); 
            update();
        }       
        break;
    case Qt::Key_8:
        for (int i = 0; i < 600; i++) {
            moveTool(tool.voxel, 0.0025, -0.005, 0);
        }
        update();      
        break;
    case Qt::Key_9:
        for (int i = 0; i < 600; i++) {
            workpiece.remove(tool);
            moveTool(tool.voxel, 0.0025, 0.005, 0); 
            update();
        }      
        break;*/
    case Qt::Key_Up:
        workpiece.remove(tool);
        moveTool(tool.voxel, 0.0025, 0.0025, 0); 
        update();
        break;
    case Qt::Key_Down:
        workpiece.remove(tool);
        moveTool(tool.voxel, 0.0025, -0.0025, 0); 
        update();
        break;
    case Qt::Key_Left:
        workpiece.remove(tool);
        moveTool(tool.voxel, -0.0025, -0.0025, 0); 
        update();
        break;
    case Qt::Key_Right:
        workpiece.remove(tool);
        moveTool(tool.voxel, -0.0025, 0.0025, 0); 
        update();
        break;
    }    
}


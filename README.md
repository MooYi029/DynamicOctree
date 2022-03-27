# DynamicOctree Readme
代码思路总体还是比较简单，使用的最基础的八叉树结果实现的动态八叉树

octree_node.h  记录八叉树结点的主要数据结构

八叉树结点，主要包含level记录结点的深度，length记录结点的长度的一半，center记录结点的中心三维坐标值，parent记录父亲节点，child[8]记录孩子节点，childNum记录其孩子节点的数量。

```c++
typedef struct Octree_Node {           // 八叉树结点
	int level;                         //该节点在八叉树中的深度，根节点为0
	double length;                     //八叉树边长的一半
	Point center;                      //八叉树结点中心位置

	Octree_Node* child[8];             //8个孩子节点
	Octree_Node* parent;               //父节点
	int childNum;                      //记录孩子节点的数量

	void init(Octree_Node* parent, double length, int level) {}      //初始化八叉树节点（父节点，格子宽度，深度） 
	
	void setCenter(double x, double y, double z) {}
	
}Octree_Node, * Octree_Struct;
```



octree.h   octree类包含刀具和工件以及布尔运算

```c++
class Octree {
public:
	Octree_Struct root;                    //八叉树root节点
	double octLength;                      // 八叉树精度（叶子结点的长度的一半
	int maxLevel;						 
	std::vector<Octree_Struct> voxel;     // 如果工件或者刀具有多个体素作为根节点则用stack存储

	Octree() {}
	Octree(double octLength) {}
	~Octree() {}

	// 工件初始化
	void creatCubeIniVoxels(double len) {}
	// 创建刀具 人为控制粗略构造长方体
	void creatToolIniVoxels(double x_scope, double y_scope, double z_scope, double pre) {}
	// 判断是否为叶子结点
	static bool isLeaf(Octree_Struct const octree) {}
	// 创建8个孩子节点
	void creat(Octree_Struct octree) {}
    // 结点的删除合并
	void mergeDelet(Octree_Struct node) {}
	// 刀具和工件布尔运算
	void remove(Octree& tool, int deep = 8) {}
	// 释放八叉树结点
	void destory(Octree_Struct octree) {}
};
```



在DynamicOctreeDemo.h中定义了workpiece和tool，在DynamicOctreeDemo.cpp中实现以及初始化

DynamicOctreeDemo.h中的drawCubeLine以及drawCubeFace实现对八叉树结点的绘制

```c++
//画线的简要实现方法，获取八叉树8个顶点的坐标，两点构成一条直线
drawCubeLine(Octree_Struct octree) {
    Point p1,p2,p3,p4,p5,p6,p7,p8;
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
```



```c++
//画面的主要代码
void DynamicOctreeDemo::drawCubeFace(Octree_Struct octree) {
    Point p[8];
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
```


#pragma once
#include "ui_DynamicOctreeDemo.h"
#include <QtWidgets/QMainWindow>
#include <qopenglwindow.h>
#include <qopenglfunctions.h>
#include <QSurfaceFormat>
#include <QtOpenGL/QtOpenGL>
#include <GL/GLU.h>
#include<GL/glut.h>
#include <QMouseEvent>
#include <QWheelEvent>
#include <vector>
#include "octree.h"
#include <time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

class DynamicOctreeDemo : public QOpenGLWindow
{
	Q_OBJECT

public:
	DynamicOctreeDemo(QWidget* parent = Q_NULLPTR);
	~DynamicOctreeDemo();
	Octree workpiece;
	Octree tool;


private:
	float rotation; // 旋转
	float translatez; // z转变

	bool lPressed = false;
	bool rPressed = false;

	QPoint pressPoint;
	QPoint movePoint;
	float moveRate = 1.0;

	float moveRad_x = 0;
	float moveRad_y = 0;
	float moveLength_x = 0;
	float moveLength_y = 0;
	int showDepth = 1;

	bool showPoint = false; // 显示点
	bool showCube = true;  //显示正方形
	bool showCubeLine = false; //显示正方形线条

	bool showTool = true;
	bool showToolLine = false;

	QOpenGLContext* context;
	QOpenGLFunctions* openGLFunctions;

	void drawCubeLine(Octree_Struct octree);
	void drawCubeFace(Octree_Struct octree);

public slots:
	void UpdateAnimation();
	void on_FileButton_clicked();

protected:
	virtual void initializeGL() override;
	virtual void resizeGL(int w, int h) override;
	virtual void paintGL() override;
	void resizeEvent(QResizeEvent* event) override;
	void paintEvent(QPaintEvent* event) override;
	void wheelEvent(QWheelEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void keyPressEvent(QKeyEvent* event)override;
};

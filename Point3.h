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


#endif
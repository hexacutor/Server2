#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Point.h"
class Buffer
{
public:
    int generate_cloud(double c_x, double c_y, double disp_x, double disp_y, int c_length);
    int rotate(double angle);
    int shift(double x, double y);
    int clear();
    int gen(int r);
    vector<Point> point_;
};
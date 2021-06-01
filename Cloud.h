#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Point.h"
class Cloud
{
public:
    vector<Point> point_;
    Cloud(int length);
    Cloud(int length, double c_x, double c_y, double disp_x, double disp_y);
    Cloud& operator= (Cloud const& c);
    Cloud(Cloud const& c);
    Cloud();
    int length() const;
};
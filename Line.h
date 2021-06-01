#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
class Line
{
public:
    Line(double x, double y);
    Line() ;
    double k;
    double b;
};
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
class Ier
{
public:
	vector<Point> point_;
	vector<double> matrix;
	vector<int> binmatrix;
	int cmatrix();
	int field(vector<Point> p);
	int ier();
};
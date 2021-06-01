#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
class Mintree
{
public:
	vector<Point> point_;
	vector<double> matrix;
	vector<int> binmatrix;
	int cmatrix();
	int stree(const string& tree, int r);
	int field(vector<Point> p);
};

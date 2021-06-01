#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
class DBscan
{
public:
	vector<Point> point_;
	vector<double> matrix;
	vector<int> binmatrix;
	int binary(double r);
	int cmatrix();
	int wave();
	int dbscan(double del, int k);
	vector<int> engage(vector<int> p,double del);
	int field(vector<Point> p);
	vector<find_cl> find_cl_;
};
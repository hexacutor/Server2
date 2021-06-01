#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
class EM
{
public:
	vector<Point> point_;
	int em(int k, ofstream* out);
	int field(vector<Point> p);
	vector<find_cl> find_cl_;
};

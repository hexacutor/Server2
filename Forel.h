#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
class Forel
{
public:
	vector<Point> point_;
	int field(vector<Point> p);
	int forel(double r, int d);
	vector<find_cl> find_cl_;
};
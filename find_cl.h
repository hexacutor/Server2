#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Point.h"
class find_cl
{
    friend class Field;
public:
    find_cl(vector<Point> p, vector<int> clus, int clusterqu, string s  ,int q);
    vector<Point> point_;
    vector<int> clus;
    int q;
    string info;
    void print(string filename);
};
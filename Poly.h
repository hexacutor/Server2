#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Hplane.h"
using namespace std;
const int M = 1000;
const int MAX_LEN = 256;
class Poly
{
    friend class Line;
    friend class Point;
    friend class Hplane;
public:
    Poly(vector<Point> p);
    vector<Point> point_;
    //Poly sec(Poly o, Hplane p);
    int q;
    void clear() ;
    ~Poly() ;
};
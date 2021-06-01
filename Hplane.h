#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Point.h"
#include "Line.h"
class Hplane
{
    friend class Line;
    friend class Point;
public:
    Hplane() ;
    Hplane(Line l, Point x);
    Line l;
    Point x;
};
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
using namespace std;
class Point
{
    friend class Cloud;
    friend class find_cl;
    friend class Field;
public:
    Point(Point const& c);
    Point(double x, double y);
    double x() const;
    double y() const;
    Point();
    int fprintf(ofstream* out) const;
    int NN(ofstream* out) const;
    int fprintfcl(ofstream* out, int k) const;
    int fprintfred(ofstream* out) const;
    int style(ofstream* out, int k, int r);
    int fprintfclr(ofstream* out, int k, double r) const;
    int fprintfLine(ofstream* out) const;
    int id() const;
    double f();
    int db;
    int st;
    double x_, y_;
    int id_;
};

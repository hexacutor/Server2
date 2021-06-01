#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "find_cl.h"
#include "methods.h"
class Field
{
public:
    Field();
    int fprintf(ofstream* out) const;
    int fprintf_cl(ofstream* out, int por) const;
    int fprintf_core(ofstream* out) const;
    int fprintf_dust(ofstream* out) const;
    int fprintf_coreLine(double del, ofstream* out) const;
    int length() const;
    vector<Point> point_;
    vector<Point> dust_;
    vector<Point> core_;
    vector<find_cl> find_cl_;
    int inf;
    vector<double> matrix;
    vector<int> binmatrix;
    int cmatrix();
    int binary(double r);
    int Voronoi();
    int wave();
    int hist(int u);
    int dbscan(double del, int k);
    int km(int k);
    int kmcore(int k, int p);
    int ier();
    int stree(const string& tree, int m);
    int em(int k, ofstream* out);
    int forel(double r, int d);
};
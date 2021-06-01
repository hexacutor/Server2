#pragma once
#include "Poly.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include <math.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001

double dist(Point a, Point b);
Point inter(Point p1, Point p2, Point p3, Point p4);
Line sp(Point a, Point b);
double vect(Point a, Point b);// z коррдината векторного произведения
double vectZ(double x1, double y1, double x2, double y2);// z коррдината векторного произведения
int intersection(Point p11, Point p12, Point p21, Point p22);//пересечение отрезков (да-нет)
int LF(Point a, Hplane p);
Poly sec(Poly o, Hplane p);
vector<Point> step(double r, vector<Point> point_, int t, ofstream* out, ofstream* out1);
vector<Point> kmc(int k, vector<Point> point_);

#pragma once
#include "methods.h"
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


double dist(Point a, Point b)
{
    return sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y()));
}
Line sp(Point a, Point b)
{
    double xm, ym; xm = (a.x_ + b.x_) / 2; ym = (a.y_ + b.y_) / 2;
    double kab = (b.y_ - a.y_) / (b.x_ - a.x_);
    double k = -1 / kab;
    double t = ym - k * xm;
    Line l(k, t);
    return l;
}
double vect(Point a, Point b)// z коррдината векторного произведения
{
    return (a.x_ * b.y_ - a.y_ * b.x_);
}
double vectZ(double x1, double y1, double x2, double y2)// z коррдината векторного произведения
{
    return (x1 * y2 - y1 * x2);
}
int intersection(Point p11, Point p12, Point p21, Point p22)//пересечение отрезков (да-нет)
{
    double v1, v2;
    v1 = vectZ(p12.x_ - p11.x_, p12.y_ - p11.y_, p22.x_ - p11.x_, p22.y_ - p11.y_) * vectZ(p12.x_ - p11.x_, p12.y_ - p11.y_, p21.x_ - p11.x_, p21.y_ - p11.y_);
    v2 = vectZ(p22.x_ - p21.x_, p22.y_ - p21.y_, p12.x_ - p21.x_, p12.y_ - p21.y_) * vectZ(p22.x_ - p21.x_, p22.y_ - p21.y_, p11.x_ - p21.x_, p11.y_ - p21.y_);
    if (((v1 < 0) || (fabs(v1) < EPS)) && ((v2 < 0) || (fabs(v2) < EPS)))
    {
        return 1;
    }
    return 0;
}
int LF(Point a, Hplane p)
{
    if (((a.y_ - (a.x_ * p.l.k + p.l.b)) * (p.x.y_ - (p.x.x_ * p.l.k + p.l.b)) > 0)|| fabs((a.y_ - (a.x_ * p.l.k + p.l.b)) * (p.x.y_ - (p.x.x_ * p.l.k + p.l.b)))<EPS)
        return 1;
    return 0;
}
Point inter(Point p1, Point p2, Point p3, Point p4)
{
    double a, b;
    Point p(((p1.x_ * p2.y_ - p1.y_ * p2.x_)*(p3.x_ - p4.x_) - (p1.x_ - p2.x_)*(p3.x_ * p4.y_ - p3.y_ * p4.x_)) / ((p1.x_ - p2.x_)*(p3.y_ - p4.y_) - (p1.y_ - p2.y_)*(p3.x_ - p4.x_)), ((p1.x_ * p2.y_ - p1.y_ * p2.x_)*(p3.y_ - p4.y_) - (p1.y_ - p2.y_)*(p3.x_ * p4.y_ - p3.y_ * p4.x_)) / ((p1.x_ - p2.x_)*(p3.y_ - p4.y_) - (p1.y_ - p2.y_)*(p3.x_ - p4.x_)));
   // b = (( p1.x_ * p2.y_ - p1.y_ * p2.x_)*(p3.y_ - p4.y_) - (p1.y_ - p2.y_)*(p3.x_ * p4.y_ - p3.y_ * p4.x_)) / ((p1.x_ - p2.x_)*(p3.y_ - p4.y_) - (p1.y_ - p2.y_)*(p3.x_ - p4.x_));
    return p;
}
Poly sec(Poly o, Hplane p)
{
    vector<Point> s;
    double t1, t2; t1 = 1000 * p.l.k + p.l.b; t2 = -1000 * p.l.k + p.l.b; Point temp1(1000, t1); Point temp2(-1000, t2);
    for (int i = 0; i < o.q - 1; ++i)
    {
        if (LF(o.point_[i], p))
            s.emplace_back(o.point_[i]);
        if (intersection(o.point_[i], o.point_[i + 1], temp1, temp2))
            s.emplace_back(inter(o.point_[i], o.point_[i + 1], temp1, temp2));
    }
    if (LF(o.point_[o.q - 1], p))
        s.emplace_back(o.point_[o.q - 1]);
    if (intersection(o.point_[o.q - 1], o.point_[0], temp1, temp2))
        s.emplace_back(inter(o.point_[o.q - 1], o.point_[0], temp1, temp2));
    Poly w(s);
    return w;
}
vector<Point> step(double r, vector<Point> point_, int t, ofstream* out, ofstream* out1)
{
    int q = point_.size();
    int si = point_.size();
    int cen;
    vector <Point> p, cent;
    double x, y;
    int s;
    Point old;
    Point nov;
    vector<int> cl;
    vector<int> o;
    int cls = 0;
    o.resize(si);
    for (int i = 0; i < point_.size(); ++i)
    {
        cl.push_back(1);
    }
    while (q > 0)
    {
        for (int i = 0; i < si; ++i)
        {
            if (cl[i] == 1)
            {
                cen = i;
                break;
            }
        }
        nov = point_[cen];
        do
        {
            x = 0;
            s = 0;
            y = 0;
            old = nov;
            for (int i = 0; i < si; ++i)
            {
                if (cl[i] == 1)
                {
                    if ((dist(point_[i], nov) < r))
                    {
                        x = x + point_[i].x();
                        y = y + point_[i].y();
                        s = s + 1;
                    }
                }
            }
            nov.x_ = x / s;
            nov.y_ = y / s;
        } while (dist(old, nov) > EPS);
        cent.push_back(nov);
        for (int i = 0; i < si; ++i)
        {
            if (((dist(point_[i], nov) < r)) && (cl[i] == 1))
            {
                p.push_back(point_[i]);
                cl[i] = 0;
                o[i] = cls;
            }
        }
        cls++;
        q = q - p.size();
        for (int i = 0; i < p.size(); ++i)
        {
            p[i].fprintfcl(out, cls);
        }
        p.clear();
        nov.fprintfclr(out1, cls, r);
    }
    return cent;
}
vector<Point> kmc(int k, vector<Point> point_)
{
    {
        vector<Point> p;
        vector<int> cl;
        vector<int> clawn;
        double s;
        double x, y;
        int ss;
        for (int j = 0; j < k; ++j)
        {
            x = 2 * (double)rand() / RAND_MAX - 1;
            y = 2 * (double)rand() / RAND_MAX - 1;
            p.emplace_back(x, y);
        }
        for (int i = 0; i < point_.size(); ++i)
        {
            cl.push_back(1);
            clawn.push_back(1);
        }
        do
        {
            clawn = cl;
            for (int i = 0; i < point_.size(); ++i)
            {
                s = 10;
                for (int j = 0; j < k; ++j)
                {
                    if ((sqrt((point_[i].x() - p[j].x()) * (point_[i].x() - p[j].x()) + (point_[i].y() - p[j].y()) * (point_[i].y() - p[j].y()))) < s)
                    {
                        cl[i] = j;
                        s = sqrt((point_[i].x() - p[j].x()) * (point_[i].x() - p[j].x()) + (point_[i].y() - p[j].y()) * (point_[i].y() - p[j].y()));
                    }
                }
            }
            for (int j = 0; j < k; ++j)
            {
                ss = 0;
                x = 0;
                y = 0;
                for (int i = 0; i < point_.size(); ++i)
                {
                    if (cl[i] == j)
                    {
                        {
                            x = x + point_[i].x();
                            y = y + point_[i].y();
                            ss++;
                        }
                    }
                }
                if (ss == 0)
                {
                    p[j].x_ = point_[0].x_;
                    p[j].y_ = point_[0].y_;
                    cl[0] = j;
                }
                else
                {
                    p[j].x_ = x / ss;
                    p[j].y_ = y / ss;
                }
            }
        } while (clawn != cl);
        return p;
    }
};










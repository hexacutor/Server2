#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "Voronoi.h"
#include "methods.h"
int Voronoi::voronoi()
{
    ofstream out("voron.txt");
    ofstream outf("field.txt");
    ofstream outt("tri.txt");
    vector<Point> main; main.emplace_back(-1, -1); main.emplace_back(-1, 1); main.emplace_back(1, 1); main.emplace_back(1, -1);
    for (int i = 0; i < point_.size(); ++i)
    {
        Poly pol(main);
        for (int j = 0; j < point_.size(); ++j)
        {
            if (j != i)
            {
                Line l = sp(point_[j], point_[i]);
                Hplane p(l, point_[i]);
                pol = sec(pol, p);
                // cout << "( "<<i<<","<< j<<" ) " << "\n";
            }
        }
        for (int k = 0; k < pol.q; ++k)
            out << pol.point_[k].x_ << "  " << pol.point_[k].y_ << "\n";
        out << pol.point_[0].x_ << "  " << pol.point_[0].y_ << "\n";
        out << "\n";
        out << "\n";
        for (int k = 0; k < pol.q - 1; ++k)
        {
            for (int j = 0; j < point_.size(); ++j)
            {
                if (j != i)
                {
                    Line l = sp(point_[j], point_[i]);
                    if (fabs(l.k - (pol.point_[k + 1].y_ - pol.point_[k].y_) / (pol.point_[k + 1].x_ - pol.point_[k].x_)) < EPS)
                    {

                        outt << point_[i].x_ << "  " << point_[i].y_ << "\n";
                        outt << point_[j].x_ << "  " << point_[j].y_ << "\n";
                        outt << "\n" << "\n";
                    }
                }
            }
        }
        for (int j = 0; j < point_.size(); ++j)
        {
            if (j != i)
            {
                Line l = sp(point_[j], point_[i]);
                if (fabs(l.k - (pol.point_[0].y_ - pol.point_[pol.q - 1].y_) / (pol.point_[0].x_ - pol.point_[pol.q - 1].x_)) < EPS)
                {
                    outt << point_[i].x_ << "  " << point_[i].y_ << "\n";
                    outt << point_[j].x_ << "  " << point_[j].y_ << "\n";
                    outt << "\n" << "\n";
                }
            }
        }
        //pol.point_.emplace_back(-1, -1); pol.point_.emplace_back(-1, 1); pol.point_.emplace_back(1, 1); pol.point_.emplace_back(1, -1);
    }
    for (int i = 0; i < point_.size(); ++i)
        outf << point_[i].x_ << "  " << point_[i].y_ << "\n";
    out.close();
    outf.close();
    outt.close();
    cout << fabs(-1);
    return 0;
};
double Voronoi::inter(double x,double y)
{
    int i1, i2, i3;
    double lool = 1000;
    for (int j = 0; j < point_.size(); ++j)
    {
        if ((sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y))) < lool)
        {
            lool = (sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y)));
            i1 = j;
        }
    }
     lool = 1000;
    for (int j = 0; j < point_.size(); ++j)
    {
        if (((sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y))) < lool)&&(j!=i1))
        {
            lool = (sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y)));
            i2 = j;
        }
    }
    lool = 1000;
    for (int j = 0; j < point_.size(); ++j)
    {
        if (((sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y))) < lool) && (j != i1) && (j != i2))
        {
            lool = (sqrt((point_[j].x_ - x) * (point_[j].x_ - x) + (point_[j].y_ - y) * (point_[j].y_ - y)));
            i3 = j;
        }
    } return (point_[i1].f() + point_[i2].f() + point_[i3].f())/3;
}
int Voronoi::field(vector<Point> p)
{
    point_.clear();
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
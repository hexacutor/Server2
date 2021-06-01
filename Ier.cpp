#pragma once
#include "Ier.h"
double metr(vector<Point> a, vector<Point> b)
{
    double r = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = 0; j < b.size(); ++j)
            r = r + sqrt((a[i].x_- b[i].x_)* (a[i].x_ - b[i].x_)+ (a[i].y_ - b[i].y_) * (a[i].y_ - b[i].y_));
    }
    return (r / (a.size() * b.size()));
}
int Ier::ier()
{
    int qu = point_.size();
    int y = qu;
    int ind1;
    int ind2;
    double buff;
    vector<int> a;
    a.resize(qu);
    for (int i = 0; i < qu; ++i)
        a[i] = 1;
    vector<vector<Point>> p;
    p.resize(qu);
    for (int i = 0; i < qu; ++i)
        p[i].push_back(point_[i]);
    ofstream out("ier.txt");
    for (int t = 0; t < (qu - 1); ++t)
    {
        buff = 20000;
        for (int i = 0; i < y; ++i)
        {
            if (a[i] == 1)
            {
                for (int j = 0; j < y; ++j)
                {
                    if ((metr(p[i], p[j]) < buff) && (i != j) && (a[j] == 1))
                    {
                        ind1 = i;
                        ind2 = j;
                        buff = metr(p[i], p[j]);
                    }
                }
            }
        }
        for (int i = 0; i < p[ind1].size(); ++i)
        {
            p[ind2].push_back(p[ind1][i]);
        }
        a[ind1] = 0;
        for (int i = 0; i < y; ++i)
        {
            if (a[i] == 1)
            {
                if (i == ind2)
                {
                    for (int j = 0; j < p[i].size(); ++j)
                        p[i][j].style(&out, i, 1);
                }
                else
                {
                    for (int j = 0; j < p[i].size(); ++j)
                        p[i][j].style(&out, i, 0);
                }
            }
        }
        out << "\n";
        out << "\n";
    }
    out.close();
    return 0;
}
int Ier::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
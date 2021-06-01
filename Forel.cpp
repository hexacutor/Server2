#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "Forel.h"
#include "methods.h"
int Forel::forel(double r, int d)
{
    int q = point_.size();
    int si = point_.size();
    int cen;
    vector <Point> p, cent;
    double x, y;
    int s;
    Point old;
    Point nov;
    ofstream out("forel.txt");
    ofstream out1("forelc.txt");
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
            p[i].fprintfcl(&out, cls);
        }
        nov.fprintfclr(&out1, cls, r);
        p.clear();
    }
    find_cl f(point_, o, (cls + 1), "Forel " + to_string(r) + ";Clusters:  " + to_string(cls), point_.size());
    find_cl_.push_back(f);
    r = r * 2;
    for (int t = 1; t < d; ++t)
    {
        out << "\n";
        out << "\n";
        out1 << "\n";
        out1 << "\n";
        cent = step(r, cent, t, &out, &out1);
        r = r * 2;
    }
    out.close();
    out1.close();
    return 12;
}
int Forel::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
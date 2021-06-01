#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "KM.h"
int KM::km(int k)
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
        for (int i = 0; i < point_.size(); ++i)
        {
            s = 10;
            clawn = cl;
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
            p[j].x_ = x / ss;
            p[j].y_ = y / ss;
        }
    } while (clawn != cl);
    ofstream out("dot2.txt");
    for (int j = 0; j < k; ++j)
    {
        for (int i = 0; i < point_.size(); ++i)
        {
            if (cl[i] == j)
            {
                point_[i].fprintfcl(&out, j);
            }
        }
    }
    out.close();
    find_cl f(point_, cl, k, "Kmeans " + to_string(k), point_.size());
    find_cl_.push_back(f);
    return 0;
}
int KM::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
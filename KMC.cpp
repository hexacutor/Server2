#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "KMC.h"
#include "methods.h"
int KMC::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
int KMC::kmcore(int k, int p)
{
    vector<vector<Point>> cen;
    vector<Point> buff;
    vector<int> cl;
    vector<int> clawn;
    double x, y, s;
    cen.resize(k);
    for (int i = 0; i < k; ++i)
        cen[i].resize(p);
    for (int i = 0; i < point_.size(); ++i)
    {
        cl.push_back(1);
        clawn.push_back(1);
    }
    for (int j = 0; j < k; ++j)
    {
        for (int i = 0; i < p; ++i)
        {
            x = 2 * (double)rand() / RAND_MAX - 1;
            y = 2 * (double)rand() / RAND_MAX - 1;
            cen[j][i].x_ = x;
            cen[j][i].y_ = y;
        }
    }
    ofstream out("kmy.txt");
    ofstream out1("kmcore.txt");
    do
    {
        clawn = cl;
        for (int i = 0; i < point_.size(); ++i)
        {
            s = 10;
            for (int j = 0; j < k; ++j)
            {
                for (int e = 0; e < p; ++e)
                {
                    if ((sqrt((point_[i].x() - cen[j][e].x()) * (point_[i].x() - cen[j][e].x()) + (point_[i].y() - cen[j][e].y()) * (point_[i].y() - cen[j][e].y()))) < s)
                    {
                        cl[i] = j;
                        s = sqrt((point_[i].x() - cen[j][e].x()) * (point_[i].x() - cen[j][e].x()) + (point_[i].y() - cen[j][e].y()) * (point_[i].y() - cen[j][e].y()));
                    }
                }
            }
        }
        for (int j = 0; j < k; ++j)
        {
            for (int i = 0; i < point_.size(); ++i)
            {
                if (cl[i] == j)
                {
                    buff.push_back(point_[i]);
                }
            }
            cen[j] = kmc(p, buff);
            buff.clear();
        }
    } while (cl != clawn);
    for (int j = 0; j < k; ++j)
    {
        for (int i = 0; i < point_.size(); ++i)
        {
            if (cl[i] == j)
            {
                point_[i].fprintfcl(&out, j);
            }
        }
        for (int i = 0; i < p; ++i)
        {
            cen[j][i].fprintfcl(&out1, j);
        }
    }
    out.close();
    out1.close();
    find_cl f(point_, cl, k, "Kmeans-core " + to_string(k) + " " + to_string(p), point_.size());
    find_cl_.push_back(f);
    return 0;
}
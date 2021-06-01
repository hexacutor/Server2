#pragma once
#include "Field.h"
#include "methods.h"
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001
Field::Field() = default;
int Field::fprintf(ofstream* out) const
{
    for (int i = 0; i < point_.size(); ++i)
    {
        point_[i].fprintf(out);
    }
    return 0;
}
int Field::fprintf_core(ofstream* out) const
{
    for (int i = 0; i < core_.size(); ++i)
    {
        core_[i].fprintf(out);
    }
    return 0;
}
int Field::fprintf_dust(ofstream* out) const
{
    for (int i = 0; i < dust_.size(); ++i)
    {
        dust_[i].fprintf(out);
    }
    return 0;
}
int Field::fprintf_coreLine(double del, ofstream* out) const
{
    int qu =  point_.size();
    for (int i = 0; i <  point_.size(); ++i)
    {
        if (point_[i].db == 2)
        {
            for (int j = 0; j <  point_.size(); ++j)
            {
                if (( matrix[qu * i + j] < del) && ( matrix[qu * i + j] > EPS))
                {
                    point_[i].fprintf(out);
                    point_[j].fprintfLine(out);
                }

            }
        }
    }
    return 0;
}


int Field::length() const
{
    return point_.size();
}
int Field::cmatrix()
{
    vector <double> x;
    vector <double> y;
    for (int i = 0; i < point_.size(); ++i)
    {
        x.push_back(point_[i].x());
        y.push_back(point_[i].y());
    }
    for (int i = 0; i < x.size(); ++i)
    {
        for (int j = 0; j < y.size(); ++j)
             matrix.push_back(sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])));
    }
     inf = 2;
    return 0;
}






int Field::fprintf_cl(ofstream* out, int por) const
{
    if (por > find_cl_.size())
    {
        return -1;
    }
    int i;
    for (i = 0; i < find_cl_[por - 1].q; ++i)
    {
        find_cl_[por - 1].point_[i].fprintfcl(out, find_cl_[por - 1].clus[i]);
    }
    return 0;
}
int Field::hist(int u)
{
    if (point_.size() == 0)
    {
        return -1;
    }
    double max = -100;
    double min = 100;
    vector<int> Histx(u);
    int t;
    for (int i = 0; i < point_.size(); ++i)
    {
        if (point_[i].x() > max)
            max = point_[i].x();
        if (point_[i].x() < min)
            min = point_[i].x();
    }
    for (int i = 0; i < point_.size(); ++i)
    {
        t = ((point_[i].x() - min) * u / (max - min));
        if (t == u)
            t--;
        Histx[t]++;
    }
    ofstream out("histx.txt");
    for (int i = 0; i < Histx.size(); ++i)
    {
        out << (i * (max - min) / u) + min << " " << Histx[i] << endl;
    }
    out.close();
    max = -100;
    min = 100;
    vector<int> Histy(u);
    for (int i = 0; i < point_.size(); ++i)
    {
        if (point_[i].y() > max)
            max = point_[i].y();
        if (point_[i].y() < min)
            min = point_[i].y();
    }
    for (int i = 0; i < point_.size(); ++i)
    {
        t = ((point_[i].y() - min) * u / (max - min));
        if (t == u)
            t--;
        Histy[t]++;
    }
    ofstream out1("histy.txt");
    for (int i = 0; i < Histy.size(); ++i)
    {
        out1 << (i * (max - min) / u) + min << " " << Histy[i] << endl;
    }
    out1.close();
    return 0;
};

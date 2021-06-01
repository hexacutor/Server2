#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "DBscan.h"
int DBscan::dbscan(double del, int k)
{
    int sch = 0;
    int qu = point_.size();
    vector<int> check(qu, 0);
    vector<int> dust(qu, 0);
    vector<int> buff;
    int t = 0;
    int z, lool,num,ind;   
    for (int i = 0; i < point_.size(); ++i)
    {
            for (int j = 0; j < point_.size(); ++j)
            {
                if ((matrix[qu * i + j] < del) && (matrix[qu * i + j] > EPS))
                {
                    sch = sch++; 
                }
            }
            buff.push_back(i);
            if (sch > k - 1)
                check[i] = 1;          
            sch = 0;
    }  
    for (int i = 0; i < point_.size(); ++i)         
    {
        if (check[i] == 1)
        {
            lool = 1000;
            ind = -1;
            for (int j = 0; j < point_.size(); ++j)
            {
                if ((check[j] == 1) && (matrix[qu * i + j] < del) && (matrix[qu * i + j] > EPS) && (matrix[qu * i + j] < lool))
                {
                    lool = matrix[qu * i + j]; if (dust[j] !=0) ind=dust[j];
                }
            }
            if (ind == -1)
            {
                t++;
                dust[i] = t;
            }
            else
            {
                dust[i] = ind;
            }
        }
    }
    for (int i = 0; i < point_.size(); ++i)
    {
        if (check[i] == 0)
        {
            num = -1;
            lool = 1000;
            for (int j = 0; j < point_.size(); ++j)
            {
                if ((check[j] == 1) && (matrix[qu * i + j] < del) && (matrix[qu * i + j] > EPS) && (matrix[qu * i + j] < lool))
                {
                    lool = matrix[qu * i + j]; num = j;
                }
            }
            if (num == -1) dust[i] = 0;
            else dust[i] = dust[num]; 
        }
    }
    for (int k = 1; k < t; ++k)
    {
        for (int l = 1; l < t; ++l)
        {
            if (l != k)
                ind = -1;
            {
                for (int i = 0; i < point_.size(); ++i)
                {
                    if (dust[i] == k)
                        for (int j = 0; j < point_.size(); ++j)
                        {
                            if (dust[j] == l)
                            {
                                if ( (matrix[qu * i + j] < del) && (matrix[qu * i + j] > EPS))
                                    ind = 0;
                            }
                        }
                }
                if (ind == 0)
                {
                    for (int i = 0; i < point_.size(); ++i)
                        if (dust[i] == k)
                            dust[i] = l;
                }
            }
        }
    }
    cout <<  "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << "\n";
    cout << t;
    find_cl F(point_, dust, t, "dbscan" + to_string(del), check.size());
    find_cl_.push_back(F);
    F.print("dbspr.txt");
    int r = 0;
    for (int i = 0; i < t; ++i)
    {
        for (int j = 0; j < point_.size(); ++j)
        {
            if (check[j] == t)
                r++;
        }
        cout << i <<" " <<r << "\n";
        r = 0;
    }
    return 0;
}
vector<int> DBscan::engage(vector<int> p,double del)
{
        int qu = p.size();
        for (int i = 0; i < point_.size(); ++i)
        {
            for (int j = 0; j < p.size(); ++j)
                if ((matrix[qu * i + j] < del) && (matrix[qu * i + j] > EPS))
                {
                    p.push_back(i);
                    break;
                }
        }
        return p;
}
int DBscan::binary(double r)
{
    binmatrix.clear();
    for (int i = 0; i < pow(point_.size(), 2); ++i)
    {
        if (matrix[i] < r)
            binmatrix.push_back(1);
        else
            binmatrix.push_back(0);
    }
    return 0;
}
int DBscan::cmatrix()
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
    return 0;
}
int DBscan::wave()
{
    if (binmatrix.size() == 0)
        return -1;
    else
    {
        ofstream out("wave.txt");
        ofstream out1("other.txt");
        int qu = point_.size();
        vector<int> check(qu);
        for (int i = 0; i < qu; ++i)
            check[i] = 0;
        int t = 1;
        for (int i = 0; i < qu; ++i)
        {
            for (int j = 0; j < qu; ++j)
            {
                if ((i != j) && (binmatrix[qu * i + j] == 1))
                {
                    out << point_[i].x() << " " << point_[i].y() << endl;
                    out << point_[j].x() << " " << point_[j].y() << endl;
                    out << "\n";
                    out << "\n";
                    if ((check[i] == 0) && (check[j] == 0))
                    {
                        check[i] = t;
                        check[j] = t;
                        t++;
                    }
                    else if
                        (check[i] == 0)
                        check[i] = check[j];
                    else if
                        (check[j] == 0)
                        check[j] = check[i];

                }
            }
        }
        find_cl(point_, check, t, "wave", check.size());
        for (int i = 0; i < qu; ++i)
        {
            if (check[i] == 0)
            {
                out1 << point_[i].x() << " " << point_[i].y() << endl;
            }
        }
        out.close();
        out1.close();
    }
    return 1;
}
int DBscan::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <vector>
#include "Mintree.h"
int Mintree::cmatrix()
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
int Mintree::stree(const string& tree, int r)
{    
        int qu =  point_.size();
        vector<int> vk;
        vector<int> vm;
        int k, m, t;
        double c;
        point_[0].st = 1;
        while (vk.size() <  point_.size() - 1)
        {
            c = 100;
            for (int i = 0; i <  point_.size(); ++i)
            {
                if (point_[i].st == 1)
                {
                    for (int j = 0; j <  point_.size(); ++j)
                    {
                        if ((point_[j].st != 1))
                        {
                            if ( matrix[qu * i + j] < c)
                            {
                                c =  matrix[qu * i + j];
                                k = j;
                                m = i;
                            }
                        }
                    }
                }
            }
            point_[k].st = 1;
            vk.push_back(k);
            vm.push_back(m);
        }
        ofstream out(tree);
        for (int i = 0; i < vm.size(); ++i)
        {
            out << point_[vk[i]].x() << " " << point_[vk[i]].y() << endl;
            out << point_[vm[i]].x() << " " << point_[vm[i]].y() << endl;
            out << "\n";
            out << "\n";
        }
        out.close();
        ofstream out1("hist.txt");
        vector<int> myVector(r);
        double max = 0;
        for (int i = 0; i < vm.size(); ++i)
        {
            if (matrix[qu * vm[i] + vk[i]] > max)
                max = matrix[qu * vm[i] + vk[i]];
        }
        for (int i = 0; i < vm.size(); ++i)
        {
            t = (matrix[qu * vm[i] + vk[i]] * r / max);
            if (t == r)
                t--;
            myVector[t]++;
        }
        for (int i = 0; i < myVector.size(); ++i)
        {
            out1 << (i * max / r) << " " << myVector[i] << endl;
        }
        out1.close();
        return 0; 
}
int Mintree::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
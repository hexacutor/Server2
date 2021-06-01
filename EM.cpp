#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#include <vector>
#include "EM.h"
#include "methods.h"
int EM::field(vector<Point> p)
{
    for (int j = 0; j < p.size(); ++j)
        point_.push_back(p[j]);
    return 0;
}
int EM::em(int k, ofstream* out)
{
    int siz = point_.size();
    int max = 0;
    vector<int> o;
    vector<vector<double>> ind;
    vector<Point> expect;
    double x, y, summ;
    for (int j = 0; j < k; ++j)
    {
        x = 2 * (double)rand() / RAND_MAX - 1;
        y = 2 * (double)rand() / RAND_MAX - 1;
        expect.emplace_back(x, y);
    }
    ind.resize(k);
    for (int i = 0; i < k; ++i)
        ind[i].resize(siz);
    vector<double> sigx;
    vector<double> sigy;
    vector<double> power(k);
    for (int i = 0; i < k; ++i)
    {
        power[i] = 1.0 / k;
    }
    summ = 0;
    for (int i = 0; i < k; ++i)
    {
        for (int j = 0; j < siz; ++j)
        {
            summ = summ + (point_[j].x() - expect[i].x()) * (point_[j].x() - expect[i].x());
        }
        summ = summ / (siz * k);
        sigx.push_back(sqrt(summ));
        printf("%lf  ", summ);
        summ = 0;
        for (int j = 0; j < siz; ++j)
        {
            summ = summ + (point_[j].y() - expect[i].y()) * (point_[j].y() - expect[i].y());
        }
        summ = summ / (siz * k);
        // printf("%f \n", summ);
        sigy.push_back(sqrt(summ));
        printf("%lf \n", summ);
        summ = 0;
    }//                   INIT         FDFDSAFASDF
    double PI = 3.1415;
    ofstream ell("ellipse.txt");
    for (int t = 0; t < 20; ++t)
    {

        for (int j = 0; j < siz; ++j)
        {
            summ = 0;
            for (int i = 0; i < k; ++i)
            {
                summ = summ + power[i] * (1 / (2 * PI * sigx[i] * sigy[i])) * exp(-0.5 * ((point_[j].x() - expect[i].x()) * (point_[j].x() - expect[i].x()) / (sigx[i] * sigx[i]) + (point_[j].y() - expect[i].y()) * (point_[j].y() - expect[i].y()) / (sigy[i] * sigy[i])));
            }
            for (int i = 0; i < k; ++i)
            {
                ind[i][j] = power[i] * (1 / (2 * PI * sigx[i] * sigy[i])) * exp(-0.5 * ((point_[j].x() - expect[i].x()) * (point_[j].x() - expect[i].x()) / (sigx[i] * sigx[i]) + (point_[j].y() - expect[i].y()) * (point_[j].y() - expect[i].y()) / (sigy[i] * sigy[i]))) / summ;
            }
        }
        for (int i = 0; i < k; ++i)
        {
            summ = 0;
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j];
            }
            power[i] = summ / siz; /// ves
            summ = 0;
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j] * (point_[j].x());
            }
            expect[i].x_ = summ / (power[i] * siz);  //// expext x
            summ = 0;
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j] * (point_[j].y());
            }
            expect[i].y_ = summ / (power[i] * siz);//// expext y
            summ = 0;
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j] * (point_[j].x() - expect[i].x()) * (point_[j].x() - expect[i].x());
            }
            summ = summ / (siz * power[i]);
            sigx[i] = sqrt(summ);//// dispx
            summ = 0;
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j] * (point_[j].y() - expect[i].y()) * (point_[j].y() - expect[i].y());
            }
            summ = summ / (siz * power[i]);
            sigy[i] = sqrt(summ);   /// dispy
            summ = 0;
        }
        for (int j = 0; j < siz; ++j)
        {
            summ = 0;
            for (int i = 0; i < k; ++i)
            {
                if (ind[i][j] > summ)
                {
                    summ = ind[i][j];
                    max = i;
                }
                // printf(" %d", ind[i][j]);
            }
            //printf(" \n");
            point_[j].fprintfcl(out, max);
            o.push_back(j);
        }
        point_[0].NN(out);
        summ = 0;
        for (int i = 0; i < k; ++i)
        {
            for (int j = 0; j < siz; ++j)
            {
                summ = summ + ind[i][j] * ((point_[j].x() - expect[i].x()) * (point_[j].x() - expect[i].x()) / (sigx[i] * sigx[i]) + (point_[j].y() - expect[i].y()) * (point_[j].y() - expect[i].y()) / (sigy[i] * sigy[i]));
            }
            ell << expect[i].x() << " " << expect[i].y() << " " << sigx[i] * sqrt(summ) / 3 << " " << sigy[i] * sqrt(summ) / 3 << endl;
            summ = 0;
        }
        ell << "\n";
        ell << "\n";
    }
    ell.close();
    find_cl f(point_, o, k, "EM " + to_string(k), point_.size());
    find_cl_.push_back(f);
    return 20;
}

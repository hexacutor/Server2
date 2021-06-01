#include "find_cl.h"
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001
find_cl::find_cl(vector<Point> p, vector<int> clo, int clusterqu, string s, int qqa)
{
    for (int i = 0; i < qqa; ++i)
    {
        point_.push_back(p[i]);
        clus.push_back(clo[i]);
    }
    q = clusterqu;
    info = s;
}
void find_cl::print(string filename)
{
    ofstream out(filename);
    for (int i = 0; i < point_.size(); ++i)
    {
        point_[i].fprintfcl(&out, clus[i]);
    }      
    out.close();
}
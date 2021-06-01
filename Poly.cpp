#include "methods.h"
void Poly::clear() { point_.clear(); q = 0; };
Poly::~Poly() { point_.clear(); };
Poly::Poly(vector<Point> p)
{
    for (int i = 0; i < p.size(); ++i)
        point_.emplace_back(p[i]);
    q = p.size();
}
#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001
#define M 100
#include "Cloud.h"
Cloud::Cloud(int length)
{
    for (int i = 0; i < length; ++i)
    {
        double x, y;
        x = y = 0;
        for (int j = 0; j < M; ++j)
        {
            x += (double)rand() / RAND_MAX - 0.5;
        }
        x /= M;
        for (int j = 0; j < M; ++j)
        {
            y += (double)rand() / RAND_MAX - 0.5;
        }
        y /= M;
        point_.emplace_back(x, y);
    }
}
Cloud::Cloud(int length, double c_x, double c_y, double disp_x, double disp_y)
{
    for (int i = 0; i < length; ++i)
    {
        double x = 0;
        double y = 0;
        for (int j = 0; j < M; ++j)
        {
            x += 2 * (double)rand() / RAND_MAX - 1;
        }
        x /= M;
        x *= disp_x;
        for (int j = 0; j < M; ++j)
        {
            y += 2 * (double)rand() / RAND_MAX - 1;
        }
        y /= M;
        y *= disp_y;
        x += c_x;
        y += c_y;
        point_.emplace_back(x, y);
    }
}
Cloud& Cloud::operator= (Cloud const& c)
{
    if (this != &c) {
        point_.clear();
        for (int i = 0; i < c.length(); ++i) {
            point_.push_back(c.point_[i]);
        }
    }
    return *this;
}
Cloud::Cloud(Cloud const& c)
{
    for (int i = 0; i < c.length(); ++i)
    {
        point_.push_back(c.point_[i]);
    }
}
Cloud::Cloud() = default;
int Cloud::length() const
{
    return point_.size();
}
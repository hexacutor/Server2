#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001
#include "Buffer.h"
#include "Cloud.h"
int Buffer::generate_cloud(double c_x, double c_y, double disp_x, double disp_y, int c_length)
{
    Cloud cloud(c_length, c_x, c_y, disp_x, disp_y);
    for (int i = 0; i < c_length; ++i)
    {
         point_.push_back(cloud.point_[i]);
    }
    return 0;
}
int Buffer::gen(int r)
{
    double x, y;
    for (int i = 0; i < r; ++i)
    {
        x = 2 * (double)rand() / RAND_MAX - 1;
        y = 2 * (double)rand() / RAND_MAX - 1;
        point_.emplace_back(x, y);
    }
    return 0;
}
int Buffer::rotate(double angle)
{
    for (int i = 0; i <  point_.size(); ++i)
    {
        point_[i].x_ = point_[i].x_ * cos(angle) - point_[i].y_ * sin(angle);
        point_[i].y_ = point_[i].x_ * sin(angle) + point_[i].y_ * cos(angle);
    }
    return 0;
}

int Buffer::shift(double x, double y)
{
    for (int i = 0; i <  point_.size(); ++i)
    {
        point_[i].x_ = point_[i].x_ + x;
        point_[i].y_ = point_[i].x_ + y;
    }
    return 0;
}
int Buffer::clear()
{
     point_.clear();
    return 0;
}

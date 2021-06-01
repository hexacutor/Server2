#include "Point.h"
Point::Point() : id_(0)
{
    x_ = 0;
    y_ = 0;
}

Point::Point(double x, double y) : x_(x), y_(y)
{
    static int quantity = 0;
    id_ = ++quantity;
    x_ = x;
    y_ = y;
}
double Point::f()
{
    return x_ * y_ + y_ * y_;
}
Point::Point(Point const& c) : x_(c.x()), y_(c.y()), id_(id())
{
}

double Point::x() const
{
    return x_;
}

double Point::y() const
{
    return y_;
}

int Point::fprintf(ofstream* out) const
{
    *out << x() << " " << y() << endl;
    return 0;
}
int Point::fprintfLine(ofstream* out) const
{
    *out << x() << " " << y() << endl;
    *out << "\n";
    *out << "\n";
    return 0;
}
int Point::NN(ofstream* out) const
{
    *out << "\n";
    *out << "\n";
    return 0;
}
int Point::fprintfcl(ofstream* out, int k) const
{
    int t = 1;
    int s = 1;
    int q = 1;
    for (int j = 0; j < 5; ++j)
    {
        t = t * (k + 35) % 256;
        q = q * (k + 95) % 256;
        s = s * (k + 138) % 256;
    }
    *out << x() << " " << y() << " " << t << " " << q << " " << s << endl;
    return 0;
}
int Point::fprintfred(ofstream* out) const
{
    *out << x() << " " << y() << " " << 255 << " " << 0 << " " << 0 << endl;
    return 0;
}
int Point::style(ofstream* out, int k, int r)
{
    int t = 1;
    int s = 1;
    int q = 1;
    for (int j = 0; j < 5; ++j)
    {
        t = t * (k + 35) % 256;
        q = q * (k + 95) % 256;
        s = s * (k + 138) % 256;
    }
    *out << x() << " " << y() << " " << t << " " << q << " " << s << " " << r << endl;
    return 0;
}
int Point::fprintfclr(ofstream* out, int k, double r) const
{
    int t = 1;
    int s = 1;
    int q = 1;
    for (int j = 0; j < 5; ++j)
    {
        t = t * (k + 35) % 256;
        q = q * (k + 95) % 256;
        s = s * (k + 138) % 256;
    }
    *out << x() << " " << y() << " " << t << " " << q << " " << s << " " << r << endl;
    return 0;
}


int Point::id() const
{
    return id_;
}
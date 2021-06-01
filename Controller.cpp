#define _CRT_SECURE_NO_WARNINGS
#define EPS 0.00001
#define EPS2 0.001
#include "Controller.h"
#include <time.h>
Controller::Controller(bool write_log) : write_log(write_log), field_(nullptr)
{
    if (write_log)
    {
        log_file_name = "logcontrol.txt";
        field_ = new Field();
        logger = ofstream(log_file_name, ios::app);
        struct tm* a;
        const time_t timer = time(NULL);
        a = localtime(&timer);
        logger << "\n";
        logger << a->tm_mday << "." << (a->tm_mon + 1) << " " << (a->tm_hour) << ":" << (a->tm_min) << ":" << (a->tm_sec) << " -- " << "NEW SESSION STARTED" << endl;
    }
}
int Controller::help(int id, string& file_name)
{
    file_name = "help.txt";
    log("Help file opened : help.txt ->correct");
    return 0;
}
int Controller::unload()
{
    if (field_ == nullptr) {
        field_ = new Field();
        log("Field Created");
    }
    log("Buffer unloaded");
    for (int i = 0; i < buff.point_.size(); ++i)
    {
        field_->point_.push_back(buff.point_[i]);
    }
    log("Unload->correct");
    return 0;
}
int Controller::DBSCAN(double del, int k)
{
    dbscan.field(field_->point_);
    dbscan.cmatrix();
    if (dbscan.dbscan(del, k) < 0)
    {
        log("DBscan(" + to_string(del) + "," + to_string(k) + ") ->error");
    }
    else
        log("DBscan(" + to_string(del) + "," + to_string(k) + ") ->correct");
    return 0;
}
int Controller::VORONOI()
{
    voronoi.field(field_->point_);
    if (voronoi.voronoi() < 0)
    {
        log("Voronoi ->error");
    }
    else
        log("Voronoi->correct");
    find_cl_.push_back(voronoi.find_cl_[voronoi.find_cl_.size() - 1]);
    return 0;
}
double Controller::inter(double x, double y)
{
    voronoi.field(field_->point_);
    cout << "\n" << "\n" << "\n" << "\n";
    cout << "Expectation:  " << x * y + y * y << "\n";
    cout << "Interpolation:  " << voronoi.inter(x, y) << "\n";
    cout << "Dif:  " << fabs(voronoi.inter(x, y) - x * y + y * y) << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n" << "\n";
    return voronoi.inter(x, y);
}
int Controller::Km(int k)
{
    voronoi.field(field_->point_);
    if (km.km(k) < 0)
    {
        log("Kmeans(" + to_string(k) + ") ->error");
    }
    else
        log("Kmeans(" + to_string(k) + ") ->correct");
    find_cl_.push_back(km.find_cl_[km.find_cl_.size() - 1]);
    return 0;
}
int Controller::infofc()
{
    if (field_->find_cl_.size() == 0)
    {
        return -1;
        log("Infofc ->error(No clusters yet)");
    }
    else
    {
        for (int i = 0; i < field_->find_cl_.size(); i++)
        {
            cout << field_->find_cl_[i].info << endl;
        }
        log("Infofc ->correct");
    }
    return 0;
}
int Controller::FOREL(double r, int d)
{
    forel.field(field_->point_);
    if (forel.forel(r, d) < 0)
    {
        log("Forel(" + to_string(r) + ") depth (" + to_string(d) + ") ->error");
    }
    else
        log("Forel(" + to_string(r) + ") depth (" + to_string(d) + ")  ->correct");
    find_cl_.push_back(forel.find_cl_[forel.find_cl_.size() - 1]);
    return 0;
}
int Controller::Kmc(int k, int p)
{
    kmc.field(field_->point_);
    if (kmc.kmcore(k, p) < 0)
    {
        log("KmeansCore(" + to_string(k) + "," + to_string(p) + ") ->error");
    }
    else
        log("KmeansCore(" + to_string(k) + "," + to_string(p) + ") ->correct");
    find_cl_.push_back(kmc.find_cl_[kmc.find_cl_.size() - 1]);
    return 0;
}
int Controller::tree(const string& tree, int m)
{
    mintree.field(field_->point_);
    if (mintree.stree(tree, m) < 0)
    {
        log("Tree ->error");
    }
    else
        log("Tree ->correct");
    return 0;
}
int Controller::IER()
{
    ier.field(field_->point_);
    if (ier.ier() < 0)
    {
        log("Hierarchy ->error");
    }
    else
        log("Hierarchy ->correct");
    return 0;
}
void Controller::log(const string& s)
{
    if (write_log)
    {
        struct tm* a;
        const time_t timer = time(NULL);
        a = localtime(&timer);
        logger << a->tm_mday << "." << (a->tm_mon + 1) << " " << (a->tm_hour) << ":" << (a->tm_min) << ":" << (a->tm_sec) << " -- " << s << endl;
    }
}
int Controller::fprintf(const string& file_name)

{

    ofstream out(file_name);

    field_->fprintf(&out);

    out.close();

    return 0;

}
int Controller::Em(const string& file_name, int m)
{
    ofstream out(file_name);
    em.field(field_->point_);
    if (em.em(m, &out) < 0)
    {
        log("ExpMax(" + to_string(m) + ") ->error");
    }
    else
        log("ExpMax(" + to_string(m) + ") ->correct");
    find_cl_.push_back(em.find_cl_[em.find_cl_.size() - 1]);
    out.close();
    return 0;
}
int Controller::fprintf_db(double del, const string& core, const string& Line, const string& dust)
{
    ofstream outc(core);
    ofstream outd(dust);
    ofstream outl(Line);
    field_->fprintf_core(&outc);
    field_->fprintf_coreLine(del, &outl);
    field_->fprintf_dust(&outd);
    outc.close();
    outd.close();
    outl.close();
    return 0;
}
int Controller::fprintf_cl(const string& out, int por)
{
    ofstream outcl(out);
    if (field_->fprintf_cl(&outcl, por) < 0)
    {
        log("Clusterization number (" + to_string(por) + ") ->error (out of range)");
    }
    else
        log("Clusterization number (" + to_string(por) + ") ->correct");
    outcl.close();
    return 0;
}
int Controller::cmatrix()
{
    return 0;
}
int Controller::hist(int u)
{
    if (field_->hist(u) < 0)
        log("Histogramm (" + to_string(u) + ") ->error");
    else
        log("Histogramm (" + to_string(u) + ") ->correct");
    return 0;
}
int Controller::binary(double r)
{
    return 0;
}
int Controller::wave()
{
    return 0;
}
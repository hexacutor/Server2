#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <vector>
#include "Field.h"
#include "Buffer.h"
#include "Forel.h"
#include "Ier.h"
#include "KM.h"
#include "KMC.h"
#include "Mintree.h"
#include "Voronoi.h"
#include "DBscan.h"
#include "EM.h"
class Controller
{
public:
    bool write_log;
    Field* field_;
    Controller(bool write_log);
    int help(int id, string& file_name);
    int unload();
    void log(const string& s);
    int fprintf(const string& file_name);
    int fprintf_cl(const string& file_name, int por);
    int Em(const string& file_name, int m);
    int cmatrix();
    int DBSCAN(double del, int k);
    int Km(int k);
    int IER();
    int VORONOI();
    double inter(double x, double y);
    int infofc();
    int binary(double r);
    int wave();
    int hist(int u);
    int FOREL(double r, int d);
    int Kmc(int k, int p);
    Buffer buff;
    int fprintf_db(double del, const string& core, const string& Line, const string& dust);
    int tree(const string& tree, int m);
    Mintree mintree;
    DBscan dbscan;
    KM km;
    KMC kmc;
    Ier ier;
    EM em;
    Voronoi voronoi;
    Forel forel;
private:
    string log_file_name;
    ofstream logger;
    vector<find_cl> find_cl_;
};
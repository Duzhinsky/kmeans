#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <time.h>
#include <cassert> // assert

using std::vector;

#define DataRow vector

template<class T>
class KMenas {
    public:
        KMenas(vector<DataRow<T>> &data);
        void solve(const int &clusters_count);

    private:
        void     select_centers(const int &clusters_count);
        double   distance(const DataRow<T> &lhs, const DataRow<T> &rhs);
        T        center(const T &lhs, const T &rhs);
        int      get_nearest_center(int i);

    private:
        int data_header_size = 0;
        int data_size = 0;
        vector<DataRow<T>> data;

    public:
        vector<DataRow<T>> centers;
        int MAX_ITERATIONS = 100;
        vector<vector<int>> clusters;
};

#include "kmeans.hpp"

#endif
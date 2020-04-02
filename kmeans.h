#ifndef   KMEANS_H
#define   KMEANS_H

#include  <limits> // numeric_limits
#include  <vector>
#include  <cstdlib>
#include  <cmath>
#include  <cstdint> //?
#include  <time.h>
#include  <cassert> // assert
#include "matplotlibcpp.h"

#include  "clustering_base.h"

namespace plt = matplotlibcpp;

template<class T>
class KMeans : public ClusteringInterface<T> { 
    public:
        KMeans();
		explicit KMeans(Vector<Vector<T>> *data);

    public:
        Vector<Vector<T>>& get_centers();
        void set_max_iterations(const size_t &val);

    public: // interface methods
        virtual void group(const size_t &clusters_count);
        virtual void set_data(Vector<Vector<T>> *data);
        virtual void display();
        virtual Vector<Vector<size_t>> membership_vector();

    private:
        void         select_centers(const size_t &clusters_count);
        long double  distance(const Vector<T> &lhs, const Vector<T> &rhs);
        long double  center(const long double &lhs, const long double &rhs);
        size_t       closest_center(const size_t &from_row);

    private:
        Vector<Vector<T>>            *data;
        Vector<Vector<size_t>>       membership;
        Vector<Vector<T>>  centers;

        size_t data_row_size = 0;
        size_t data_size;

        size_t MAX_ITERATIONS = 100;
}; // class KMeans

#include "kmeans.cpp"

#endif
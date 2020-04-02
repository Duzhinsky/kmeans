#ifndef CLUSTERING_BASE_H
#define CLUSTERING_BASE_H

#include <vector>

template<class T>
using Vector = std::vector<T>;

template<class T>
class ClusteringInterface {
    protected: 
        ClusteringInterface();
        ClusteringInterface(const ClusteringInterface &rhs);
        ~ClusteringInterface();

    public:
        virtual void group(const size_t &clusters_count) = 0;
        virtual void set_data(Vector<Vector<T>> *data) = 0;
        virtual void display() = 0;
        virtual Vector<Vector<size_t>> membership_vector() = 0;
};

#include "clustering_base.cpp"

#endif // CLUSTERING_BASE_H
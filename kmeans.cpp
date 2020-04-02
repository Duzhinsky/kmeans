#ifndef KMEANS_H
    #error "Do not compile kmeans.cpp!"
#endif


template<class T>
KMeans<T>::KMeans() {
}

template<class T>
KMeans<T>::KMeans(std::vector<Vector<T>> *data) : ClusteringInterface<T>() {
    set_data(data);
}   

template<class T>
void KMeans<T>::group(const size_t &clusters_count) {
    assert(clusters_count <= data_size);
    
    select_centers(clusters_count);
    Vector<Vector<size_t>> clusters_mem;

    for(size_t it = 0; it < MAX_ITERATIONS; ++it) {
        membership.clear();
        membership.assign(clusters_count, Vector<size_t>());
        
        for(size_t i = 0; i < data_size; ++i) {
            size_t nearest_center = closest_center(i);
            for(size_t k = 0; k < data_row_size; ++k) 
                centers[nearest_center][k] = center( (*data)[i][k], centers[nearest_center][k]);
        }

        for(size_t i = 0; i < data_size; ++i) {
            size_t nearest_center = closest_center(i);
            membership[nearest_center].push_back(i);
        }

        if(clusters_mem == membership) {
            break;
        }
        clusters_mem = membership;
    }

}

template<class T>
std::vector<Vector<T>>& KMeans<T>::get_centers() {
    return centers;
}

template<class T>
void KMeans<T>::set_max_iterations(const size_t &val) {
    MAX_ITERATIONS = val;
}

template<class T>
void KMeans<T>::set_data(Vector<Vector<T>> *data_p) {
    assert(data_p != 0); 
    assert(data_p != nullptr);
    assert(data_p->size() > 0);
    data = data_p;
    data_row_size = (*data)[0].size();
    data_size = data->size();
}

template<class T>
void KMeans<T>::display() {
    // TODO refactor this <== temporary solution

    Vector<double> x;
    Vector<double> y;
    plt::xlim(0, 150);
    plt::ylim(0, 150);
    std::string colors[] = {"#ff1100", "#00ff11", "#1100ff", "#fe00ef", "#7A6BFF", "#5FFFF2", "#FFC0AD", "#E8E192", "#EBB950"};
    for(int i = 0; i < membership.size(); ++i) {
        x.clear();
        y.clear();
        for(int k = 0; k < membership[i].size(); ++k) {
            x.push_back((*data)[membership[i][k]][0]);
            y.push_back((*data)[membership[i][k]][1]);
        }
        plt::scatter(x, y, 40, {{"alpha","0.8"}, {"c",colors[i]}});
    }
    x.clear();
    y.clear();
    for(int i = 0; i < centers.size(); ++i) {
        x.push_back(centers[i][0]);
        y.push_back(centers[i][1]);
    }
    plt::scatter(x, y, 80, {{"alpha","0.95"}, {"c","#000000"}});
    plt::title("With");
    plt::show();
}

template<class T>
Vector<Vector<size_t>> KMeans<T>::membership_vector() {
    return membership;
}

template<class T>
void KMeans<T>::select_centers(const size_t &clusters_count) {
    centers.clear();
    centers.assign(clusters_count, std::vector<T>(data_row_size));
  
    srand(time(NULL));

    for(size_t i = 0; i < clusters_count; ++i) {
        size_t ri = rand() % data_size;
        centers[i] = (*data)[ri];
        for(size_t k = 0; k < clusters_count; ++k) {
            if(centers[i] == centers[k] && k != i) {
                --i;
                break;
            }
        }

    }
}

template<class T>
long double KMeans<T>::center(const long double &lhs, const long double &rhs) {
    return (lhs + rhs)/2;
}

template<class T>
long double KMeans<T>::distance(const Vector<T> &lhs, const Vector<T> &rhs) {
    long double amount = 0;
    for(size_t i = 0; i < data_row_size; ++i)
        amount += (lhs[i] - rhs[i])*(lhs[i] - rhs[i]);
    return sqrt(amount);
}

template<class T>
size_t KMeans<T>::closest_center(const size_t &from_row) {
    size_t nearest_center = 0;
    long double min_distance_center = std::numeric_limits<long double>::max();
    for(size_t i = 0; i < centers.size(); ++i) {
        long double dist = distance((*data)[from_row], centers[i]);
        if(dist < min_distance_center) {
            nearest_center = i;
            min_distance_center = dist;
        }
    }
    return nearest_center;
}

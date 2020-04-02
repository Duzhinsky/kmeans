
template<class T>
KMenas<T>::KMenas(vector<DataRow<T>> &data_p) {
    data = data_p;
    data_size = data.size();
    assert(data_size != 0);
    data_header_size = data[0].size();
}

template<class T>
void KMenas<T>::select_centers(const int &clusters_count) {
    centers.clear();
    centers.assign(clusters_count, vector<T>());
    srand(time(NULL));
    for(int i = 0; i < clusters_count; ++i) {
        int ri = rand() % data_size;
        centers[i] = data[ri];
        for(int k = 0; k < clusters_count; ++k) {
            if(centers[i] == centers[k] && i != ri) {
                --i;
                break;
            }
        }
    }
}

template<class T>
double KMenas<T>::distance(const DataRow<T> &lhs, const DataRow<T> &rhs) {
    long double sum = 0;
    for(int i = 0; i < data_header_size; ++i) {
        sum += (lhs[i]-rhs[i])*(lhs[i]-rhs[i]);
        // sum += abs(lhs[i]-rhs[i]);
    }
    return sqrt(sum);
}

template<class T>
T KMenas<T>::center(const T &lhs, const T &rhs) {
    return (lhs + rhs)/2;
}

template<class T>
int KMenas<T>::get_nearest_center(int i) {
    int nearest_center = 0;
    int min_distance_center = INT32_MAX;
    double tmpdist;
    int clusters_count = clusters.size();
    for(int k = 0; k < clusters_count; ++k) {
        tmpdist = distance(data[i], centers[k]);
        if(tmpdist < min_distance_center) {
            nearest_center = k;
            min_distance_center = tmpdist;
        }
    }
    return nearest_center;
}

#include <iostream>
using std::cout;

template<class T>
void KMenas<T>::solve(const int &clusters_count) {
    select_centers(clusters_count);
    vector<vector<int>> clusters_mem;
    std::vector<vector<int>> diff;

    for(int it = 0; it < MAX_ITERATIONS; ++it) {
        clusters.clear();
        clusters.assign(clusters_count, vector<int>());
        for(int i = 0; i < data_size; ++i) {
            int nearest_center = get_nearest_center(i);
            for(int k = 0; k < data_header_size; ++k) {
                centers[nearest_center][k] = center(data[i][k], centers[nearest_center][k]);
            }
        }
        for(int i = 0; i < data_size; ++i) { 
            int nearest_center = get_nearest_center(i);
            clusters[nearest_center].push_back(i);
        }
        // cout << "==========\n";
        // for(int i = 0; i < clusters_count; ++i) {
        //     cout << "CLUSTER::::: ";
        //     for(int k = 0; k < clusters[i].size(); ++k)
        //         cout << clusters[i][k] << " ";
        //     cout << "\n";
        // }
        diff.clear();
        if(it >= 500)
        std::set_difference(clusters.begin(), clusters.end(), clusters_mem.begin(), clusters_mem.end(), 
                            std::inserter(diff, diff.begin()));

        if(clusters_mem == clusters) {
            cout << "END at IT: " << it << "\n";
            break;
        }
        clusters_mem = clusters;
        cout << "it: " << it << "\n";
        for(int i = 0; i < diff.size(); ++i) {
            cout << " ===> " << diff[i].size() << "\n";
            // for(int k = 0; k < diff[i].size(); ++k)
            //     cout << diff[i][k] << " "; 
            // cout << "\n";
        }
    }
}

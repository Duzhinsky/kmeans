#include "fast-cpp-csv-parser/csv.h"
#include "kmeans.h"
#include <vector>

using namespace std;
using io::CSVReader;

int main() {
    CSVReader<2> in("datasets/xy.csv");
    in.read_header(io::ignore_extra_column, "x","y");
    vector<vector<double>> xy;

    double x_tmp, y_tmp;
    while(in.read_row(x_tmp, y_tmp)) {
        xy.push_back({x_tmp, y_tmp});
    }

    KMeans<double> km(&xy);
    cout << "Start solving\n";
    km.group(7);
    cout << "[OK]Solved!\n";
    km.display();
    return 0;
}


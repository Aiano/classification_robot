#include "knn.h"
#include <iostream>

using namespace std;

int main() {
        knn KNN("data.dat");
        std::vector<float> sample = {1,5};
        int predictLabel = KNN.predict(sample);
        std::cout << predictLabel << std::endl;
        return 0;
}
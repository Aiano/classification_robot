#include "knn/knn.h"
#include <iostream>

using namespace std;

int main() {
        knn KNN("data.dat");
        std::vector<float> sample = {3,4};
        int predictLabel = KNN.predict(sample);
        std::cout << predictLabel << std::endl;
        return 0;
}
//
// Created by aiano on 2020/1/24.
//

#ifndef CLASSIFICATION_ROBOT_KNN_H
#define CLASSIFICATION_ROBOT_KNN_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

class knn {
public:
    knn(int dimen = 1);

    knn(std::string file);

    bool addSample(std::vector<float> sample, int label);

    bool save(std::string file);

    int predict(std::vector<float> predictSample);

    ~knn();

private:
    int dimension = 1;
    int sampleNumber = 0;
    std::vector<std::vector<float>> samples;
    std::vector<int> labels;
};

#endif //CLASSIFICATION_ROBOT_KNN_H

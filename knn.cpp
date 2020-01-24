//
// Created by aiano on 2020/1/24.
//

#include "knn.h"

knn::knn(int dimen) {
        dimension = dimen;
}

knn::knn(std::string file) {
        std::fstream inFile;
        inFile.open(file, std::ios::in);
        inFile >> dimension;
        std::cout << "Dimension : " << dimension << std::endl;
        inFile >> sampleNumber;
        std::cout << "Sample number : " << sampleNumber << std::endl;

        float bit;
        for (int i = 0; i < sampleNumber; i++) {
                std::vector<float> sample;
                std::cout << "Sample " << i + 1 << " : ";
                for (int j = 0; j < dimension; j++) {
                        inFile >> bit;
                        std::cout << bit << " ";
                        sample.push_back(bit);
                }
                inFile >> bit;
                std::cout << "Label : " << bit << std::endl;
                samples.push_back(sample);
                labels.push_back(bit);
        }
}

bool knn::addSample(std::vector<float> sample, int label) {
        samples.push_back(sample);
        labels.push_back(label);
        sampleNumber = samples.size();
        return true;
}

bool knn::save(std::string file) {
        std::fstream outFile;
        outFile.open(file, std::ios::out | std::ios::trunc);
        outFile << std::to_string(dimension) << std::endl;
        outFile << std::to_string(sampleNumber) << std::endl;

        for (int i = 0; i < samples.size(); i++) {
                for (int j = 0; j < dimension; j++) {
                        outFile << std::to_string(samples[i][j]) << " ";
                }
                outFile << std::to_string(labels[i]) << std::endl;
        }

        outFile.close();
}

int knn::predict(std::vector<float> predictSample) {
        int result = 0;
        float minDistance=99999999,distance;
        for (int i = 0; i < sampleNumber; i++) {
                float sum=0;
                for(int j=0;j<dimension;j++){
                        sum+=pow(samples[i][j] - predictSample[j],2);
                }
                distance=sqrt(sum);
                if(distance<minDistance){
                        minDistance=distance;
                        result=labels[i];
                }
        }

        return result;
}

knn::~knn() {

}



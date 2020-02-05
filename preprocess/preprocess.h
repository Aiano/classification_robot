#ifndef CLASSIFICATION_ROBOT_PREPROCESS_H
#define CLASSIFICATION_ROBOT_PREPROCESS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

#define AREA_LOWER_LIMIT 50
#define AREA_SCALING_DOWN_DIVISOR 1

bool process(const cv::Mat &input, const cv::Mat &background, cv::Mat &output);

bool drawDivision(const cv::Mat &input, cv::Mat &drawnOutput, std::vector<std::vector<float>> &samples,
                  std::vector<std::vector<int>> &positions, const int sample_dimension = 2);//area, ar

#endif //CLASSIFICATION_ROBOT_PREPROCESS_H
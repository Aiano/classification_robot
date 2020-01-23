#ifndef CLASSIFICATION_ROBOT_PREPROCESS_H
#define CLASSIFICATION_ROBOT_PREPROCESS_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

bool process(const cv::Mat &input, const cv::Mat &background, cv::Mat &output);

bool drawDivision(const cv::Mat &input, cv::Mat &drawnOutput);

#endif //CLASSIFICATION_ROBOT_PREPROCESS_H
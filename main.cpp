#include <opencv2/opencv.hpp>
#include "preprocess.h"
#include "knn.h"

#define CAMERA_ID 0
//#define ADD_SAMPLE_MODE
#define KNN_DIMENSION 2

int main() {
        cv::VideoCapture cap(CAMERA_ID);
        if (!cap.isOpened()) {
                std::cerr << "Can't open camera." << std::endl;
                return -1;
        }

        std::vector<std::vector<float>> samples;
        std::vector<std::vector<int>> positions;

#ifdef ADD_SAMPLE_MODE
        knn KNN(KNN_DIMENSION);
#else
        knn KNN("data.dat");
#endif

        cv::Mat frame, backGround, result;
        while (true) {
                cap >> frame;

                cv::imshow("Frame", frame);
                int key = cv::waitKey(23);
                if (key == 27) break;
                else if (key == 'b') {
                        backGround = frame.clone();
                        cv::imshow("Background", backGround);
                        cv::waitKey(0);
                        cv::destroyWindow("Background");
                } else if (key == 'p') {
                        process(frame, backGround, result);
                        cv::imshow("Result", result);
                        cv::waitKey(0);
                        cv::destroyWindow("Result");
                        drawDivision(result, result, samples, positions, 2);
#ifndef ADD_SAMPLE_MODE
                        for (int i = 0; i < samples.size(); i++) {
                                std::cout << "Object " << i+1 << " with label: " << KNN.predict(samples[i])
                                          << " and position: [x:" << positions[i][0] << ",y:" << positions[i][1] << "]"
                                          << std::endl;
                        }
#endif
                        cv::imshow("Result", result);
                        cv::waitKey(0);
                        cv::destroyWindow("Result");
                }
#ifdef ADD_SAMPLE_MODE
                else if (key == 'a') {
                        int label;
                        char y_or_n;
                        std::cout << "We get " << samples.size() << " sample(s)" << std::endl;
                        std::cout << "Please input their label :";
                        std::cin >> label;
                        std::cout << "Please confirm the label " << label << " [y/n]" << std::endl;
                        std::cin >> y_or_n;
                        if (y_or_n == 'y') {
                                for (int i = 0; i < samples.size(); i++)
                                        KNN.addSample(samples[i], label);
                                std::cout<<"Adding succeed."<<std::endl;
                        } else {
                                std::cout << "Adding has been canceled." << std::endl;
                        }
                } else if (key=='s'){
                        KNN.save("data.dat");
                        std::cout<<"Saving succeed."<<std::endl;
                }
#endif
        }
        return 0;
}
//
// Created by aiano on 2020/1/23.
//

#include "preprocess.h"

bool process(const cv::Mat &input, const cv::Mat &background, cv::Mat &output) {
        if (input.empty()) {
                std::cout << "Input image is empty" << std::endl;
                return false;
        }

        //copy
        cv::Mat temporaryInput;
        cv::Mat temporaryBackground;
        cv::Mat aux;

        //to gray
        cv::cvtColor(input, temporaryInput, cv::COLOR_BGR2GRAY);
        cv::cvtColor(background, temporaryBackground, cv::COLOR_BGR2GRAY);

        //median blur
        cv::medianBlur(temporaryInput, temporaryInput, 3);
        cv::medianBlur(temporaryBackground, temporaryBackground, 3);

        /*
        optical elimination
        There are two methods ,we choose subtraction
        Method subtraction:
        if we have an "Optical pattern" L and a "Image" I
        the "result" R=L - I
        */
        aux = temporaryBackground - temporaryInput;

        //threshold
        cv::threshold(aux, output, 30, 255, cv::THRESH_BINARY);
}

bool drawDivision(const cv::Mat &input, cv::Mat &drawnOutput) {
        //connected components
        cv::Mat lables, stats, centroids;
        cv::Mat img = input.clone();
        auto num_objects = cv::connectedComponentsWithStats(input, lables, stats, centroids, 8);
        if (num_objects < 2) {
                std::cout << "Find nothing." << std::endl;
                return true;
        }
        std::cout << "Find " << num_objects - 1 << " object(s)." << std::endl;
        drawnOutput = cv::Mat::zeros(input.rows, input.cols, CV_8UC3);
        for (auto i = 1; i < num_objects; i++) {
                std::cout << "Object " << i << " with position: " << centroids.at<cv::Point2d>(i) << " and area: "
                          << stats.at<int>(i, cv::CC_STAT_AREA) << std::endl;
                cv::Mat mask = lables == i;
                int l=stats.at<int>(i, cv::CC_STAT_LEFT);
                int t=stats.at<int>(i, cv::CC_STAT_TOP);
                int w=stats.at<int>(i, cv::CC_STAT_WIDTH);
                int h=stats.at<int>(i, cv::CC_STAT_HEIGHT);
                drawnOutput.setTo(rand() % 100 + 1, mask);
                if (stats.at<int>(i, cv::CC_STAT_AREA) > 50){
                        cv::putText(drawnOutput, "Area: " + std::to_string(stats.at<int>(i, cv::CC_STAT_AREA)),
                                    centroids.at<cv::Point2d>(i), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 255, 255));
                        //cv::rectangle(drawnOutput, cv::Point(l, t), cv::Point(l + w, t + h), cv::Scalar(255, 255, 255));
                }
        }

        //contours
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(img, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
        for (int i = 0; i < contours.size(); i++) {
                cv::Mat mask = cv::Mat::zeros(img.rows, img.cols, CV_8UC1);
                cv::drawContours(mask, contours, i, cv::Scalar(1), cv::FILLED, cv::LINE_8, hierarchy, 1);
                cv::Scalar area_s = cv::sum(mask);
                float area = area_s[0];
                if (area > 50) {
                        cv::RotatedRect r = cv::minAreaRect(contours[i]);
                        float width = r.size.width;
                        float height = r.size.height;
                        float ar = (width < height) ? height / width : width / height;
                        cv::ellipse(drawnOutput,r,cv::Scalar(255,255,255));
                        cv::putText(drawnOutput,"ar: " +std::to_string(ar),cv::Point(r.center.x,r.center.y+15),cv::FONT_HERSHEY_PLAIN,1,cv::Scalar(255,255,255));
                }
        }
}


#include <opencv2/opencv.hpp>
#include "preprocess.h"
#include "knn.h"

#define CAMERA_ID 0
int main(){
        cv::VideoCapture cap(CAMERA_ID);
        if(!cap.isOpened()){
                std::cerr<<"Can't open camera."<<std::endl;
                return -1;
        }

        cv::Mat frame,backGround,result;
        while(true){
                cap>>frame;

                cv::imshow("Frame",frame);
                int key=cv::waitKey(23);
                if(key==27) break;
                else if(key=='b'){
                        backGround=frame.clone();
                        cv::imshow("Background",backGround);
                        cv::waitKey(0);
                        cv::destroyWindow("Background");
                } else if (key=='p'){
                        process(frame,backGround,result);
                        cv::imshow("Result",result);
                        cv::waitKey(0);
                        cv::destroyWindow("Result");
                        drawDivision(result,result);
                        cv::imshow("Result",result);
                        cv::waitKey(0);
                        cv::destroyWindow("Result");
                }
        }
        return 0;
}
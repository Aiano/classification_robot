cmake_minimum_required(VERSION 3.15)
project(classification_robot)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)

add_executable(classification_robot main.cpp preprocess.cpp preprocess.h knn.cpp knn.h)

add_executable(testKnn knn.cpp knn.h testKnn.cpp)

target_link_libraries(classification_robot ${OpenCV_LIBS})
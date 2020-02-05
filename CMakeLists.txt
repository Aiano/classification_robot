cmake_minimum_required(VERSION 3.15)
project(classification_robot)
set(CMAKE_CXX_STANDARD 11)


find_package(OpenCV REQUIRED)

add_subdirectory(preprocess)
add_subdirectory(knn)

add_executable(classification_robot main.cpp)
target_link_libraries(classification_robot Preprocess Knn)

add_executable(testKnn testKnn.cpp)
target_link_libraries(testKnn Knn)
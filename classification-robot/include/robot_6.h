#ifndef CLASSIFICATION_ROBOT_ROBOT_6_H
#define CLASSIFICATION_ROBOT_ROBOT_6_H

#include <assert.h>
#include <math.h>
#define PI 3.14159

class robot_6
{
public:
    robot_6(float L1, float L2, float L3, float L4, float L5, float S1, float S2, float S3, float S4, float X_lower_limit, float X_upper_limit,
            float Y_lower_limit, float Y_upper_limit, float Z_lower_limit, float Z_upper_limit);

    void get_rotate_degree(const float &x, const float &y, const float &z, float &t1, float &t2, float &t3, float &t4);

    ~robot_6();

private:
    float l1, l2, l3, l4, l5;
    float s1, s2, s3, s4;
    float x_lower_limit, x_upper_limit;
    float y_lower_limit, y_upper_limit;
    float z_lower_limit, z_upper_limit;
};

#endif //CLASSIFICATION_ROBOT_ROBOT_6_H

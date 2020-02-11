#include "robot_6.h"

robot_6::robot_6(float L1, float L2, float L3, float L4, float L5, float S1, float S2, float S3, float S4, float X_lower_limit, float X_upper_limit,
                 float Y_lower_limit, float Y_upper_limit, float Z_lower_limit, float Z_upper_limit)
{
        assert(L1 > 0 && L2 > 0 && L3 > 0 && L4 > 0 && L5 > 0);
        assert(X_upper_limit - X_lower_limit > 0 && Y_upper_limit - Y_lower_limit > 0 &&
               Z_upper_limit - Z_lower_limit > 0);

        l1 = L1;
        l2 = L2;
        l3 = L3;
        l4 = L4;
        l5 = L5;
        s1 = S1;
        s2 = S2;
        s3 = S3;
        s4 = S4;
        x_lower_limit = X_lower_limit;
        x_upper_limit = X_upper_limit;
        y_lower_limit = Y_lower_limit;
        y_upper_limit = Y_upper_limit;
        z_lower_limit = Z_lower_limit;
        z_upper_limit = Z_upper_limit;
}

robot_6::~robot_6()
{
}

void robot_6::get_rotate_degree(const float &x, const float &y, const float &z, float &t1, float &t2, float &t3, float &t4)
{
        float d1 = sqrt(pow(x, 2) + pow(y, 2));

        float d2 = d1 - l2;
        float d3 = sqrt(pow(l1, 2) + pow(d2, 2));
        float b1 = atan(l1 / d2) / PI * 180;
        float b2 = 90 - b1;
        float d4 = z + l5;
        float d5 = sqrt(pow(d3, 2) + pow(d4, 2) - 2 * d3 * d4 * cos(b2 / 180 * PI));

        float a1 = (atan(d2 / l1) / PI * 180) + (acos((pow(d3, 2) + pow(d5, 2) - pow(d4, 2)) / (2 * d3 * d5)) / PI * 180) +
                   (acos((pow(d5, 2) + pow(l3, 2) - pow(l4, 2)) / (2 * d5 * l3)) / PI * 180) - 90;
        float a2 = 180 - (acos((pow(l3, 2) + pow(l4, 2) - pow(d5, 2)) / (2 * l3 * l4)) / PI * 180);
        float a3 = 180 - ((acos((pow(d4, 2) + pow(d5, 2) - pow(d3, 2)) / (2 * d4 * d5)) / PI * 180) +
                          (acos((pow(l4, 2) + pow(d5, 2) - pow(l3, 2)) / (2 * l4 * d5)) / PI * 180));
        float a4 = atan(x / y) / PI * 180;

        float s5 = sqrt(pow(s1, 2) + pow(s2, 2) - 2 * s1 * s2 * cos(a2 / 180 * PI));
        float k1=(acos((pow(s1, 2) + pow(s5, 2) - pow(s2, 2)) / (2 * s1 * s5)) / PI * 180);
        float k2=(acos((pow(s4, 2) + pow(s5, 2) - pow(s3, 2)) / (2 * s4 * s5)) / PI * 180);
        t1 = 180 - a1;
        t2 = a1+k1+k2-90;
        t3= a3+98;
        t4 = 95 + a4;
        
}

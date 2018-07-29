// Copyright © 2018 Naoki Akai. All rights reserved.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <geometry_msgs/Quaternion.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <utility_funcs.hpp>

// random
inline double rand_normal(double mu, double sigma) {
    double r = rand_normal_cos(mu, sigma);
    return r;
}

inline double rand_normal_cos(double mu, double sigma) {
    double r = mu + sigma * sqrt(-2.0 * log((double)rand() / RAND_MAX) ) * cos(2.0 * M_PI * rand() / RAND_MAX);
    return r;
}

inline double rand_normal_sin(double mu, double sigma) {
    double r = mu + sigma * sqrt(-2.0 * log((double)rand() / RAND_MAX) ) * sin(2.0 * M_PI * rand() / RAND_MAX);
    return r;
}

// angle
inline double modify_angle_value(double angle) {
    double pi2 = 2.0 * M_PI;
    while (angle < -M_PI)
        angle += pi2;
    while (angle > M_PI)
        angle -= pi2;
    return angle;
}

// visualize
inline void value2rgb_heatmap(double value, int* r, int* g, int* b) {
    double tmp_val = cos(4.0 * M_PI * value);
    int col_val = (int)(( -tmp_val / 2.0 + 0.5) * 255.0);
    if (value >= (4.0 / 4.0)) {
        *r = 255, *g = 0, *b = 0;
    } else if (value >= (3.0 / 4.0)) {
        *r = 255, *g = col_val, *b = 0;
    } else if (value >= (2.0 / 4.0)) {
        *r = col_val, *g = 255, *b = 0;
    } else if (value >= (1.0 / 4.0)) {
        *r = 0, *g = 255, *b = col_val;
    } else if (value >= (0.0 / 4.0)) {
        *r = 0, *g = col_val, *b = 255;
    } else {
        *r = 0, *g = 0, *b = 255;
    }
}

// ros geometry
inline void quaternion2rpy(geometry_msgs::Quaternion quat, double* roll, double* pitch, double* yow) {
    tf::Quaternion q(quat.x, quat.y, quat.z, quat.w);
    tf::Matrix3x3 m(q);
    m.getRPY(*roll, *pitch, *yow);
}

inline geometry_msgs::Quaternion rpy2quaternion(double roll, double pitch, double yaw) {
    tf::Quaternion q;
    q.setRPY(roll, pitch, yaw);
    geometry_msgs::Quaternion quat;
    quat.x = q.getX();
    quat.y = q.getY();
    quat.z = q.getZ();
    quat.w = q.getW();
    return quat;
}

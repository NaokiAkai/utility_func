// Copyright © 2018 Naoki Akai. All rights reserved.

#ifndef __UTILITY_FUNCS_HPP__
#define __UTILITY_FUNCS_HPP__

#include <geometry_msgs/Quaternion.h>

/*
    in: average (mu) and standard deviation (sigma)
    out: random value based on normal distribution
 */
inline double rand_normal(double mu, double sigma); // this is equal to rand_normal_cos()
inline double rand_normal_cos(double mu, double sigma);
inline double rand_normal_sin(double mu, double sigma);

/*
    in: angle
    out: angle (-pi to pi)
 */
inline double modify_angle_value(double angle);

/*
    in: value
    out: rgb values (0 to 255)
    example: value2rgb_heatmap((value - min) / (max - min)), &r, &g, &b);
 */
inline void value2rgb_heatmap(double value, int* r, int* g, int* b);

/*
    in: quaternion
    out: roll, pitch, and yaw angles
 */
inline void quaternion2rpy(geometry_msgs::Quaternion quat, double* roll, double* pitch, double* yow);
inline geometry_msgs::Quaternion rpy2quaternion(double roll, double pitch, double yaw);

#endif /* __UTILITY_FUNCS_HPP__ */

// Copyright © 2018 Naoki Akai. All rights reserved.

#ifndef __UTILITY_FUNCS_HPP__
#define __UTILITY_FUNCS_HPP__

#include <std_msgs/Time.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

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
    out: roll, pitch, and yaw angles in radian
 */
inline void quaternion2rpy(geometry_msgs::Quaternion quat, double* roll, double* pitch, double* yow);

/*
    in: roll, pitch, and yaw angles in radian
    out: quaternion
 */
inline geometry_msgs::Quaternion rpy2quaternion(double roll, double pitch, double yaw);

namespace utility_funcs {

class TFUtility {
  private:
    tf::TransformListener* tf_listener;
    tf::StampedTransform transform;
    std::string parent_frame_id, child_frame_id;

  public:
    TFUtility() {
        tf_listener = new tf::TransformListener();
    }

    TFUtility(std::string parent, std::string child) {
        tf_listener = new tf::TransformListener();
        parent_frame_id = parent;
        child_frame_id = child;
    }

    ~TFUtility() {
        delete tf_listener;
    }

    bool lookup_transform(ros::Time stamp, double duration) {
        try {
            tf_listener->waitForTransform(parent_frame_id, child_frame_id, stamp, ros::Duration(duration));
            tf_listener->lookupTransform(parent_frame_id, child_frame_id, stamp, transform);
            return true;
        } catch (tf::TransformException ex) {
            ROS_ERROR("%s", ex.what());
            return false;
        }
    }

    bool lookup_transform(std::string parent, std::string child, ros::Time stamp, double duration) {
        try {
            tf_listener->waitForTransform(parent, child, stamp, ros::Duration(duration));
            tf_listener->lookupTransform(parent, child, stamp, transform);
            return true;
        } catch (tf::TransformException ex) {
            ROS_ERROR("%s", ex.what());
            return false;
        }
    }

    tf::StampedTransform get_transform(void) {
        return transform;
    }

    void get_xyzrpy(double* x, double* y, double* z, double* roll, double* pitch, double* yaw) {
        *x = transform.getOrigin().x();
        *y = transform.getOrigin().y();
        *z = transform.getOrigin().z();
        tf::Quaternion q(transform.getRotation().x(), transform.getRotation().y(),
            transform.getRotation().z(), transform.getRotation().w());
        tf::Matrix3x3 m(q);
        m.getRPY(*roll, *pitch, *yaw);
    }
};

}

#endif /* __UTILITY_FUNCS_HPP__ */

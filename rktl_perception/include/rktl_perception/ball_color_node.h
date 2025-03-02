/* Node to detect the ball's position on the field.
 * License:
 *   BSD 3-Clause License
 *   Copyright (c) 2020, Autonomous Robotics Club of Purdue (Purdue ARC)
 *   All rights reserved.
 */

#pragma once

/* ros */
#include <ros/ros.h>
#include <ros/console.h>

/* image */
#include <image_transport/image_transport.h>
#include <image_transport/camera_subscriber.h>
#include <image_geometry/pinhole_camera_model.h>


/* opencv */
#include <opencv2/opencv.hpp> 
#include <opencv2/imgproc.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/core/types.hpp>
#include <cv_bridge/cv_bridge.h> 

/* messages */
#include <geometry_msgs/Vector3Stamped.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

/* math & vectors */
#include <vector>
#include <math.h>
#include <string>
// #include <iostream>

    using namespace cv;
const int max_value_H = 360 / 2;
const int max_value = 255;
const String window_capture_name = "Video Capture";
const String window_detection_name = "Object Detection";
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;



class BallColor {
public:
    BallColor();
    ~BallColor() = default;

private:
    void BallCallback(
        const sensor_msgs::ImageConstPtr& msg, const sensor_msgs::CameraInfoConstPtr& info);

    ros::NodeHandle nh;
    ros::NodeHandle pnh;
    image_transport::ImageTransport image_transport;
    image_transport::CameraSubscriber camera_subscriber;
    image_transport::Publisher imgPub;
    ros::Publisher vecPub;
    ros::Subscriber detectionSub;
    int minHue, minSat, minVib, maxHue, maxSat, maxVib, minSize, erode_amnt, dilate_amnt;
    double originX, originY;
    // bool publishThresh;
    image_geometry::PinholeCameraModel camera;

};


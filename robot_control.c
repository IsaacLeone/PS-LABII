#include "robot_control.h"
#include <webots/robot.h>
#include <webots/position_sensor.h>
#include <math.h>
#include <stdio.h>


#define WHEEL_RADIUS 0.0985   // Raio da roda (metros)
#define WHEEL_BASE 0.4044     // Distância entre as duas rodas (metros)


static WbDeviceTag left_encoder;
static WbDeviceTag right_encoder;


static Pose current_pose = {0.0, 0.0, 0.0};

static double last_left_dist = 0.0;
static double last_right_dist = 0.0;

void control_init(double time_step_ms) {

    left_encoder = wb_robot_get_device("wheel_left_joint_sensor");
    right_encoder = wb_robot_get_device("wheel_right_joint_sensor");


    wb_position_sensor_enable(left_encoder, (int)time_step_ms);
    wb_position_sensor_enable(right_encoder, (int)time_step_ms);
}

void control_update_odometry(double time_step_ms) {

    double left_rad = wb_position_sensor_get_value(left_encoder);
    double right_rad = wb_position_sensor_get_value(right_encoder);


    if (isnan(left_rad) || isnan(right_rad)) return;

 
    double current_left_dist = left_rad * WHEEL_RADIUS;
    double current_right_dist = right_rad * WHEEL_RADIUS;


    double d_left = current_left_dist - last_left_dist;
    double d_right = current_right_dist - last_right_dist;

  
    last_left_dist = current_left_dist;
    last_right_dist = current_right_dist;


    double d_center = (d_left + d_right) / 2.0;       // Deslocamento linear do centro do robô
    double d_theta = (d_right - d_left) / WHEEL_BASE;   // Deslocamento angular (orientação)

 
    current_pose.x += d_center * cos(current_pose.theta + d_theta / 2.0);
    current_pose.y += d_center * sin(current_pose.theta + d_theta / 2.0);
    current_pose.theta += d_theta;


    if (current_pose.theta > M_PI)  current_pose.theta -= 2.0 * M_PI;
    if (current_pose.theta < -M_PI) current_pose.theta += 2.0 * M_PI;


    printf("[ODOMETRIA] X: %.3f m | Y: %.3f m | Theta: %.2f rad\n", 
           current_pose.x, current_pose.y, current_pose.theta);
}

Pose control_get_pose(void) {
    return current_pose;
}

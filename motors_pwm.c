#include "motors_pwm.h"
#include <webots/robot.h>
#include <webots/motor.h>
static WbDeviceTag left_motor;
static WbDeviceTag right_motor;

void motors_init(void) {

    left_motor = wb_robot_get_device("wheel_left_joint");
    right_motor = wb_robot_get_device("wheel_right_joint");

    wb_motor_set_position(left_motor, INFINITY);
    wb_motor_set_position(right_motor, INFINITY);

    motors_stop();
}
void motors_set_speed(double left_speed, double right_speed) {

    wb_motor_set_velocity(left_motor, left_speed);
    wb_motor_set_velocity(right_motor, right_speed);
}

void motors_stop(void) {
    wb_motor_set_velocity(left_motor, 0.0);
    wb_motor_set_velocity(right_motor, 0.0);
}

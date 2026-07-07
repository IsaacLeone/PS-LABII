#ifndef MOTORS_PWM_H
#define MOTORS_PWM_H
void motors_init(void);
void motors_set_speed(double left_speed, double right_speed);
void motors_stop(void);
#endif // MOTORS_PWM_H

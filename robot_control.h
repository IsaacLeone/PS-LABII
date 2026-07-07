#ifndef ROBOT_CONTROL_H
#define ROBOT_CONTROL_H


typedef struct {
    double x;     // Posição no eixo X (metros)
    double y;     // Posição no eixo Y (metros)
    double theta; // Orientação/Ângulo (radianos)
} Pose;

void control_init(double time_step_ms);

void control_update_odometry(double time_step_ms);

Pose control_get_pose(void);

#endif // ROBOT_CONTROL_H

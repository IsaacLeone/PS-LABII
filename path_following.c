#include "path_following.h"
#include <math.h>
#include <stdio.h>

#define MAX_WAYPOINTS 4
#define ARRIVAL_THRESHOLD 0.15
#define KP_LINEAR 1.2          
#define KP_ANGULAR 3.5         

static Waypoint trajectory[MAX_WAYPOINTS];
static int current_wp_index = 0;
static int trajectory_finished = 0;

void path_init(void) {

    trajectory[0] = (Waypoint){0.0, 0.0};  // Ponto inicial
    trajectory[1] = (Waypoint){1.5, 0.0};  // Avança em X
    trajectory[2] = (Waypoint){1.5, 1.5};  // Avança em Y
    trajectory[3] = (Waypoint){0.0, 1.5};  // Retorna em X
    
    current_wp_index = 1; // Começa mirando no primeiro alvo real
    trajectory_finished = 0;
}

void path_compute_control(Pose current_pose, double *v_target, double *w_target) {
    if (trajectory_finished) {
        *v_target = 0.0;
        *w_target = 0.0;
        return;
    }

    Waypoint target = trajectory[current_wp_index];

   
    double error_x = target.x - current_pose.x;
    double error_y = target.y - current_pose.y;
    double distance_error = sqrt(error_x * error_x + error_y * error_y);

  
    if (distance_error < ARRIVAL_THRESHOLD) {
        current_wp_index++;
        if (current_wp_index >= MAX_WAYPOINTS) {
            trajectory_finished = 1;
            *v_target = 0.0;
            *w_target = 0.0;
            return;
        }
        target = trajectory[current_wp_index];
        error_x = target.x - current_pose.x;
        error_y = target.y - current_pose.y;
        distance_error = sqrt(error_x * error_x + error_y * error_y);
    }


    double target_angle = atan2(error_y, error_x);
    
 
    double orientation_error = target_angle - current_pose.theta;


    if (orientation_error > M_PI)  orientation_error -= 2.0 * M_PI;
    if (orientation_error < -M_PI) orientation_error += 2.0 * M_PI;

  
    *w_target = KP_ANGULAR * orientation_error;
    
    if (fabs(orientation_error) < 0.4) {
        *v_target = KP_LINEAR * distance_error;
    } else {
        *v_target = 0.0; // Gira no próprio eixo primeiro para se alinhar
    }

  // saturação
    if (*v_target > 0.5)  *v_target = 0.5;  // max 0.5 m/s 
    if (*w_target > 1.0)  *w_target = 1.0;  // max 1.0 rad/s
    if (*w_target < -1.0) *w_target = -1.0;
}

int path_is_finished(void) {
    return trajectory_finished;
}

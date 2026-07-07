#ifndef PATH_FOLLOWING_H
#define PATH_FOLLOWING_H

#include "robot_control.h"

typedef struct {
    double x;
    double y;
} Waypoint;

void path_init(void);

void path_compute_control(Pose current_pose, double *v_target, double *w_target);

int path_is_finished(void);

#endif // PATH_FOLLOWING_H

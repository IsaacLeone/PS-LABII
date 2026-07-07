#include <webots/robot.h>
#include "motors_pwm.c"
#include "robot_control.c"
#include "path_following.c"
#include "supervisorio.c" 

#define TIME_STEP 64
#define WHEEL_RADIUS 0.0985
#define WHEEL_BASE 0.4044

int main(int argc, char **argv) {
    wb_robot_init();
    
    motors_init();
    control_init(TIME_STEP);
    path_init();
    supervisorio_init();

    while (wb_robot_step(TIME_STEP) != -1) {
        
        control_update_odometry(TIME_STEP);
        Pose pose_atual = control_get_pose();


        double v_cmd = 0.0, w_cmd = 0.0;
        path_compute_control(pose_atual, &v_cmd, &w_cmd);

   
        int concluido = path_is_finished();
        supervisorio_transmitir(TIME_STEP, pose_atual, v_cmd, w_cmd, concluido);


        double speed_left = (v_cmd - (w_cmd * WHEEL_BASE / 2.0)) / WHEEL_RADIUS;
        double speed_right = (v_cmd + (w_cmd * WHEEL_BASE / 2.0)) / WHEEL_RADIUS;

        motors_set_speed(speed_left, speed_right);
        
        if (concluido) {
            motors_stop();
            printf("[PROCESSO] Trajetória finalizada. Sistema em modo de espera.\n");
            break; 
        }
    }

    wb_robot_cleanup();
    return 0;
}

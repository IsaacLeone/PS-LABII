#include <webots/robot.h>
#include "motors_pwm.h"


#define TIME_STEP 64

int main(int argc, char **argv) {

    wb_robot_init();
    motors_init();
    while (wb_robot_step(TIME_STEP) != -1) {       
        motors_set_speed(2.0, -2.0);
    }
    wb_robot_cleanup();

    return 0;
}

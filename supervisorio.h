#ifndef SUPERVISORIO_H
#define SUPERVISORIO_H

#include "robot_control.h"

typedef struct {
    double tempo_simulacao; 
    Pose pose_estimada;     
    double v_linear;        
    double w_angular;       
    int status_sistema;     
} TelemetriaFrame;

void supervisorio_init(void);
void supervisorio_transmitir(double time_step_ms, Pose atual, double v, double w, int finalizado);

#endif // SUPERVISORIO_H

#include "supervisorio.h"
#include <stdio.h>

static double tempo_acumulado = 0.0;

void supervisorio_init(void) {
    tempo_acumulado = 0.0;
    printf("[SUPERVISÓRIO] Módulo de telemetria inicializado com sucesso.\n");
}

void supervisorio_transmitir(double time_step_ms, Pose atual, double v, double w, int finalizado) {
    tempo_acumulado += (time_step_ms / 1000.0); // Converte o passo de simulação para segundos

    TelemetriaFrame frame;
    frame.tempo_simulacao = tempo_acumulado;
    frame.pose_estimada = atual;
    frame.v_linear = v;
    frame.w_angular = w;
    frame.status_sistema = finalizado;

}

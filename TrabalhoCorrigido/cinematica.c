#include "cinematica.h"
#include "hardware_pwm.h"
#include <math.h>

// Parâmetros de calibração geométrica do chassi
#define RAIO_RODA 0.035  // Exemplo: rodas de 35mm
#define RAIO_ROBO 0.150  // Distância do centro até os motores (150mm)
#define GANHO_PWM 500.0  // Fator de conversão física (m/s) para escala digital (0-255)

void cinematica_inversa(VelocidadeGlobal input) {
    // Equações da matriz de acoplamento cinemático para 3 rodas a 120 graus
    double w1 = -sin(0) * input.vx + cos(0) * input.vy + RAIO_ROBO * input.theta;
    double w2 = -sin(2.0 * M_PI / 3.0) * input.vx + cos(2.0 * M_PI / 3.0) * input.vy + RAIO_ROBO * input.theta;
    double w3 = -sin(4.0 * M_PI / 3.0) * input.vx + cos(4.0 * M_PI / 3.0) * input.vy + RAIO_ROBO * input.theta;

    // Converte as velocidades angulares calculadas para a escala de duty cycle do PWM (-255 a 255)
    int pwm_m1 = (int)(w1 * GANHO_PWM);
    int pwm_m2 = (int)(w2 * GANHO_PWM);
    int pwm_m3 = (int)(w3 * GANHO_PWM);

    // Envia os valores processados diretamente para os registradores de hardware
    motor_set_speed(1, pwm_m1);
    motor_set_speed(2, pwm_m2);
    motor_set_speed(3, pwm_m3);
}

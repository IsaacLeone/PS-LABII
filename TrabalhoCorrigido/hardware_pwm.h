#ifndef HARDWARE_PWM_H
#define HARDWARE_PWM_H

// Inicializa os Timers para gerar 3 canais PWM e os pinos de GPIO para direção
void hardware_init(void);

// Seta a velocidade (-255 a 255) de cada motor individualmente
// Valores positivos = frente | Valores negativos = trás | 0 = parado
void motor_set_speed(int motor_id, int velocidade);

#endif // HARDWARE_PWM_H

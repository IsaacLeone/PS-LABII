#include "hardware_pwm.h"
#include <avr/io.h>

void hardware_init(void) {
    // Configura os pinos de PWM como saída: PD5 (M1), PD6 (M2), PB3 (M3)
    DDRD |= (1 << DDD5) | (1 << DDD6);
    DDRB |= (1 << DDB3);

    // Configura os pinos de Direção como saída:
    // Motor 1: PD2, PD3 | Motor 2: PD4, PD7 | Motor 3: PB0, PB1
    DDRD |= (1 << DDD2) | (1 << DDD3) | (1 << DDD4) | (1 << DDD7);
    DDRB |= (1 << DDB0) | (1 << DDB1);

    // Configura Timer 0 (Fast PWM, Modo Não-Invertido, Prescaler 64) -> Controla M1 e M2
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B = (1 << CS01) | (1 << CS00);

    // Configura Timer 2 (Fast PWM, Modo Não-Invertido, Prescaler 64) -> Controla M3
    TCCR2A = (1 << COM2A1) | (1 << WGM21) | (1 << WGM20);
    TCCR2B = (1 << CS22);
}

void motor_set_speed(int motor_id, int velocidade) {
    int sentido = 0;
    if (velocidade > 0) sentido = 1;
    if (velocidade < 0) { sentido = -1; velocidade = -velocidade; } // Módulo da velocidade
    if (velocidade > 255) velocidade = 255;

    if (motor_id == 1) {
        OCR0A = velocidade; // Define o duty cycle do PWM
        if (sentido == 1) {        PORTD |= (1 << PD2);  PORTD &= ~(1 << PD3); }
        else if (sentido == -1) {  PORTD &= ~(1 << PD2); PORTD |= (1 << PD3);  }
        else {                     PORTD &= ~(1 << PD2); PORTD &= ~(1 << PD3); }
    }
    else if (motor_id == 2) {
        OCR0B = velocidade;
        if (sentido == 1) {        PORTD |= (1 << PD4);  PORTD &= ~(1 << PD7); }
        else if (sentido == -1) {  PORTD &= ~(1 << PD4); PORTD |= (1 << PD7);  }
        else {                     PORTD &= ~(1 << PD4); PORTD &= ~(1 << PD7); }
    }
    else if (motor_id == 3) {
        OCR2A = velocidade;
        if (sentido == 1) {        PORTB |= (1 << PB0);  PORTB &= ~(1 << PB1); }
        else if (sentido == -1) {  PORTB &= ~(1 << PB0); PORTB |= (1 << PB1);  }
        else {                     PORTB &= ~(1 << PB0); PORTB &= ~(1 << PB1); }
    }
}

#ifndef CINEMATICA_H
#define CINEMATICA_H

// Estrutura para os inputs de velocidade do robô
typedef struct {
    double vx;    // Velocidade linear no eixo X
    double vy;    // Velocidade linear no eixo Y
    double theta; // Velocidade angular (ômega)
} VelocidadeGlobal;

// Processa o vetor (Vx, Vy, Theta) e calcula a velocidade inteira (-255 a 255) para cada motor
void cinematica_inversa(VelocidadeGlobal input);

#endif // CINEMATICA_H

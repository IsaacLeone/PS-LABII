int main(void) {
    hardware_init();

    VelocidadeGlobal comando;

   while (1) {
       
        comando.vx = 0.4;
        comando.vy = 0.0;
        comando.theta = 0.0;
        cinematica_inversa(comando);
        _delay_ms(4000);


        comando.vx = 0.0;
        comando.vy = 0.3;
        comando.theta = 0.5;
        cinematica_inversa(comando);
        _delay_ms(4000);

   
        comando.vx = 0.0;
        comando.vy = 0.0;
        comando.theta = 0.0;
        cinematica_inversa(comando);
        _delay_ms(2000);
    }

    return 0;
}

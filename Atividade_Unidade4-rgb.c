/*  Aluna: Hirislayne Batista R. dos Santos
    Curso de Capacitação Embarcatech
    Exemplo piscar LED RGB da placa BitDogLab
*/

// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"

// Define os pinos GPIO para as cores do LED RGB
#define LEDR_Pin 13 // LED vermelho
#define LEDB_Pin 12 // LED azul
#define LEDG_Pin 11 // LED verde
#define LED_delay_ms 500 // define o tempo de espera (delay)

// Cria uma função para controle dos LED RGB
void led_rgb_put(bool r, bool g, bool b){
    gpio_put(LEDR_Pin, r); 
    gpio_put(LEDG_Pin, g);
    gpio_put(LEDB_Pin, b);
}

int main(){
    // Inicializa comunicacao padrão
    stdio_init_all();

    // Inicializa os pinos GPIO do RGB
    gpio_init(LEDR_Pin); 
    gpio_init(LEDB_Pin);
    gpio_init(LEDG_Pin);

    // Configuração dos pinos GPIO do RGB como saída
    gpio_set_dir(LEDR_Pin, GPIO_OUT);
    gpio_set_dir(LEDB_Pin, GPIO_OUT);
    gpio_set_dir(LEDG_Pin, GPIO_OUT);

    // Loop para ligar os LEDs
    while (1){
        led_rgb_put(1,0,0); // liga o LED RED
        sleep_ms(LED_delay_ms);

        led_rgb_put(0,1,0); // liga o LED VERDE
        sleep_ms(LED_delay_ms);

        led_rgb_put(0,0,1); // liga o LED AZUL
        sleep_ms(LED_delay_ms);

        led_rgb_put(1,1,1); // liga o LED BRANCO (todos os LEDs)
        sleep_ms(LED_delay_ms);
    }
}
/*  Aluna: Hirislayne Batista R. dos Santos
    Curso de Capacitação Embarcatech
    Tarefa 1 - https://wokwi.com/projects/420360925119773697
*/

// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"

// Define os pinos GPIO para as cores do LED RGB
#define LEDR_Pin 13 // LED vermelho
#define LEDB_Pin 12 // LED azul
#define LEDG_Pin 11 // LED verde
#define PIN_BTN_D 4   // Botao direito
#define PIN_BTN_E 8   // Botao esquerdo
#define LED_delay_ms 200 // define o tempo de espera (delay)

// Cria uma função para controle dos LED RGB
void led_rgb_put(bool r, bool g, bool b){
  gpio_put(LEDR_Pin, r); 
  gpio_put(LEDG_Pin, g);
  gpio_put(LEDB_Pin, b);
}

int main(){
  // Inicializacao de entradas e saidas
  stdio_init_all();

  // Inicializa os pinos do LED RGB e configura como saida
  gpio_init(LEDR_Pin); 
  gpio_init(LEDB_Pin);
  gpio_init(LEDG_Pin);
  gpio_set_dir(LEDR_Pin, GPIO_OUT);
  gpio_set_dir(LEDB_Pin, GPIO_OUT);
  gpio_set_dir(LEDG_Pin, GPIO_OUT);

  // Inicializa os pinos dos botoes e configura como entrada com resistor pull up interno
  gpio_init(PIN_BTN_D);
  gpio_init(PIN_BTN_E);
  gpio_set_dir(PIN_BTN_D, GPIO_IN);
  gpio_set_dir(PIN_BTN_E, GPIO_IN);
  gpio_pull_down(PIN_BTN_D);
  gpio_pull_down(PIN_BTN_E);


  // Loop para ligar os LEDs
  while (1){
    if (gpio_get(PIN_BTN_D) == 1 && gpio_get(PIN_BTN_E) == 1){
      led_rgb_put(1, 0, 0); // liga o LED RED
    }else if  (gpio_get(PIN_BTN_D) == 1){
      led_rgb_put(0, 1, 0); // liga o LED VERDE
    }else if (gpio_get(PIN_BTN_E) == 1){
      led_rgb_put(0, 0, 1); // liga o LED AZUL
    }else{
      led_rgb_put(0, 0, 0); // desliga o LED
    }
    sleep_ms(LED_delay_ms);
  }
} 

/*  Aluna: Hirislayne Batista R. dos Santos
    Curso de Capacitação Embarcatech
    https://wokwi.com/projects/420372124245534721
*/

// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"

// Define os pinos GPIO para as cores do LED RGB
#define LEDR_Pin 13 // LED vermelho
#define LEDG_Pin 11 // LED verde
#define LEDB_Pin 12 // LED azul
#define PIN_BTN_R 28   // Botao vermelho
#define PIN_BTN_G 27   // Botao verde
#define PIN_BTN_B 26   // Botao azul
#define LED_delay_ms 500 // define o tempo de espera (delay)

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
  gpio_init(LEDG_Pin);
  gpio_init(LEDB_Pin);
  gpio_set_dir(LEDR_Pin, GPIO_OUT);
  gpio_set_dir(LEDG_Pin, GPIO_OUT);
  gpio_set_dir(LEDB_Pin, GPIO_OUT);

  // Inicializa os pinos dos botoes e configura como entrada com resistor interno
  gpio_init(PIN_BTN_R);
  gpio_init(PIN_BTN_G);
  gpio_init(PIN_BTN_B);
  gpio_set_dir(PIN_BTN_R, GPIO_IN);
  gpio_set_dir(PIN_BTN_G, GPIO_IN);
  gpio_set_dir(PIN_BTN_B, GPIO_IN);
  gpio_pull_down(PIN_BTN_R);
  gpio_pull_down(PIN_BTN_G);
  gpio_pull_down(PIN_BTN_B);

  // Loop para ligar os LEDs
  while (1){
    if (gpio_get(PIN_BTN_R)) { // Botão vermelho pressionado
      printf("Botão vermelho pressionado.\n");
      led_rgb_put(1, 0, 0); // Liga o LED vermelho
    } else if (gpio_get(PIN_BTN_G)) { // Botão verde pressionado
      printf("Botão verde pressionado.\n");
      led_rgb_put(0, 1, 0); // Liga o LED verde
    } else if (gpio_get(PIN_BTN_B)) { // Botão azul pressionado
      printf("Botão azul pressionado.\n");
      led_rgb_put(0, 0, 1); // Liga o LED azul
    } else { 
      printf("LED desligado.\n");
      led_rgb_put(0, 0, 0); // Desliga todos os LEDs
    }
    sleep_ms(LED_delay_ms);
  }
}

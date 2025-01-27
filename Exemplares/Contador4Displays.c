#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

#define NUM_PINS_MUX 4 // 4 displays
#define NUM_PINS_SEGMENTS 7
#define NUM_DIGITS 10

// Definição dos pinos dos segmentos do display
const uint8_t segment_pins[] = {7, 8, 2, 3, 4, 5, 6};
const uint8_t mux_display_pins[] = {10, 11, 12, 13}; 
// Gpio 10: posição 0 do vetor, Display que representa o digito das milhares;
// Gpio 11: posição 1 do vetor, Display que representa o dígito das centenas;
// Gpio 12: poisção 0 do vetor, Display que representa o digito das dezenas;
// Gpio 13: posição 1 do vetor, Display que representa o dígito das unidades;

// Mapeamento dos dígitos para os segmentos do display
const uint8_t display[NUM_DIGITS][NUM_PINS_SEGMENTS] =  {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 0, 0, 1, 1}  // 9
};

// Função para configurar os pinos como saída
void setup_display(){
  for (int i = 0; i < NUM_PINS_SEGMENTS; i++) {
      gpio_init(segment_pins[i]);
      gpio_set_dir(segment_pins[i], GPIO_OUT);
  }
  for (int i = 0; i < NUM_PINS_MUX; i++){
      gpio_init(mux_display_pins[i]);
      gpio_set_dir(mux_display_pins[i], GPIO_OUT);
      gpio_put(mux_display_pins[i], 1); // Desativa os displays (catodo comum)
  }
}

// Função para mostrar um dígito em um dos displays selecionados
void show_digit(uint8_t digits, uint8_t digit){
    // Desativa todos os displays
    for (int i = 0; i < NUM_PINS_MUX; i++) {
        gpio_put(mux_display_pins[i], 1);
    }
  
    // Ativa os segmentos referentes ao dígito
    for (int i = 0; i < NUM_PINS_SEGMENTS; i++){
        gpio_put(segment_pins[i], display[digit][i]);
    }

    // Ativa o display desejado
    gpio_put(mux_display_pins[digits], 0);
}


// Contador de 0000 a 9999
int main() {
  stdio_init_all();
  setup_display();  // Configura os displays
  uint16_t number = 0;

  while (true) {
    uint8_t milhares = number / 1000; // Dígito dos milhares
    uint8_t centenas = (number % 1000) / 100; // Dígito das centenas
    uint8_t dezenas = (number % 100) / 10; // Dígito das dezenas
    uint8_t unidades = number % 10; // Dígito das unidades
    
    // Multiplex rápido entre os displays
    for (int j = 0; j < 100; j++) { // Controla a velocidade de atualização
        show_digit(0, milhares); // Exibe o dígito dos milhares no primeiro display
        sleep_ms(0.1); // Tempo de permanência no primeiro display
        show_digit(1, centenas); // Exibe o dígito das centenas no segundo display
        sleep_ms(0.1); // Tempo de permanência no segundo display
        show_digit(2, dezenas); // Exibe o dígito das dezenas no terceiro display
        sleep_ms(0.1); // Tempo de permanência no terceiro display
        show_digit(3, unidades); // Exibe o dígito das unidades no quarto display
        sleep_ms(0.1); // Tempo de permanência no quarto display
    }
    
    number++; // Incrementa o número
    if (number > 9999) {
        number = 0; // Reseta para 0000 após alcançar 9999
    }
    sleep_ms(50); // Pausa entre os incrementos
  }
  return 0;
}

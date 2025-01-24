/*
  //Aluna: Hirislayne Batista R. dos Santos
  Curso de Capacitação Embarcatech

  Pressionando as teclas 1, 4, 7 e "*" - Acenda o led vermelho;
  Pressionando as teclas 2, 5, 8 e 0 - Acenda o led verde;
  Pressionando as teclas 3, 6, 9 e "#" - Acenda o led azul;
  Pressionando as teclas A, B, C e D - Nenhum led deve acender;
*/

#include <stdio.h>
#include "pico/stdlib.h"

// Inicializacoes
#define NUM_LINHAS 4
#define NUM_COLUNAS 4
#define NUM_LEDS 3

// Define os pinos GPIO para as linhas e colunas 
uint8_t pin_linha[NUM_LINHAS] = {2, 3, 4, 5};    // definicao dos pinos R1, R2, R3 e R4
uint8_t pin_coluna[NUM_COLUNAS] = {6, 7, 8, 9};  // definicao dos pinos C1, C2, C3 e C4
uint8_t pin_leds[NUM_LEDS] = {28, 27, 26};       // definicao dos pinos do led

// Mapeamento das teclas em uma matriz 4x4
const char teclado[NUM_LINHAS][NUM_COLUNAS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
}; // ou com o #include (Keypad.h> Keypad keypad - Keypad(makeKeymap(keys), pin_linha, pin_coluna, NUM_COLUNAS, NUM_LINHAS);

void init_leds();
void init_teclado();
char leitura_teclado();
void acender_led(char valor_tecla);

int main() {
  stdio_init_all();  // Inicializa a UART (Serial)
  init_teclado();    // Inicializa o teclado matricial
  init_leds();       // Inicializa o led RGB

  printf("Pressione uma tecla!\n");

  while (1) {
    char tecla_press = leitura_teclado();
    if (tecla_press != 'n') { // Condição de segurança
      printf("Tecla pressionada: %c\n", tecla_press);
      acender_led(tecla_press); // Envia para funcao de acender o RGB com base na tecla pressionada
    }
    sleep_ms(100); // Estabilização - para evitar múltiplas leituras da mesma tecla
  }
  return 0;
}

// Cria uma função para controle dos LED RGB
void led_rgb_put(bool r, bool g, bool b) {
  gpio_put(pin_leds[0], r); 
  gpio_put(pin_leds[1], g);
  gpio_put(pin_leds[2], b);
}

// Inicializa os pinos do LED RGD e configura como saida
void init_leds() {
  for(int i = 0; i < NUM_LEDS; i++){
    gpio_init(pin_leds[i]);
    gpio_set_dir(pin_leds[i], GPIO_OUT);
    gpio_put(pin_leds[i], 0);
  }
}

// Inicializando os pinos de GPIO do teclado - configuração para teclados matriciais com pull-down nas LINHAS.
void init_teclado() {
  // Inicializa e configura as LINHAS como ENTRADAS digitais com resistores de PULL-UP
  for (int i = 0; i < NUM_LINHAS; i++) {
    gpio_init(pin_linha[i]);
    gpio_set_dir(pin_linha[i], GPIO_IN);
    gpio_pull_up(pin_linha[i]); // Habilita o PULL-UP para as LINHAS
  }

  // Inicializa e configura as COLUNAS como SAIDAS digitais
  for (int i = 0; i < NUM_COLUNAS; i++) {
    gpio_init(pin_coluna[i]);
    gpio_set_dir(pin_coluna[i], GPIO_OUT);
    gpio_put(pin_coluna[i], 1); // Inicializa as COLUNAS como ALTO (inativas)
  }
}

// Varredura do teclado e retorno da tecla pressionada
char leitura_teclado() {
  char numero = 'n'; // Valor padrão para quando nenhuma tecla for pressionada

  for (int i = 0; i < NUM_COLUNAS; i++) {
    // Coloca a coluna atual em nível baixo (ativa)
    gpio_put(pin_coluna[i], 0);

    for (int j = 0; j < NUM_LINHAS; j++) {
      // Verifica se a linha atual está em nível baixo (tecla pressionada)
      if (gpio_get(pin_linha[j]) == 0) {
        numero = teclado[j][i]; // Mapeia a tecla pressionada
        
        // Aguarda a tecla ser liberada (debounce - para estalibizacao)
        while (gpio_get(pin_linha[j]) == 0){
          sleep_ms(20);
        } break; // Sai do laço após detectar a tecla
      }
    }

    // Reseta a coluna atual para condição inicial (nivel alto)
    gpio_put(pin_coluna[i], 1);

    // Para sair do laço de Colunas, caso um tecla seja pressionada
    if (numero != 'n') {
        break;
    }
  }
  return numero; // Retorna a tecla pressionada
}

// Função para controlar os LEDs com base na tecla pressionada
void acender_led(char valor_tecla){
    // Verifica a tecla pressionada e acende o LED correspondente
    if (valor_tecla == '1' || valor_tecla == '4' || valor_tecla == '7' || valor_tecla == '*') {
      printf("LED vermelho ligado.\n");
      led_rgb_put(1, 0, 0); // Liga o LED vermelho
    } else if (valor_tecla == '2' || valor_tecla == '5' || valor_tecla == '8' || valor_tecla == '0') {
      printf("LED verde ligado.\n");
      led_rgb_put(0, 1, 0); // Liga o LED verde
    } else if (valor_tecla == '3' || valor_tecla == '6' || valor_tecla == '9' || valor_tecla == '#') {
      printf("LED azul ligado.\n");
      led_rgb_put(0, 0, 1); // Liga o LED azul
    } else{
      printf("LED desligado.\n");
      led_rgb_put(0, 0, 0); // Nenhuma LED acende
    }

    sleep_ms(300);          // Aguarda pelo tempo definido
    led_rgb_put(0, 0, 0);   // Desliga todos os LEDs
}
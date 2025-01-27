/*  Aluna: Hirislayne Batista R. dos Santos
    Curso de Capacitação Embarcatech
    Desafio 2 - Cofre Digital
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>
#include <time.h>

#define NUM_PINS_MUX 4
#define NUM_PINS_SEGMENTS 7
#define NUM_DIGITS 10
#define password_length 4 // Tamanho da senha
char password1[password_length + 1] = {0}; // senha cadastrada

// Definição dos pinos dos LEDs
#define LED_G 14
#define LED_R 15

// Define os pinos GPIO para as linhas e para as colunas do teclado matricial
const uint8_t row_pins[] = {16, 17, 18, 19};
const uint8_t col_pins[] = {20, 21,22, 26};

// Definição dos pinos dos segmentos do display
const uint8_t segment_pins[] = {3, 4, 5, 6, 7, 8, 9};
const uint8_t mux_display_pins[] = {10, 11, 12, 13}; 

// Mapeamento das teclas em uma matriz 4x4
char key_map[4][4] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Mapeamento dos dígitos para os segmentos do display
const uint8_t display_map[NUM_DIGITS][NUM_PINS_SEGMENTS] =  {
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

// Inicializar LEDS
void leds_init() {
  // Led verde
  gpio_init(LED_G);
  gpio_set_dir(LED_G, GPIO_OUT);
  gpio_put(LED_G, 0); // Inicialmente desligado

  // Led vermelho
  gpio_init(LED_R);
  gpio_set_dir(LED_R, GPIO_OUT);
  gpio_put(LED_R, 0); // Inicialmente desligado
}

// Inicializar teclado matricial
void keypad_init() {
  printf("Inicializando teclado...\n");
  for (int i = 0; i < 4; i++) {
    // Configuração dos pinos das linhas
    gpio_init(row_pins[i]);
    gpio_set_dir(row_pins[i], GPIO_OUT);
    gpio_put(row_pins[i], 1);
    
    // Configuração dos pinos das colunas
    gpio_init(col_pins[i]);
    gpio_set_dir(col_pins[i], GPIO_IN);
    gpio_pull_down(col_pins[i]); 
  }
  printf("Teclado inicializado com sucesso!\n");
}

// Inicializar displays
void display_init(){
  // Configura os segmentos
  for (int i = 0; i < NUM_PINS_SEGMENTS; i++) {
      gpio_init(segment_pins[i]);
      gpio_set_dir(segment_pins[i], GPIO_OUT);
  }
  // Configura os mux
  for (int i = 0; i < NUM_PINS_MUX; i++){
      gpio_init(mux_display_pins[i]);
      gpio_set_dir(mux_display_pins[i], GPIO_OUT);
      gpio_put(mux_display_pins[i], 1); // Desativa os displays (catodo comum)
  }
}

// Função para desativar displays
void disable_display(){
  for(int i = 0; i < NUM_PINS_MUX; i++){
    gpio_put(mux_display_pins[i], 1);
  }
}

// Função para ativar displays
void show_display(int digit, int mux){
  disable_display();
  for(int i = 0; i < NUM_PINS_SEGMENTS; i++){
    gpio_put(segment_pins[i], display_map[digit][i]); // Ativa os segmentos referentes ao dígito
  }
  gpio_put(mux_display_pins[mux], 0); // Ativa o display desejado
}

// Leitura do teclado e retorno da tecla pressionada
char read_keypad() {
  for (int row = 0; row < 4; row++) {
    gpio_put(row_pins[row], 1);   // Coloca a linha atual em nível lógico alto
    
    for (int col = 0; col < 4; col++) {
      if (gpio_get(col_pins[col])) {
        sleep_ms(100); // Tempo para estabilização da tecla pressionada
        while (gpio_get(col_pins[col])); // Espera liberação da tecla
        gpio_put(row_pins[row], 0); // Reseta a linha atual
        return key_map[row][col];
      }
    }
    gpio_put(row_pins[row], 0); // Coloca a linha atual novamente em nível lógico baixo
  }
  return 0; 
}

// Função para pegar a senha digitada 
void get_password(char *password, int lenght) {
  int index = 0;
  while (index < lenght) {
    char key = read_keypad();
    if (key != 0) {
        printf("%c", key); // %c\t
        password[index] = key;
        index++;
        sleep_ms(5); 
    }
    for (int i = 0; i <= index - 1; i++){
      show_display(password[i] - '0', i);
      sleep_ms(5);
    }
  }
  password[lenght] = '\0'; 
}

// Função para comparar senhas
bool compare_passwords(const char *password1, const char *password2){
  return strcmp(password1, password2) == 0; 
}

// Função para mostrar senha digitada no display
void confirm_pass_blinks(char *password){
  uint32_t start_time = to_ms_since_boot(get_absolute_time());
  while(to_ms_since_boot(get_absolute_time()) - start_time < 3000){
    for(int i = 0; i < 4; i++){
      show_display(password[i] - '0', i);
      sleep_ms(5);
    }
    disable_display();
    sleep_ms(750);
  }
}

// Função para acender LEDs para sinalização
void set_leds(bool r, bool g){
  if(r){
    gpio_put(LED_R, r);
    sleep_ms(1000);
    r = !r;
  }
  gpio_put(LED_R, r);
  gpio_put(LED_G, g);
}

int main() {
  stdio_init_all();
  keypad_init();   // Configuração inicial do teclado
  leds_init();     // Configuração inicial dos LEDs
  display_init();  // Configuração inicial dos displays

  printf("\nCadastro da senha do cofre. Informe uma senha de 4 digitos: ");
  get_password(password1, password_length);
  printf("\nSenha cadastrada com sucesso!\n");

  confirm_pass_blinks(password1); 

  int cont = 0;       // variável para contagem de tentativas de acesso
  bool acess = true;  // variável de controle de loop
  
  while (acess) {
    disable_display();
    printf("\nPara acesso ao cofre, digite a senha: ");
    char input[password_length + 1] = {0};
    get_password(input, password_length);
              
    if (compare_passwords(input, password1)) {
        printf("\n\nSenha Correta. Acesso liberado!\n");
        set_leds(false, true);
        confirm_pass_blinks(input);
        acess = !acess;
    } else {
      disable_display();
      set_leds(true, false);
      cont++;
      if(cont < 3){
        printf("\n\nSenha incorreta, acesso negado! Tente novamente (%d tentativas restantes)\n", 3- cont);
      } else {
        printf("\n\nNúmero de tentativas excedidas! Sistema bloqueado por 5 segundos...\n\n");
        sleep_ms(5000);
        cont = 0;
      }
    }
  }
}

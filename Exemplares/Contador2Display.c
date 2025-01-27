#include <stdio.h>
#include "pico/stdlib.h"
#include <string.h>

#define NUM_PINS_MUX 2
#define NUM_PINS_SEGMENTS 7
#define NUM_DIGITS 10

// Definição dos pinos dos segmentos do display
const uint8_t segment_pins[] = {0, 1, 2, 3, 4, 5, 6};
const uint8_t mux_display_pins[] = {10, 11}; //Pinos de controle dos 2 displays - catodo comum
// Gpio 10: poisção 0 do vetor, Display que representa o digito das dezenas;
// Gpio 11: posição 1 do vetor, Display que representa o dígito das unidades;

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

// função para configurar os pinos como saída
void setup_display(){
  for (int i = 0; i < NUM_PINS_SEGMENTS; i++) {
      gpio_init(segment_pins[i]);
      gpio_set_dir(segment_pins[i], GPIO_OUT);
  }
  for (int i = 0; i < NUM_PINS_MUX; i++){
      gpio_init(mux_display_pins[i]);
      gpio_set_dir(mux_display_pins[i], GPIO_OUT);
      gpio_put(mux_display_pins[i], 1); // Desativa os displays de catodo comum
      
  }
}

// função para mostrar um dígito em um dos display selecionado
void show_digit(uint8_t digits, uint8_t digit){
    // desativa os displays     
    gpio_put(mux_display_pins[0], 1);
    gpio_put(mux_display_pins[1], 1);
  
    //Ativa os segmentos referentes ao dígito
    for (int i = 0; i < NUM_PINS_SEGMENTS; i++){
        gpio_put(segment_pins[i], display[digit][i]);
        }

    gpio_put(mux_display_pins[digits], 0); //Ativa o display desejado

}

// Contador de 0 a 99
int main() {
  stdio_init_all();
  // Inicializa e configura os pinos dos segmentos como saída
  setup_display(); 
  while (true) {
    for (uint8_t numero = 0; numero < 100; numero++) {// contagem de 0 a 99
        uint8_t dezenas = numero/10; // calcula o dígito das dezenas
        uint8_t unidades = numero % 10; // calcula o dígito da unidades
    
        // Multiplex rápido entre os display
        for (int j=0; j<100; j++){ // valor de j controla a velocidade de atualização
        show_digit(0, dezenas); // exibe o dígito das dezenas no primeiro display
        sleep_ms(5); // tempo de permanência no primeiro display
        show_digit(1, unidades); // exibe o dígito das unidades no segundo display
        sleep_ms(5); // tempo de permanência no segundo display
        }
        sleep_ms(50); // pausa de 0,5 segundos entre os incrementos
    }
  }
  return 0;
}

//////////////////////////// TESTES DE FUNÇÕES MAIN ///////////////////////////////

///////////////////////////////////////////////////////////////////////////////////
// Exibir apenas um numero pré-definido
// int main() {
//   stdio_init_all();
//   setup_display();

//   while (true) {
//     show_digit(0, 2); // Exibe o número 2 no primeiro display
//     sleep_ms(500); // Intervalo para estabilidade na exibição
//   }
//   return 0;
// }

///////////////////////////////////////////////////////////////////////////////////
// Inserir um numero de 0 a 99 - forma direta
// int main() {
//   stdio_init_all();
//   printf("Digite um número entre 0 e 99:\n");
//   setup_display();

//   while (true) {
//     for (int i = 0; i < 100; i++) { // Multiplexação rápida
//       show_digit(0, 2); // Exibe o número 1 no primeiro display (dezenas)
//       sleep_ms(5);      // Tempo para exibição
//       show_digit(1, 1); // Exibe o número 2 no segundo display (unidades)
//       sleep_ms(5);      // Tempo para exibição
//     }
//   }
//   return 0;
// }


// int main() {
//     stdio_init_all(); // Inicializa o sistema de E/S
//     sleep_ms(1000);   // Aguarda 1 segundo para a comunicação serial estabilizar

//     char input[100]; // Array para armazenar a string digitada

//     // Teste do printf
//     printf("Olá, Wokwi!\n");
    
//     while(1) {
//         printf("\nDigite uma mensagem");
//         scanf("%99s", input); // Lê até 99 caracteres do console e armazena em 'input'
//         printf("\nVocê digitou: %s\n", input); // Exibe a string digitada
//         sleep_ms(1000);
//     }

//     return 0;
// }


///////////////////////////////////////////////////////////////////////////////////
// Inserir um número de 0 a 99 pelo serial e exibir o número nos displays
// int main() {
//     stdio_init_all();  // Inicializa a comunicação serial
//     sleep_ms(1000);

//     char input_buffer[4];  // Buffer para receber o número (máximo 3 dígitos)
//     uint8_t number = 0;    // Número lido do usuário

//     printf("Digite um número entre 0 e 99: \n");

//     while (true) {
//         // Lê o número via serial
//         if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
//             number = (uint8_t) atoi(input_buffer); // Converte para inteiro

//             if (number < 0 || number > 99) {
//                 printf("Número inválido. Digite entre 0 e 99: \n");
//                 continue;
//             }

//             uint8_t dezenas = number/10; // calcula o dígito das dezenas
//             uint8_t unidades = number % 10; // calcula o dígito da unidades

//             printf("Exibindo o número: %d\n", number);
            
            
//             setup_display();
//             // Exibe o número nos displays
//             for (int i = 0; i < 100; i++) { // Loop de multiplexação rápida
//                 show_digit(0, dezenas);
//                 show_digit(1, unidades);
//             }
//             sleep_ms(3000); // pausa de 0,5 segundos entre os incrementos
//             clear_display();
//         }
//     }

//     return 0;
// }


// int main() {
//     stdio_init_all();
//     setup_display();

//     printf("Digite um número entre 0 e 99:\n");

//     char input_buffer[4];
//     uint8_t number = 0;

//     while (true) {
//         if (fgets(input_buffer, sizeof(input_buffer), stdin) != NULL) {
//             number = (uint8_t)atoi(input_buffer);

//             if (number > 99) {
//               printf("Número inválido! Digite entre 0 e 99:\n");
//               continue;
//             }

//             printf("Número recebido: %d\n", number);

//             uint8_t dezenas = number / 10;
//             uint8_t unidades = number % 10;

//             for (int i = 0; i < 200; i++) { // Multiplexação
//                 show_digit(0, dezenas);
//                 sleep_ms(5);
//                 show_digit(1, unidades);
//                 sleep_ms(5);
//             }
//         }
//     }

//     return 0;
// }
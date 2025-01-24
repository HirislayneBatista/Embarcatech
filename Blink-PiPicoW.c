/*  Aluna: Hirislayne Batista R. dos Santos
    Curso de Capacitação Embarcatech
    Exemplo Blink - Piscar LED embutido da Placa Raspberry PI PICO W
*/

// Inclusão de bibliotecas
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h" // Biblioteca para controlar o LED embutido, driver Wifi

#define LED_delay_ms 500 // Define o tempo de espera (delay)

int main(){    
    // Inicializa comunicacao padrão
    stdio_init_all();

    // Inicializa a biblioteca cyw43_arch - driver do chip Wifi
    if (cyw43_arch_init() != 0) { // Verifica se a inicializacao falhou
        printf("Falha ao inicializar cyw43_arch\n");
        return -1;
    }

    // Loop para ligar e desligar o LED embutido
    while (1) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1); // Liga o LED embutido
        printf("LED ligado\n"); // Imprime mensagem no console
        sleep_ms(LED_delay_ms);

        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0); // Desliga o LED embutido
        printf("LED desligado\n");
        sleep_ms(LED_delay_ms);
    }
}
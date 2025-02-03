#include <stdio.h> // Biblioteca padrão do C.
#include "pico/stdlib.h" // Biblioteca padrão do Raspberry Pi Pico para controle de GPIO, temporização e comunicação serial.
#include "pico/time.h"   // Biblioteca para gerenciamento de temporizadores e alarmes.

const uint LED_PIN_GREEN = 11; // Define o pino GPIO 11 para controlar o LED verde
const uint LED_PIN_BLUE = 12; // Define o pino GPIO 12 para controlar o LED azul
const uint LED_PIN_RED = 13; // // Define o pino GPIO 13 para controlar o LED vermelho
const uint BUTTON_PIN = 5;  // Define o pino GPIO 5 para ler o estado do botão A

// Variáveis globais para controle do estados dos LEDs e botão
bool led_on = false;        // Indica se os LEds estão ativos
int led_state = 0;    // Estado atual dos LEDs 


// Função de callback para mudar o estado dos LEDs após o tempo programado
int64_t change_led_state_callback(alarm_id_t id, void *user_data) {

    switch (led_state) {
        case 1: // Desliga o LED azul, mantém vermelho e verde ligados
            gpio_put (LED_PIN_BLUE, false);
            led_state = 2;
            break;
        case 2: // Desliga o LED vermelho, mantém o verde ligado
            gpio_put (LED_PIN_RED, false);
            led_state = 3;
            break;
        case 3:// Desliga o LED verde
            gpio_put (LED_PIN_GREEN, false); 
            led_on = false; // Indica que todos os LEDs estão desligados
            led_state = 0;
            return 0; // Retorna 0 para indicar que o alarme não deve se repetir
    }
    
    //Agenda o próximo estado dos LEDs após 3 segundos
    add_alarm_in_ms(3000, change_led_state_callback, NULL, false);
    return 0;

}
          

int main() {
    // Inicializa a comunicação serial
    stdio_init_all();

    // Configura os pinos dos LEDs como saída digital
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);

    // Configura o pino BUTTON_PIN (5) como entrada digital com resistor pull-up
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);


    // Loop principal do programa que verifica continuamente o estado do botão.
    while (true){
        // Verifica se o botão foi pressionado (nível baixo no pino) e se o LED não está ativo.
        if (gpio_get(BUTTON_PIN) == 0 && !led_on) {
            // Adiciona um pequeno atraso para debounce, evitando leituras errôneas.
            sleep_ms(50);

            // Verifica novamente o estado do botão após o debounce.
            if (gpio_get(BUTTON_PIN) == 0) {
                // Liga o LED configurando o pino LED_PIN para nível alto.
                gpio_put(LED_PIN_GREEN, true);
                gpio_put(LED_PIN_BLUE, true);
                gpio_put(LED_PIN_RED, true);

                // Define o estado inicial dos LEDs
                led_state = 1;
                led_on = true;

                // Agenda um alarme para desligar o LED após 3 segundos (3000 ms).
                add_alarm_in_ms(3000, change_led_state_callback, NULL, false);
            }
        }
        // Introduz uma pequena pausa de 10 ms para reduzir o uso da CPU.
              sleep_ms(10);
    }

        return 0;
}     


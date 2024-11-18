Machine Learning - Detecção de Plantas

#include <Arduino.h>

// Definindo as categorias de plantas
#define NUM_PLANTAS 4

const char* categorias_plantas[NUM_PLANTAS] = {
    "Palmeira",
    "Roseira",
    "Arruda",
    "Mosquitinho"
};

// Estrutura para armazenar o resultado da detecção
struct resultado_deteccao_t {
    float valor;
};

// Estrutura para armazenar todos os resultados da detecção
struct resultado_inferencia_t {
    resultado_deteccao_t classificacao[NUM_PLANTAS];
};

// Função simulada para detectar plantas
void detectar_plantas_simulado(resultado_inferencia_t* resultado) {
    // Atribuindo valores aleatórios para simular a detecção
    for (size_t i = 0; i < NUM_PLANTAS; i++) {
        resultado->classificacao[i].valor = random(0, 100) / 100.0; // Valores entre 0 e 1
    }
}

void setup() {
    Serial.begin(115200); // Inicializa a comunicação serial
    Serial.println("Iniciando a detecção de plantas...");

    resultado_inferencia_t resultado = { 0 };

    // Chama a função simulada para detectar plantas
    detectar_plantas_simulado(&resultado);

    Serial.println("Detecção concluída:");
    for (size_t i = 0; i < NUM_PLANTAS; i++) {
        Serial.printf("%s: %.2f\n", categorias_plantas[i], resultado.classificacao[i].valor);
    }
}

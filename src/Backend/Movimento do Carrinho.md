## Código Movimentação do carrinho:
```C++
#include <HCSR04.h>
#define led 2

// Pinos para o controle dos motores no driver Ponte H (L298N)
#define motorPin1 9   // Motor esquerdo
#define motorPin2 10  // Motor esquerdo
#define motorPin3 11  // Motor direito
#define motorPin4 12  // Motor direito

UltraSonicDistanceSensor distancesensor(5, 4);  // Pinos do trig e echo

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);

  // Configuração dos pinos dos motores
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
}

void loop() {
  // Medindo a distância em cm
  float distancia = distancesensor.measureDistanceCm();

  // Validar a leitura do sensor
  if (distancia <= 0 || distancia > 400) { // Distâncias válidas para o HC-SR04 estão entre 2 cm e 400 cm
    Serial.println("Leitura inválida do sensor!");
    parar();
    delay(200);
    return;
  }

  // Exibindo a distância no monitor serial
  Serial.print("Distância: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Condição de desvio
  if (distancia > 0 && distancia < 15) {
    Serial.println("Obstáculo detectado! Pausando para análise...");
    parar();
    delay(2000);  // Delay maior para a câmera detectar a praga (2 segundos)

    Serial.println("Iniciando manobra de desvio...");
    recuar();
    delay(500);

    virar90GrausDireita();
    frente();
  } else {
    Serial.println("Caminho livre! Indo para frente...");
    digitalWrite(led, LOW);
    frente();
  }

  delay(200);
}

void frente() {
  Serial.println("Motores para frente");
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void parar() {
  Serial.println("Parando os motores");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  digitalWrite(led, HIGH); // Acende o LED indicando obstáculo
}

void recuar() {
  Serial.println("Recuando");
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void virar90GrausDireita() {
  Serial.println("Virando à direita (90 graus)");
  digitalWrite(motorPin1, HIGH); // Motor esquerdo avança
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);  // Motor direito para trás
  digitalWrite(motorPin4, HIGH);

  delay(700); // Ajustar para 90 graus exatos
  parar();
}
```

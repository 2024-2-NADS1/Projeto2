#include <WiFi.h>
#include <HTTPClient.h>
#include "esp_camera.h"

const char* ssid = "SEU_SSID";
const char* password = "SUA_SENHA";
const char* serverUrl = "http://SEU_SERVIDOR.com/api/dados";

const int trigPin = 5;
const int echoPin = 4;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Conectando ao WiFi...");
    }
    Serial.println("Conectado ao WiFi!");

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    int distancia = medirDistancia();
    enviarDados(distancia);
    delay(5000); // Envia a cada 5 segundos
}

int medirDistancia() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2;
    return distance;
}

void enviarDados(int distancia) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(serverUrl);
        http.addHeader("Content-Type", "application/json");

        String postData = "{\"distancia\":" + String(distancia) + "}";
        int httpResponseCode = http.POST(postData);

        if (httpResponseCode > 0) {
            Serial.println("Dados enviados com sucesso!");
        } else {
            Serial.println("Erro ao enviar dados.");
        }
        http.end();
    }
}

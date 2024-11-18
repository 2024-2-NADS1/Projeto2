### Passos para o Desenvolvimento
# 1. Configuração do Hardware (ESP32-CAM)
 
## O ESP32-CAM será responsável por capturar os dados do sensor e enviar as informações via rede para um servidor. No exemplo, utilizaremos: #

### Sensor ultrassônico [HC-SR04](https://www.mercadolivre.com.br/modulo-sensor-ultrassonico-hc-sr04-arduino-pic-raspberry/p/MLB32491020?pdp_filters=item_id%3AMLB3902448817&from=gshop&matt_tool=63064967&matt_word=&matt_source=google&matt_campaign_id=14303413826&matt_ad_group_id=133431076203&matt_match_type=&matt_network=g&matt_device=c&matt_creative=584156655540&matt_keyword=&matt_ad_position=&matt_ad_type=pla&matt_merchant_id=735128188&matt_product_id=MLB32491020-product&matt_product_partition_id=2269730643578&matt_target_id=aud-1966981570049:pla-2269730643578&cq_src=google_ads&cq_cmp=14303413826&cq_net=g&cq_plt=gp&cq_med=pla&gad_source=1&gclid=CjwKCAiAxea5BhBeEiwAh4t5K_4KUUOEQQQsFKraQZrJbHZJ7oTXwmN21QonatnAhfXMK9LCvKBFKRoCW4kQAvD_BwE) para medir distâncias.
 
### Protocolo HTTP para comunicação.

# 2. Código do ESP32-CAM
## Este código realiza a captura dos dados do sensor e os envia para o servidor:

```C++
 
#include <WiFi.h>
#include <HTTPClient.h>
#include <HCSR04.h>

// Configuração do Wi-Fi
const char* ssid = "SEU_SSID";          // Substitua pelo nome da sua rede Wi-Fi
const char* password = "SUA_SENHA";    // Substitua pela senha da sua rede

// URL do servidor
const char* serverUrl = "http://SEU_SERVIDOR:5000/dados";

// Pinos do sensor ultrassônico
#define TRIG_PIN 5
#define ECHO_PIN 4

UltraSonicDistanceSensor distanceSensor(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(115200);
  
  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi!");
}

void loop() {
  // Captura a distância
  float distance = distanceSensor.measureDistanceCm();
  Serial.print("Distância medida: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Envia os dados para o servidor
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);

    // Configura o tipo de conteúdo da requisição
    http.addHeader("Content-Type", "application/json");

    // Monta os dados em formato JSON
    String json = "{\"distancia\": " + String(distance) + "}";
    int httpResponseCode = http.POST(json);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Resposta do servidor: " + response);
    } else {
      Serial.println("Erro ao enviar os dados!");
    }
    http.end();
  }

  delay(2000); // Intervalo entre as medições
}
```
# 3. Código do Servidor (Python com Flask)
### O servidor recebe os dados enviados pelo ESP32-CAM e os exibe em uma interface web.

## Dependências:
### Instale as dependências necessárias:

```bash
pip install flask flask-cors
```
### Código do Servidor:
```python
from flask import Flask, request, jsonify, render_template
from flask_cors import CORS

app = Flask(__name__)
CORS(app)

# Variável para armazenar o último dado recebido
dados_recebidos = {"distancia": None}

@app.route("/dados", methods=["POST"])
def receber_dados():
    global dados_recebidos
    dados_recebidos = request.json  # Captura os dados enviados pelo ESP32-CAM
    print(f"Dados recebidos: {dados_recebidos}")
    return jsonify({"status": "Dados recebidos com sucesso!"})

@app.route("/")
def index():
    global dados_recebidos
    return render_template("index.html", dados=dados_recebidos)

if __name__ == "__main__":
    app.run(host="0.0.0.0", port=5000)
``` 
# 4. Interface Web
### Este arquivo exibe os dados capturados pelo sensor em tempo real.

```html

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Monitor IoT</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      padding: 20px;
    }
    h1 {
      color: #333;
    }
    .data-box {
      margin-top: 20px;
      font-size: 24px;
      color: #007BFF;
    }
  </style>
</head>
<body>
  <h1>Monitoramento IoT</h1>
  <div class="data-box">
    <p>Distância capturada: <span id="distancia">Carregando...</span> cm</p>
  </div>

  <script>
    async function fetchData() {
      try {
        const response = await fetch("/");
        const data = await response.json();
        document.getElementById("distancia").innerText = data.distancia || "N/A";
      } catch (error) {
        console.error("Erro ao buscar os dados:", error);
      }
    }

    setInterval(fetchData, 2000); // Atualiza a cada 2 segundos
  </script>
</body>
</html>
```

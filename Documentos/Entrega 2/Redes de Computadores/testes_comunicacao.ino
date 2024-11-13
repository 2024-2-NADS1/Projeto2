#include <WiFi.h>
#include <HTTPClient.h>

// Defina as credenciais da rede Wi-Fi
const char* ssid = "sua_rede_wifi";
const char* password = "sua_senha_wifi";

// URL do servidor de teste
const char* serverUrl = "http://servidor-teste.com/api/dados";  // Exemplo de URL

void setup() {
  Serial.begin(115200);
  
  // Conecte-se ao Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Monta uma requisição POST com dados de teste
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    // Exemplo de JSON com dados fictícios, incluindo um teste de imagem
    String dados = "{\"sensor\":\"camera\",\"valor\":\"imagem_capturada.jpg\"}";

    int httpResponseCode = http.POST(dados);

    if (httpResponseCode > 0) {
      String resposta = http.getString();
      Serial.print("Resposta do Servidor: ");
      Serial.println(resposta);
    } else {
      Serial.print("Erro ao enviar dados: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  } else {
    Serial.println("Erro: WiFi desconectado.");
  }
  
  delay(10000);  // Intervalo entre os testes
}

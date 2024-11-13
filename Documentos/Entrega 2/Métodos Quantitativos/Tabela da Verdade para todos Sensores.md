Claro! Vamos criar uma Tabela da Verdade considerando os sensores **ESP32-CAM** e **HC-SR04** (sensor de ultrassom para medir distância). Vamos definir algumas entradas e saídas baseadas em um possível uso de ambos os sensores.

### Entradas Possíveis
1. **Movimento Detectado** - Pode ser interpretado como uma condição para ativar a câmera (ESP32-CAM).
2. **Distância Detectada (HC-SR04)** - O HC-SR04 fornece uma leitura de distância; uma condição mínima pode acionar a câmera, por exemplo.
3. **Conexão Wi-Fi (ESP32-CAM)** - Indica se a ESP32-CAM está conectada à rede.

### Saídas Possíveis
1. **Imagem Capturada (ESP32-CAM)** - A ESP32-CAM tira uma foto ou grava vídeo ao detectar movimento ou uma certa distância.
2. **Alerta de Objeto Próximo** - Um sinal enviado para indicar que a distância medida pelo HC-SR04 está abaixo de um valor limite.
3. **Status da Conexão** - Indicação se a ESP32-CAM está conectada ou não.

### Exemplo de Tabela da Verdade para ESP32-CAM e HC-SR04

| Movimento Detectado | Distância (< Limiar) | Conexão Wi-Fi | Imagem Capturada | Alerta de Objeto Próximo | Status da Conexão |
|---------------------|-----------------------|---------------|------------------|--------------------------|--------------------|
| 1                   | 1                     | 1             | 1                | 1                        | 1                  |
| 1                   | 1                     | 0             | 0                | 1                        | 0                  |
| 1                   | 0                     | 1             | 1                | 0                        | 1                  |
| 1                   | 0                     | 0             | 0                | 0                        | 0                  |
| 0                   | 1                     | 1             | 1                | 1                        | 1                  |
| 0                   | 1                     | 0             | 0                | 1                        | 0                  |
| 0                   | 0                     | 1             | 0                | 0                        | 1                  |
| 0                   | 0                     | 0             | 0                | 0                        | 0                  |

### Explicação
- **Movimento Detectado**: 1 indica movimento, 0 indica ausência.
- **Distância (< Limiar)**: 1 indica que a distância medida pelo HC-SR04 está abaixo do limiar (objeto próximo), 0 indica que está acima.
- **Conexão Wi-Fi**: 1 indica que a ESP32-CAM está conectada à rede, 0 indica que não está.
- **Imagem Capturada**: 1 indica que a ESP32-CAM captura uma imagem, 0 indica que não há captura.
- **Alerta de Objeto Próximo**: 1 indica que um objeto foi detectado próximo (com base no HC-SR04), 0 indica que não.
- **Status da Conexão**: 1 indica que a ESP32-CAM está conectada à rede, 0 indica que não está.

Essa tabela cobre diferentes cenários operacionais e como cada sensor responde em cada situação. Ela pode ser ajustada conforme os requisitos específicos do seu projeto.

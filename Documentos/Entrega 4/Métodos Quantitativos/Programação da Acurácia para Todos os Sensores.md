
Para calcular a acurácia dos sensores ESP32-CAM e HC-SR04 com base em probabilidades, você pode seguir os passos a seguir. Vou detalhar um modelo geral de cálculo de acurácia utilizando a comparação entre as leituras dos sensores e os valores de referência, que chamaremos de "valor verdadeiro".

Aqui está um esboço do processo:

### 1. Coleta de Dados
Primeiro, colete uma série de leituras de cada sensor e compare essas leituras com os valores de referência.

- Para o **ESP32-CAM**, as leituras podem ser imagens ou dados de reconhecimento (por exemplo, reconhecimento de objetos).
- Para o **HC-SR04** (sensor ultrassônico de distância), as leituras são medidas de distância em centímetros.

### 2. Cálculo da Acurácia

A acurácia pode ser calculada com base na frequência de leituras corretas em comparação com o valor de referência. Podemos usar a fórmula:

\[
\text{Acurácia} = \frac{\text{Número de Leituras Corretas}}{\text{Número Total de Leituras}} \times 100\%
\]

Uma leitura é considerada "correta" se estiver dentro de uma margem aceitável de erro em relação ao valor verdadeiro.

### 3. Implementação em Código

Aqui está um exemplo em Python para calcular a acurácia de cada sensor. Vamos simular um conjunto de leituras e valores de referência.

#### Código de Exemplo

```python
import random

# Configuração dos parâmetros de margem de erro
margem_erro_esp32cam = 0.1  # 10% de margem para o ESP32-CAM
margem_erro_hcsr04 = 2.0  # 2 cm de margem para o HC-SR04

# Simulação de leituras e valores verdadeiros
leituras_esp32cam = [random.uniform(0.9, 1.1) for _ in range(100)]  # Simulando leituras do ESP32-CAM
valores_referencia_esp32cam = [1.0] * 100  # Valor esperado para ESP32-CAM

leituras_hcsr04 = [random.uniform(48, 52) for _ in range(100)]  # Simulando leituras do HC-SR04
valores_referencia_hcsr04 = [50.0] * 100  # Valor esperado para HC-SR04

# Função para calcular acurácia com base em uma margem de erro
def calcular_acuracia(leituras, referencia, margem_erro):
    leituras_corretas = sum(1 for leitura, ref in zip(leituras, referencia) if abs(leitura - ref) <= margem_erro)
    return (leituras_corretas / len(leituras)) * 100

# Calculando acurácia para cada sensor
acuracia_esp32cam = calcular_acuracia(leituras_esp32cam, valores_referencia_esp32cam, margem_erro_esp32cam)
acuracia_hcsr04 = calcular_acuracia(leituras_hcsr04, valores_referencia_hcsr04, margem_erro_hcsr04)

print(f"Acurácia do ESP32-CAM: {acuracia_esp32cam:.2f}%")
print(f"Acurácia do HC-SR04: {acuracia_hcsr04:.2f}%")
```

### Explicação do Código

1. **Configuração da Margem de Erro**: A margem de erro é ajustada conforme o tipo de sensor.
2. **Simulação de Leituras**: Utiliza-se o `random.uniform` para gerar leituras aleatórias, simulando as variações reais de leitura dos sensores.
3. **Função `calcular_acuracia`**: Conta as leituras corretas (dentro da margem de erro) e calcula a porcentagem de acurácia.
4. **Resultados**: A saída exibe a acurácia de cada sensor em porcentagem.

### Adaptação para Outros Sensores

Este modelo pode ser adaptado para outros tipos de sensores. Basta ajustar a margem de erro e o valor de referência para cada sensor específico.

Essa abordagem permite que você avalie a acurácia com base na frequência das leituras corretas, utilizando uma técnica probabilística que depende da amostra de dados coletada.

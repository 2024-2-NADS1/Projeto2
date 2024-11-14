
Para calcular a acurácia dos sensores (o quanto eles acertam nas leituras), vamos comparar as leituras dos sensores com valores de referência (o valor que seria o “verdadeiro”). Esse cálculo é baseado na frequência com que os sensores fornecem leituras dentro de uma margem de erro aceitável. Assim, a ideia é contar quantas vezes os sensores “acertam” comparado ao total de leituras feitas.

Aqui está o processo que você pode seguir:

### . Coleta de Leituras

- **Para o ESP32-CAM**: as leituras podem ser feitas em imagens ou no reconhecimento de objetos. Por exemplo, se o objetivo for identificar corretamente um objeto em uma imagem, a acurácia pode ser calculada com base na frequência de identificação correta.
  
- **Para o HC-SR04**: como ele mede a distância, as leituras devem ser comparadas a uma distância de referência. Por exemplo, se a distância correta é 50 cm, vamos ver quantas leituras saem próximas disso.

### . Definindo a Margem de Erro

Cada sensor terá uma margem de erro específica, que define o quanto a leitura pode variar do valor correto e ainda ser considerada aceitável. Por exemplo:

- **ESP32-CAM**: pode ter uma margem de erro de 10%.
- **HC-SR04**: pode ter uma margem de erro de 2 cm.

### . Código para Calcular a Acurácia

O código abaixo faz o cálculo da acurácia para os dois sensores. Ele gera algumas leituras simuladas para cada sensor, compara com os valores de referência e calcula a porcentagem de acertos.

```python
import random

# Configurando a margem de erro para cada sensor
margem_erro_esp32cam = 0.1  # 10% de margem para ESP32-CAM
margem_erro_hcsr04 = 2.0    # 2 cm de margem para HC-SR04

# Simulando leituras do ESP32-CAM e do HC-SR04
leituras_esp32cam = [random.uniform(0.9, 1.1) for _ in range(100)]  # ESP32-CAM
valores_referencia_esp32cam = [1.0] * 100  # Valor de referência para ESP32-CAM

leituras_hcsr04 = [random.uniform(48, 52) for _ in range(100)]      # HC-SR04
valores_referencia_hcsr04 = [50.0] * 100  # Valor de referência para HC-SR04

# Função que calcula a acurácia comparando leituras com o valor de referência
def calcular_acuracia(leituras, referencia, margem_erro):
    leituras_corretas = sum(1 for leitura, ref in zip(leituras, referencia) if abs(leitura - ref) <= margem_erro)
    return (leituras_corretas / len(leituras)) * 100

# Calculando a acurácia para cada sensor
acuracia_esp32cam = calcular_acuracia(leituras_esp32cam, valores_referencia_esp32cam, margem_erro_esp32cam)
acuracia_hcsr04 = calcular_acuracia(leituras_hcsr04, valores_referencia_hcsr04, margem_erro_hcsr04)

print(f"Acurácia do ESP32-CAM: {acuracia_esp32cam:.2f}%")
print(f"Acurácia do HC-SR04: {acuracia_hcsr04:.2f}%")
```

### Explicação Simples do Código

1. **Definição da Margem de Erro**: A margem de erro determina o quanto a leitura pode variar do valor verdadeiro para ainda ser considerada correta.
2. **Simulação de Leituras**: Usamos números aleatórios para simular as leituras dos sensores. No caso real, você substituiria isso pelas leituras reais.
3. **Cálculo da Acurácia**: A função `calcular_acuracia` conta quantas leituras estão dentro da margem de erro e calcula a porcentagem de acurácia.
4. **Resultados**: O código imprime a acurácia dos dois sensores como uma porcentagem.

### Conclusão

Esse código fornece uma estimativa da acurácia dos sensores com base em uma série de leituras, mostrando quantas vezes o sensor forneceu uma leitura “correta”. Basta rodá-lo para ver a acurácia de cada sensor.

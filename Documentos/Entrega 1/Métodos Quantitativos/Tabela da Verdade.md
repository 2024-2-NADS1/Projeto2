Para o desenvolvimento da tabela da verdade, escolhemos o módulo ESP32-CAM. Este módulo é baseado no microcontrolador ESP32 com uma câmera embutida, ideal para aplicações de visão computacional, segurança e monitoramento remoto. Ele combina poder de processamento e conectividade, permitindo o envio de imagens e vídeos para servidores ou dispositivos em tempo real via Wi-Fi.

O ESP32-CAM oferece uma série de pinos GPIO que podem ser configurados como entradas ou saídas digitais. A configuração correta dos pinos permite a leitura de sensores ou o controle de dispositivos, como LEDs, relés e motores. A lógica de controle dos pinos segue a tabela binária: 0 (LOW) e 1 (HIGH), correspondendo aos estados desligado (falso) e ligado (verdadeiro), respectivamente.

No projeto usando o ESP32-CAM, utilizamos sensores de movimento, temperatura e câmera para capturar imagens e identificar a presença de pragas. O sistema pode atuar com entrada digital (como sensores ou até a própria imagem da câmera processada) e gerar saídas que acionam alarmes, notificações ou registram dados.

Segue abaixo Tabela da Verdade para o ESP32-CAM, sistema básico de detecção de pragas:


| Sensor/Entrada         | Condição do Sensor | Câmera (imagem)              | Saída (Ação)    | Descrição   |
|------------------------|------------------|--------------------------------|-----------------|-------------|
| Sensor de movimento    | Ativado (1)      | Praga detectada (1)            | Alarme acionado (1) | Movimento detectado e praga identificada, aciona alarme. |
| Sensor de movimento    | Desativado (0)   | Nenhuma praga (0)              | Alarme desligado (0) | Nenhum movimento detectado, desliga o alarme. |
| Sensor de temperatura  | Temperatura alta (1) | Praga detectada (1)        | Enviar notificação (1) | Temperatura elevada e praga detectada, envia alerta via Wi-Fi.
| Sensor de temperatura  | Temperatura normal (0) | Nenhuma praga (0)        | Nenhuma ação (0) | Temperatura normal e nenhuma praga detectada, sem ação. |
| Câmera (visão computacional) | Praga detectada (1) | Imagem gerada (1)     | Alarme (1) | Detecção de praga por visão computacional, armazena imagem para análise posterior. |
| Câmera (visão computacional) | Nenhuma praga detectada (0) | Nenhuma imagem (0) | Nenhuma ação (0) | Nenhuma praga detectada pela câmera, nenhuma ação tomada. |
| Sensor de umidade      | Umidade alta (1) | Praga detectada (1)            | Enviar alerta (1) | Alta umidade e praga detectada, envia alerta para o usuário. |


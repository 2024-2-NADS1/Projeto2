Para o desenvolvimento da tabela da verdade, escolhemos o módulo ESP32-CAM. Este módulo é baseado no microcontrolador ESP32 com uma câmera embutida, ideal para aplicações de visão computacional, segurança e monitoramento remoto. Ele combina poder de processamento e conectividade, permitindo o envio de imagens e vídeos para servidores ou dispositivos em tempo real via Wi-Fi.

O ESP32-CAM oferece uma série de pinos GPIO que podem ser configurados como entradas ou saídas digitais. A configuração correta dos pinos permite a leitura de sensores ou o controle de dispositivos, como LEDs, relés e motores. A lógica de controle dos pinos segue a tabela binária: 0 (LOW) e 1 (HIGH), correspondendo aos estados desligado e ligado, respectivamente.

No projeto usando o ESP32-CAM, utilizamos sensores de movimento, temperatura e câmera para capturar imagens e identificar a presença de pragas. O sistema pode atuar com entrada digital (como sensores ou até a própria imagem da câmera processada) e gerar saídas que acionam alarmes, notificações ou registram dados.

Segue abaixo Tabela da Verdade para o ESP32-CAM, sistema básico de detecção de pragas:


| Sensor/Entrada               | Condição do Sensor | Câmera (imagem)                |
|------------------------|------------------|--------------------------------|
| Objeto detectado       | Ativo            | Captura uma foto ou vídeo      |
| Objeto não detectado   | Ativo            | Não faz nada                   |
| Conexão Wi-Fi OK       | Ativo            | Envia a imagem/vídeo           |
| Conexão Wi-Fi falhou   | Ativo            | Tenta reconectar               |
| Sem energia            | Inativo          | Sistema desligado              |


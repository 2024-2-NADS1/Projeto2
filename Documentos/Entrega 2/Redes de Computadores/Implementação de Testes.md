# Testes de Comunicação em Rede

## Objetivo
Verificar o funcionamento e desempenho da comunicação em rede entre o ESP32-CAM e um servidor remoto. Esses testes garantem que a troca de dados ocorre sem perdas ou erros e avaliam a integridade dos dados transmitidos.

## Configuração

### Requisitos
- ESP32-CAM com conexão Wi-Fi.
- Servidor para receber os dados enviados (pode ser uma API de teste HTTP).

### Estrutura do Teste
1. O ESP32-CAM se conecta à rede Wi-Fi configurada.
2. O dispositivo envia uma requisição HTTP POST para o servidor, incluindo dados de teste (ex.: simulação de captura de imagem).
3. O servidor responde com uma confirmação que é registrada no monitor serial.
4. O ESP32-CAM exibe no monitor serial a resposta do servidor, validando a integridade da comunicação.

## Execução
1. Carregue o código `testes_comunicacao.ino` no ESP32-CAM.
2. Abra o Monitor Serial para verificar a conexão e o status da comunicação.
3. O código enviará dados a cada 10 segundos e exibirá a resposta do servidor para cada envio.

## Resultados Esperados
- O ESP32-CAM envia e recebe dados com sucesso.
- O monitor serial exibe "Resposta do Servidor: OK" (ou outra confirmação) para cada requisição enviada.
- Em caso de falhas, erros específicos serão mostrados para identificação de problemas na comunicação.

## Considerações
Caso o teste falhe, verifique:
- Credenciais de Wi-Fi.
- Disponibilidade e URL do servidor de teste.
- Erros no código ou na estrutura do JSON enviado.

Para mais detalhes, consulte o [README principal](Redes de Computadores/README.md).


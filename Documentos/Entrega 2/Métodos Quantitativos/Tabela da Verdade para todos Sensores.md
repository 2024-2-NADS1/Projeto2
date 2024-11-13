Entradas Possíveis
Detecção de Movimento - Entrada de um sensor de movimento, que poderia ativar a câmera.
Comando Externo - Sinal vindo de outro dispositivo para ativar ou desativar a câmera ou Wi-Fi.
Estado da Conexão Wi-Fi - Indicação se o módulo está conectado à rede Wi-Fi.
Saídas Possíveis
Imagem Capturada - Saída quando a câmera tira uma foto ou faz uma transmissão.
Sinal de Alerta - Sinal enviado para outros dispositivos após uma detecção.
Confirmação de Conexão - Indicativo do status de conexão do módulo.
Exemplo de Tabela da Verdade Simplificada
Movimento Detectado	Conexão Wi-Fi	Comando Externo	Imagem Capturada	Alerta
1	1	1	1	1
1	0	1	0	0
0	1	0	0	0
...	...	...	...	...
Essa tabela exemplifica algumas combinações de entrada e saída. Você precisará adaptá-la para refletir os estados específicos do seu projeto e as condições de funcionamento do ESP32-CAM no sistema.







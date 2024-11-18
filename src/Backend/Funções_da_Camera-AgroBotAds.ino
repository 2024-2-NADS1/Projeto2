#include <eloquent_esp32cam.h>
#include <eloquent_esp32cam/extra/esp32/wifi/sta.h>
#include <project-1_inferencing.h>
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "esp_camera.h"
#include <WebServer.h> 

#define WIFI_SSID "Rede Wi-fi" // Nome da rede Wi-Fi
#define WIFI_PASS "senha" // Senha da rede Wi-Fi
#define HOSTNAME "aithinker" // Nome do host

// Definições do modelo da câmera
#define CAMERA_MODEL_AI_THINKER // Tem PSRAM

#if defined(CAMERA_MODEL_ESP_EYE)
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM    4
#define SIOD_GPIO_NUM    18
#define SIOC_GPIO_NUM    23

#define Y9_GPIO_NUM      36
#define Y8_GPIO_NUM      37
#define Y7_GPIO_NUM      38
#define Y6_GPIO_NUM      39
#define Y5_GPIO_NUM      35
#define Y4_GPIO_NUM      14
#define Y3_GPIO_NUM      13
#define Y2_GPIO_NUM      34
#define VSYNC_GPIO_NUM   5
#define HREF_GPIO_NUM    27
#define PCLK_GPIO_NUM    25

#elif defined(CAMERA_MODEL_AI_THINKER)
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#else
#error "Modelo da câmera não selecionado" // Erro se nenhum modelo for definido
#endif

/* Definições constantes -------------------------------------------------------- */
#define EI_CAMERA_RAW_FRAME_BUFFER_COLS           320 // Largura do buffer da imagem
#define EI_CAMERA_RAW_FRAME_BUFFER_ROWS           240 // Altura do buffer da imagem
#define EI_CAMERA_FRAME_BYTE_SIZE                 3   // Tamanho em bytes de cada pixel

using eloq::camera; // Usando o namespace da biblioteca de câmera
using eloq::wifi; // Usando o namespace da biblioteca de Wi-Fi

/* Variáveis privadas ------------------------------------------------------- */
static bool debug_nn = false; // Defina como true para ver informações de depuração
static bool is_initialised = false; // Indica se a câmera foi inicializada
uint8_t *snapshot_buf; // Ponteiro para o buffer de captura

// Configuração da câmera
static camera_config_t camera_config = {
    .pin_pwdn = PWDN_GPIO_NUM,
    .pin_reset = RESET_GPIO_NUM,
    .pin_xclk = XCLK_GPIO_NUM,
    .pin_sscb_sda = SIOD_GPIO_NUM,
    .pin_sscb_scl = SIOC_GPIO_NUM,

    .pin_d7 = Y9_GPIO_NUM,
    .pin_d6 = Y8_GPIO_NUM,
    .pin_d5 = Y7_GPIO_NUM,
    .pin_d4 = Y6_GPIO_NUM,
    .pin_d3 = Y5_GPIO_NUM,
    .pin_d2 = Y4_GPIO_NUM,
    .pin_d1 = Y3_GPIO_NUM,
    .pin_d0 = Y2_GPIO_NUM,
    .pin_vsync = VSYNC_GPIO_NUM,
    .pin_href = HREF_GPIO_NUM,
    .pin_pclk = PCLK_GPIO_NUM,

    // Frequência do XCLK 20MHz ou 10MHz para OV2640 para FPS duplo (Experimental)
    .xclk_freq_hz = 20000000,
    .ledc_timer = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0, 

    .pixel_format = PIXFORMAT_JPEG, // Formato do pixel: JPEG
    .frame_size = FRAMESIZE_QVGA,    // Tamanho do quadro: QQVGA-UXGA (não usar tamanhos acima de QVGA quando não for JPEG)

    .jpeg_quality = 12, // Qualidade JPEG: 0-63 (número menor significa maior qualidade)
    .fb_count = 1,       // Se mais de um, o I2S funciona em modo contínuo. Usar apenas com JPEG
    .fb_location = CAMERA_FB_IN_PSRAM, // Localização do buffer de quadro
    .grab_mode = CAMERA_GRAB_WHEN_EMPTY, // Modo de captura
};

/* Definições de funções ------------------------------------------------------- */
bool ei_camera_init(void); // Função para inicializar a câmera
void ei_camera_deinit(void); // Função para desinicializar a câmera
bool ei_camera_capture(uint32_t img_width, uint32_t img_height, uint8_t *out_buf); // Função para capturar imagem
static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr); // Função para obter dados da imagem
WebServer logServer(8080); // Novo servidor HTTP para logs na porta 8080
String serialLogs = ""; // Buffer global para armazenar os logs do monitor serial

/**
* @brief      Função de configuração do Arduino
*/
void setup()
{
    delay(3000); // Atraso inicial
    Serial.begin(115200); // Inicializa a comunicação serial
    Serial.println("___SERVIDOR DE COLETA DE IMAGENS___"); // Mensagem de inicialização

    // Inicializa a câmera
    if (ei_camera_init() == false) {
        Serial.println("Falha ao inicializar a câmera!"); // Mensagem de erro
        return;
    }

    // Conecta ao Wi-Fi
    while (!wifi.connect(WIFI_SSID, WIFI_PASS).isOk())
        Serial.println(wifi.exception.toString()); // Exibe erro de conexão

    // Adiciona um novo endpoint para exibir os logs
    logServer.on("/logs", []() {
        logServer.send(200, "text/plain", serialLogs); // Exibe os logs armazenados
    });

    // Inicia o servidor de logs
    logServer.begin();

    // Exibe o endereço IP do servidor
    Serial.print("Servidor de Logs iniciado em: ");
    Serial.println(WiFi.localIP()); // Mostra o endereço IP do ESP32

    Serial.println("Câmera OK"); // Mensagem de sucesso
    Serial.println("WiFi OK"); // Mensagem de sucesso
    Serial.println("Servidor de Coleta de Imagens OK"); // Mensagem de sucesso
}

/**
* @brief      Obtém dados e executa a inferência
*
* @param[in]  debug  Obtém informações de depuração se verdadeiro
*/
void loop()
{
    String logMessage = "Monitor serial ativo!"; // Mensagem de log
    Serial.println(logMessage); // Exibe a mensagem no monitor serial
    serialLogs += logMessage + "\n"; // Armazena a mensagem nos logs

    // Limita o tamanho do buffer para evitar estouro de memória
    if (serialLogs.length() > 2000) {
        serialLogs = serialLogs.substring(serialLogs.length() - 2000); // Mantém os últimos 2000 caracteres
    }

    // Em vez de wait_ms, vamos esperar pelo sinal, isso permite que threads nos cancelem...
    if (ei_sleep(5) != EI_IMPULSE_OK) {
        return; // Retorna se houver erro
    }

    snapshot_buf = (uint8_t*)malloc(EI_CAMERA_RAW_FRAME_BUFFER_COLS * EI_CAMERA_RAW_FRAME_BUFFER_ROWS * EI_CAMERA_FRAME_BYTE_SIZE); // Aloca memória para o buffer de captura

    // Verifica se a alocação foi bem-sucedida
    if(snapshot_buf == nullptr) {
        ei_printf("ERR: Falha ao alocar buffer de captura!\n"); // Mensagem de erro
        return;
    }

    ei::signal_t signal; // Estrutura de sinal
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT; // Define o comprimento total do sinal
    signal.get_data = &ei_camera_get_data; // Define a função para obter dados

    // Captura a imagem
    if (ei_camera_capture((size_t)EI_CLASSIFIER_INPUT_WIDTH, (size_t)EI_CLASSIFIER_INPUT_HEIGHT, snapshot_buf) == false) {
        ei_printf("Falha ao capturar imagem\r\n"); // Mensagem de erro
        free(snapshot_buf); // Libera memória
        return;
    }

    // Executa o classificador
    ei_impulse_result_t result = { 0 }; // Inicializa o resultado

    EI_IMPULSE_ERROR err = run_classifier(&signal, &result, debug_nn); // Executa a inferência
    if (err != EI_IMPULSE_OK) {
        ei_printf("ERR: Falha ao executar classificador (%d)\n", err); // Mensagem de erro
        return;
    }

    // Imprime as previsões
    ei_printf("Pre dições (DSP: %d ms., Classificação: %d ms., Anomalia: %d ms.): \n",
                result.timing.dsp, result.timing.classification, result.timing.anomaly);

#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    ei_printf("Caixas delimitadoras de detecção de objetos:\r\n");
    for (uint32_t i = 0; i < result.bounding_boxes_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.bounding_boxes[i];
        if (bb.value == 0) {
            continue; // Ignora se o valor da caixa for 0
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, largura: %u, altura: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }

    // Imprime os resultados da classificação
#else
    ei_printf("Previsões:\r\n");
    for (uint16_t i = 0; i < EI_CLASSIFIER_LABEL_COUNT; i++) {
        ei_printf("  %s: ", ei_classifier_inferencing_categories[i]); // Imprime a categoria
        ei_printf("%.5f\r\n", result.classification[i].value); // Imprime o valor da classificação
    }
#endif

    // Imprime o resultado da anomalia (se existir)
#if EI_CLASSIFIER_HAS_ANOMALY
    ei_printf("Previsão de anomalia: %.3f\r\n", result.anomaly);
#endif

#if EI_CLASSIFIER_HAS_VISUAL_ANOMALY
    ei_printf("Anomalias visuais:\r\n");
    for (uint32_t i = 0; i < result.visual_ad_count; i++) {
        ei_impulse_result_bounding_box_t bb = result.visual_ad_grid_cells[i];
        if (bb.value == 0) {
            continue; // Ignora se o valor da caixa for 0
        }
        ei_printf("  %s (%f) [ x: %u, y: %u, largura: %u, altura: %u ]\r\n",
                bb.label,
                bb.value,
                bb.x,
                bb.y,
                bb.width,
                bb.height);
    }
#endif

    free(snapshot_buf); // Libera a memória do buffer de captura
}

/**
 * @brief   Configura o sensor de imagem e inicia o streaming
 *
 * @retval  false se a inicialização falhar
 */
bool ei_camera_init(void) {
    if (is_initialised) return true; // Retorna se já estiver inicializada

#if defined(CAMERA_MODEL_ESP_EYE)
    pinMode(13, INPUT_PULLUP); // Configura pino 13 como entrada com pull-up
    pinMode(14, INPUT_PULLUP); // Configura pino 14 como entrada com pull-up
#endif

    // Inicializa a câmera
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        Serial.printf("Falha na inicialização da câmera com erro 0x%x\n", err); // Mensagem de erro
        return false;
    }

    sensor_t * s = esp_camera_sensor_get(); // Obtém o sensor da câmera
    // Sensores iniciais estão invertidos verticalmente e as cores estão um pouco saturadas
    if (s->id.PID == OV3660_PID) {
        s->set_vflip(s, 1); // Inverte verticalmente
        s->set_brightness(s, 1); // Aumenta um pouco o brilho
        s->set_saturation(s, 0); // Diminui a saturação
    }

#if defined(CAMERA_MODEL_M5STACK_WIDE)
    s->set_vflip(s, 1); // Inverte verticalmente
    s->set_hmirror(s, 1); // Espelha horizontalmente
#elif defined(CAMERA_MODEL_ESP_EYE)
    s->set_vflip(s, 1); // Inverte verticalmente
    s->set_hmirror(s, 1); // Espelha horizontalmente
    s->set_awb_gain(s, 1); // Ativa ganho de balanço de branco
#endif

    is_initialised = true; // Marca como inicializada
    return true; // Retorna sucesso
}

/**
 * @brief      Para o streaming de dados do sensor
 */
void ei_camera_deinit(void) {
    // Desinicializa a câmera
    esp_err_t err = esp_camera_deinit();

    if (err != ESP_OK) {
        ei_printf("Falha ao desinicializar a câmera\n return; // Retorna se houver erro
    }

    is_initialised = false; // Marca como não inicializada
    return; // Retorna
}

/**
 * @brief      Captura, redimensiona e recorta a imagem
 *
 * @param[in]  img_width     largura da imagem de saída
 * @param[in]  img_height    altura da imagem de saída
 * @param[in]  out_buf       ponteiro para armazenar a imagem de saída, NULL pode ser usado
 *                           se ei_camera_frame_buffer for usado para captura e redimensionamento/corte.
 *
 * @retval     false se não estiver inicializado, captura de imagem, redimensionamento ou corte falhar
 *
 */
bool ei_camera_capture(uint32_t img_width, uint32_t img_height, uint8_t *out_buf) {
    bool do_resize = false; // Variável para verificar se é necessário redimensionar

    if (!is_initialised) {
        ei_printf("ERR: A câmera não está inicializada\r\n"); // Mensagem de erro
        return false; // Retorna erro
    }

    camera_fb_t *fb = esp_camera_fb_get(); // Obtém o frame da câmera

    if (!fb) {
        ei_printf("Falha na captura da câmera\n"); // Mensagem de erro
        return false; // Retorna erro
    }

    bool converted = fmt2rgb888(fb->buf, fb->len, PIXFORMAT_JPEG, snapshot_buf); // Converte o formato da imagem

    esp_camera_fb_return(fb); // Retorna o frame da câmera

    if(!converted) {
        ei_printf("Falha na conversão\n"); // Mensagem de erro
        return false; // Retorna erro
    }

    // Verifica se é necessário redimensionar
    if ((img_width != EI_CAMERA_RAW_FRAME_BUFFER_COLS) || (img_height != EI_CAMERA_RAW_FRAME_BUFFER_ROWS)) {
        do_resize = true; // Marca para redimensionar
    }

    if (do_resize) {
        ei::image::processing::crop_and_interpolate_rgb888(
        out_buf,
        EI_CAMERA_RAW_FRAME_BUFFER_COLS,
        EI_CAMERA_RAW_FRAME_BUFFER_ROWS,
        out_buf,
        img_width,
        img_height); // Redimensiona a imagem
    }

    return true; // Retorna sucesso
}

static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr) {
    // Recalcula o deslocamento em índice de pixel
    size_t pixel_ix = offset * 3; // Índice do pixel
    size_t pixels_left = length; // Pixels restantes
    size_t out_ptr_ix = 0; // Índice de saída

    while (pixels_left != 0) {
        // Troca BGR por RGB aqui
        // devido a https://github.com/espressif/esp32-camera/issues/379
        out_ptr[out_ptr_ix] = (snapshot_buf[pixel_ix + 2] << 16) + (snapshot_buf[pixel_ix + 1] << 8) + snapshot_buf[pixel_ix];

        // Vai para o próximo pixel
        out_ptr_ix++;
        pixel_ix += 3; // Avança para o próximo pixel
        pixels_left--; // Decrementa pixels restantes
    }
    // E pronto!
    return 0; // Retorna sucesso
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_CAMERA
#error "Modelo inválido para o sensor atual" // Erro se o modelo não for compatível
#endif

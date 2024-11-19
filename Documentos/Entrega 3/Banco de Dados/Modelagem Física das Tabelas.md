# Modelo Físico

Modelagem física de duas tabelas com base no modelo conceitual previamente definido. A seguir, as tabelas são referentes ao ESP32-CAM e a Praga_Detectada, contendo os atributos e tipos de informação contidas no atributo.

<br>

```sh
CREATE TABLE ESP32_CAM (
     ID_DISPOSITIVO INT PRIMARY KEY,
     LOCALIZACAO VARCHAR (100) NOT NULL,
     STATUS_ATIVO_INATIVO_BOOLEAN,
     IP_LOCAL VARCHAR(15) NOT NULL
);

CREATE TABLE IMAGEM_CAPTURADA_PRAGA_DETECTADA (
     ID_IMAGEM INT PRIMARY KEY,
     URL_ARQUIVO VARCHAR(255) NOT NULL,
     DATA_HORA DATE NOT NULL,
     SEVERIDADE VARCHAR(50) NOT NULL,
     ID_PRAGA INT NOT NULL
 );
```

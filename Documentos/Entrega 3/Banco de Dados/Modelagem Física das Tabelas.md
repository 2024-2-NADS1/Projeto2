# Modelo Físico

Modelagem física de duas tabelas com base no modelo conceitual previamente definido. A seguir, as tabelas são referentes ao ESP32-CAM e a Praga_Detectada, contendo os atributos e tipos de informação contidas no atributo.

<br>

```sh
CREATE TABLE ESP32_CAM (
     LOCALIZACAO VARCHAR,
     STATUS_ATIVO_INATIVO_BOOLEAN,
     ID_DISPOSITIVO INT,
     IP_LOCAL VARCHAR
);

CREATE TABLE IMAGEM_CAPTURADA_PRAGA_DETECTADA (
     URL_ARQUIVO VARCHAR,
     DATA_HORA DATE,
     ID_IMAGEM INT,
     SEVERIDADE VARCHAR,
     ID_PRAGA INT
 );
```

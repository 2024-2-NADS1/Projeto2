# Modelo Físico de Todas as Tabelas
Modelagem física de todas as tabelas com base no modelo conceitual sensores previamente definido.

<br>

<p align="center">
<img src="https://github.com/user-attachments/assets/ce445e25-53cb-4d5c-9826-ee8858f81265" >
  <p align="center">
      
```sh
CREATE TABLE Ambiente (
    ID_Ambiente INT,
    Tipo VARCHAR,
    Localizacao VARCHAR,
    Condicoes_Climaticas VARCHAR
);

CREATE TABLE Praga (
    ID_Praga INT,
    Nome VARCHAR,
    Categoria VARCHAR
);

CREATE TABLE ESP32_CAM (
    ID_Dispositivo INT,
    IP_Local VARCHAR,
    Status_Ativo_Inativo_BOOLEAN,
    Localizacao VARCHAR,
);

CREATE TABLE Sensor_Proximidade (
    Modelo VARCHAR(50) NOT NULL,
    Status_Ativo_Inativo_BOOLEAN
);

CREATE TABLE Leitura_Proximidade (
    ID_Leitura INT,
    Data_Hora DATETIME,
    Distancia FLOAT,

);

CREATE TABLE Chassi_Tank (
    ID_Tank INT
    Modelo VARCHAR
    Localizacao VARCHAR
);
``


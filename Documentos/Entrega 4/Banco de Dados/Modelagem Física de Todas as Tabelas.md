# Modelo Físico de Todas as Tabelas
Modelagem física de todas as tabelas com base no modelo conceitual sensores previamente definido.

<br>

```sh
CREATE TABLE Ambiente (
    ID_Ambiente INT PRIMARY KEY,
    Tipo VARCHAR(50) NOT NULL,
    Localizacao VARCHAR(100) NOT NULL,
    Condicoes_Climaticas TEXT
);

CREATE TABLE ESP32_CAM (
    ID_Dispositivo INT PRIMARY KEY,
    IP_Local VARCHAR(15) NOT NULL,
    Status ENUM('Ativo', 'Inativo') DEFAULT 'Inativo',
    Localizacao VARCHAR(100) NOT NULL,
    ID_Ambiente INT NOT NULL,
    FOREIGN KEY (ID_Ambiente) REFERENCES Ambiente(ID_Ambiente)
);

CREATE TABLE Sensor_Proximidade (
    ID_Sensor INT PRIMARY KEY,
    Modelo VARCHAR(50) NOT NULL,
    Status ENUM('Ativo', 'Inativo') DEFAULT 'Inativo'
);

CREATE TABLE Leitura_Proximidade (
    ID_Leitura INT PRIMARY KEY,
    Data_Hora DATETIME NOT NULL,
    Distancia DECIMAL(5, 2) NOT NULL,
    ID_Sensor INT NOT NULL,
    FOREIGN KEY (ID_Sensor) REFERENCES Sensor_Proximidade(ID_Sensor)
);

CREATE TABLE Imagem_Capturada (
    ID_Imagem INT PRIMARY KEY,
    URL_Arquivo VARCHAR(255) NOT NULL,
    Data_Hora DATETIME NOT NULL,
    ID_Dispositivo INT NOT NULL,
    FOREIGN KEY (ID_Dispositivo) REFERENCES ESP32_CAM(ID_Dispositivo)
);

CREATE TABLE Praga (
    ID_Praga INT PRIMARY KEY,
    Nome VARCHAR(100) NOT NULL,
    Categoria VARCHAR(50) NOT NULL
);

CREATE TABLE Praga_Detectada (
    ID_Deteccao INT PRIMARY KEY,
    ID_Praga INT NOT NULL,
    ID_Imagem INT NOT NULL,
    Data_Hora DATETIME NOT NULL,
    Severidade ENUM('Baixa', 'Moderada', 'Alta') NOT NULL,
    FOREIGN KEY (ID_Praga) REFERENCES Praga(ID_Praga),
    FOREIGN KEY (ID_Imagem) REFERENCES Imagem_Capturada(ID_Imagem)
);

CREATE TABLE Chassi_Tank (
    ID_Tank INT PRIMARY KEY,
    Modelo VARCHAR(50) NOT NULL,
    Localizacao VARCHAR(100) NOT NULL
);
``


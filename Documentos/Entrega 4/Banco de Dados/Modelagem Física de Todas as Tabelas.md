#Modelo Físico

Modelagem física de duas tabelas com base no modelo conceitual previamente definido. A seguir, as tabelas são referentes ao ESP32-CAM e a Praga_Detectada, contendo os atributos e tipos de informação contidas no atributo.

<br>

```sh
CREATE TABLE ESP32_CAM (
    ID_Dispositivo INT PRIMARY KEY,
    IP_Local VARCHAR(15) NOT NULL,
    Status ENUM('Ativo', 'Inativo') DEFAULT 'Inativo',
    Localizacao VARCHAR(100) NOT NULL,
    ID_Ambiente INT NOT NULL,
    FOREIGN KEY (ID_Ambiente) REFERENCES Ambiente(ID_Ambiente)
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
``

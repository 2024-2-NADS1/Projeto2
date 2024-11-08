# FECAP - Fundação de Comércio Álvares Penteado

<p align="center">
<a href= "https://www.fecap.br/"><img src="https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRhZPrRa89Kma0ZZogxm0pi-tCn_TLKeHGVxywp-LXAFGR3B1DPouAJYHgKZGV0XTEf4AE&usqp=CAU" alt="FECAP - Fundação de Comércio Álvares Penteado" border="0"></a>
</p>

# Sistema de Monitoramento de Pragas 

## Nome do Grupo

## Integrantes: <a href="https://www.linkedin.com/in/eriane-dos-santos-oliveira/">Eriane do Santos Oliveira Dias</a>, <a href="https://www.linkedin.com/in/giovana-kamilly-ferrari-blanck/">Giovanna Kamilly Ferrari Blanck</a>, <a href="https://www.linkedin.com/in/henrique-jorge/">Henrique Jorge Martins Figueiredo</a>, <a href="https://www.linkedin.com/in/luan-rocha/">Luan Rocha da Silva</a>

## Professores Orientadores: <a href="https://www.linkedin.com/in/victorbarq/">Victor Bruno Alexander Rosetti de Queiroz</a>

## Descrição

<p align="center">
<img src="https://github.com/2024-1-NADS1-A/Projeto9/blob/main/imagens/ODS.jpg" alt="NOME DO JOGO" border="0"><br><br>
 Feito por <a href="https://github.com/2024-1-NADS1-A/Projeto9/blob/main/imagens/ODS.jpg">Objetivos de Desenvolvimento Sustentável</a> <a rel="license">
  </a></p>

O nosso projeto tem como objetivo desenvolver e implementar uma solução inovadora para o monitoramento e controle de pragas em ambientes agrícolas, utilizando sensores conectados por IoT para a detecção e identificação em tempo real de pragas. A proposta visa proporcionar uma abordagem mais eficiente, ágil e precisa na detecção de infestação de pragas, com a finalidade de reduzir os impactos negativos na produção agrícola, como por exemplo o uso de excessivo de pesticidas e promover práticas mais sustentáveis e rentáveis para os produtores rurais.
<br><br>
O sistema desenvolvido integra um carrinho robótico que percorre autonomamente a área da plantação, utilizando uma combinação de sensores e câmeras para realizar a coleta contínua de dados. Este carrinho é equipado com sensores de movimento, que detectam a presença de pragas, e câmeras de alta resolução, que capturam imagens das plantas e do solo, permitindo a análise visual das pragas presentes. A presença desses sensores e câmeras no carrinho permite uma cobertura dinâmica e extensiva das áreas agrícolas, sem a necessidade de intervenção constante por parte dos agricultores.
<br><br>
Os dados coletados pelos sensores e câmeras são processados em tempo real e transmitidos para uma plataforma de análise na nuvem. A partir dessa análise, o sistema consegue identificar padrões, como a movimentação das pragas. Caso seja detectada uma infestação, o sistema envia alertas automáticos ao agricultor, por meio de notificações no celular ou por e-mail, permitindo que ações corretivas sejam tomadas de forma rápida e eficaz.
<br><br>

## Componentes do Projetos

<br>🛠 Hardware</br>
 <br>•	Sensor ultrassônico HC – SR04</br>
 <br>•	ESP32 – CAM </br>
 <br>•	Arduino uno R4 Wifi </br>
 <br>•	Chassi Tank com esteira </br>
 <br>•	Driver Ponte H L298N </br>
 <br>•	Protoboard e Jumpers</br>
 
<br>💻  Software:</br>
 <br>•	Arduino IDE</br>
 <br>•	Blynk IOT (em andamento)</br>

##  Técnicas e Tecnologias utilizadas

- ``Arduino IDE``
- ``Blynk IOT``

## 🛠 Estrutura de pastas

-Raiz<br>
|<br>
|-->documentos<br>
  &emsp;|-->antigos<br>
  &emsp;|Documentação.docx<br>
|-->executáveis<br>
  &emsp;|-->windows<br>
  &emsp;|-->android<br>
  &emsp;|-->HTML<br>
|-->imagens<br>
|-->src<br>
  &emsp;|-->Backend<br>
  &emsp;|-->Frontend<br>
|readme.md<br>

A pasta raiz contem dois arquivos que devem ser alterados:

<b>README.MD</b>: Arquivo que serve como guia e explicação geral sobre seu projeto. O mesmo que você está lendo agora.

Há também 4 pastas que seguem da seguinte forma:

<b>documentos</b>: Toda a documentação estará nesta pasta.

<b>executáveis</b>: Binários e executáveis do projeto devem estar nesta pasta.

<b>imagens</b>: Imagens do sistema

<b>src</b>: Pasta que contém o código fonte.

## 🛠 Impacto Esperado

<b>AgroBot:</b>

Este projeto tem o potencial de transformar práticas agrícolas tradicionais, reduzindo custos e aumentando a eficiência do cultivo de hortaliças. A introdução de robôs na agricultura pode melhorar a sustentabilidade e otimizar recursos 

```sh
A tecnologia ESP32 permite que o robô seja utilizado com conectividade Bluetooth e Wi-Fi, facilitando a coleta e armazenamento de dados em tempo real. As informações capturadas podem ser exibidas em uma plataforma online, proporcionando ao usuário uma visualização imediata e remota do progresso e das condições monitoradas pelo robô.
```

<b>Arduino:</b>

Não é necessária nenhuma instalação! Basta executar o arquivo. 
O vídeo será exibido apenas se houver um servidor web, podendo ser executado como qualquer outro programa.

```sh
Coloque código do prompt de comnando se for necessário
```

<b>HTML:</b>

Não há instalação!
Encontre o index.html na pasta executáveis e execute-o como uma página WEB (através de algum browser).

## 💻 Configuração para Desenvolvimento

Descreva como instalar todas as dependências para desenvolvimento e como rodar um test-suite automatizado de algum tipo. Se necessário, faça isso para múltiplas plataformas.

Para abrir este projeto você necessita das seguintes ferramentas:

-<a href="https://godotengine.org/download">GODOT</a>

```sh
make install
npm test
Coloque código do prompt de comnando se for necessário
```

## 🗃 Histórico de lançamentos

* 07/10/2024 CONCLUÍDO: Compra de materiais (Eriane)
* 10/10/2024 ANDAMENTO: Chassi Tank (Henrique)
* 10/10/2024 ANDAMENTO: Integração ao Blynk (Luan)
* 17/10/2024 CONCLUÍDO: Teste de sensores (Todos)
* 03/11/2024 CONCLUÍDO: Divisão de afazeres 
* 07/11/2024 ANDAMENTO: Organização do github e pastas (Todos)
* 07/11/2024 ANDAMENTO: Desenvolvimento do código e circuito (Todos)
* 08/11/2024 ANDAMENTO: Documentação do projeto (Giovanna)
* 17/11/2024 ANDAMENTO: Conclusão do projeto.

## 📋 Licença/License


## 🎓 Referências

Aqui estão as referências usadas no projeto.

1. <https://github.com/iuricode/readme-template>
2. <https://github.com/gabrieldejesus/readme-model>
3. <https://chooser-beta.creativecommons.org/>
4. <https://freesound.org/>
5. <https://www.toptal.com/developers/gitignore>
6. Músicas por: <a href="https://freesound.org/people/DaveJf/sounds/616544/"> DaveJf </a> e <a href="https://freesound.org/people/DRFX/sounds/338986/"> DRFX </a> ambas com Licença CC 0.

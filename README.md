
---
# Trabalho de Conclusão de Curso

# Sistema de Automação Residencial com ESP32 - Software Embarcados

## Descrição do Projeto

Este projeto apresenta uma solução completa para **automação residencial**, utilizando o microcontrolador **ESP32**, com foco em **conforto térmico**,
**otimização de consumo energético** e **controle de dispositivos via comando de voz** e aplicativo para celular. A proposta é oferecer uma plataforma 
de baixo custo que integra hardware e software para automação de diversos dispositivos, como:

- Controle automatizado de janelas para troca térmica passiva.
- Controle de iluminação, ventiladores, aquecedores e umidificadores.
- Supervisão de condições ambientais (temperatura, umidade, chuva) por sensores dedicados.
- Controle e monitoramento via **aplicativo móvel** e integração com assistente virtual Alexa.

O sistema utiliza tecnologias avançadas como **RTOS (Real-Time Operating System)**, **banco de dados em tempo real Firebase**, e comunicação via **Wi-Fi**.

---
### Demonstração do Projeto

Assista ao vídeo no YouTube que detalha e demonstra o funcionamento do sistema de automação residencial:

[![Clique para assistir ao vídeo no YouTube](https://img.youtube.com/vi/SzaZPuNGjWI/0.jpg)](https://youtu.be/SzaZPuNGjWI)

---

## Funcionalidades

### Automação Residencial
- Controle automatizado de janelas com base em sensores de temperatura e chuva.
- Modos de operação: **manual, automático, manter frio e manter quente**.
- Otimização do consumo energético com trocas térmicas passivas e dispositivos ativos (ventilador e aquecedor).

### Controle de Dispositivos
- Ventiladores, janelas, aquecedores e umidificadores podem ser acionados manualmente por aplicação de celular ou comando de voz. 
Ou automaticamente em função das condições do ambiente predefinidas pelo usuário.
- Controle lâmpadas e computador remoto por aplicação de celular ou comando de voz.

### Monitoramento
- Leitura em tempo real de temperatura interna e externa, umidade e nível de chuva.
- Histórico de máximos e mínimos para parâmetros ambientais.

### Interface de Controle
- Aplicativo móvel.
- Comando de voz integrado à **Amazon Alexa**.

---

## Tecnologias Utilizadas

### Hardware
- Microcontrolador **ESP32**.
- Sensores:
  - **DS18B20** para temperatura.
  - **DHT22** para umidade.
  - Sensor de chuva com **LM393**.
- Relés de estado sólido e eletromecânicos.
- Motor de passo para acionamento de janelas.
- Driver de controle de potencia para motores de passo

### Software
- **RTOS** para multitarefa e gerenciamento eficiente.
- Banco de dados em tempo real Firebase para sincronização entre dispositivos.
- Desenvolvimento do firmware em IDE Arduino.
- MIT App Inventor para construção do aplicativo móvel.
- Biblioteca Espalexa para integração com Alexa.

---

## Requisitos para Execução

### Hardware Necessário
1. ESP32 (modelo ESP-WROOM-32): microcontrolador de uso geral com Wi-Fi e Bluetooth integrados.
2. Sensores de temperatura, umidade e chuva: dispositivos para aquisição de dados ambientais em tempo real.
3. Relés de estado sólido e eletromecânicos: utilizados para controle de dispositivos de alta potência.
4. Componentes adicionais para montagem de protótipos (motores, atuadores, resistores, etc.): peças necessárias para a construção do hardware funcional.

### Software Necessário
- [IDE Arduino](https://www.arduino.cc/en/software)
- Biblioteca [Firebase ESP32 Client](https://github.com/mobizt/Firebase-ESP32)
- Biblioteca [Espalexa](https://github.com/Aircoookie/Espalexa)
- **Proteus** (para simulação e prototipagem PCB).

---

## Como Executar

1. **Configurar o Ambiente:**
   - Instale a IDE Arduino e adicione o suporte ao ESP32.
   - Configure o banco de dados Firebase com autenticação.
   - Importe as bibliotecas necessárias.

2. **Desenvolvimento do Aplicativo:**
   - Importe o projeto para o MIT App Inventor.
   - Configure os endpoints de comunicação para o Firebase.

3. **Montagem de Hardware:**
   - Monte o circuito conforme especificado no capítulo 3 do TCC.

4. **Carregar o Código:**
   - Compile e carregue o código para o ESP32.

5. **Testar e Ajustar:**
   - Realize ajustes finos no aplicativo e no microcontrolador conforme necessário.

---

## Autor

**Luís Gustavo de Almeida**  
Universidade Federal de Juiz de Fora (UFJF)  
Curso de Engenharia Elétrica - Habilitação em Telecomunicações  

Orientadora: **Prof. Dra. Ana Sophia Cavalcante Vilas Boas**

---

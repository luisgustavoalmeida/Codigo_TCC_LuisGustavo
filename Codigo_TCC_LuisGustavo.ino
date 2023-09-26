///*** S H I E L D ***///
//Funciona perfeiro na 3,7,5 Firebase Realtime Database

//teste ok em 3,9,7
//teste ok em 3,8,26

TaskHandle_t Task_1;    //Roda o codigo pricipal
TaskHandle_t Task_2;    //Roda o controle da janela
//TaskHandle_t Task_3;
//TaskHandle_t Task_4;
//TaskHandle_t Task_5;

//condigo para o esp nao ficar reiniciando com a função microsegundos
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

//Semaforo
SemaphoreHandle_t holy1 = 0;  //deslixador da janela
SemaphoreHandle_t holy2 = 0; //abertura da janela
SemaphoreHandle_t holy3 = 0;  //comando da janela

//Biblioteca do Wifi
#include <WiFi.h>

//Boblioteca do ping
///#include <ESP32Ping.h>

//bibçioteca do Firebase    //https://console.firebase.google.com/u/0/project/app-lg-control-b143a/database/app-lg-control-b143a/data~2F?pli=1
#include "FirebaseESP32.h"  //https://github.com/mobizt/Firebase-ESP32
#define FIREBASE_HOST "https://app-lg-control-b143a.firebaseio.com/"
#define FIREBASE_AUTH "aB6HrwalCTlw3EzItnmOqlfh14phEAApEG1NJk9R"

const char* ssid     = "Gustavo2.4G";// "Gustavo 2.4G"  //nome da rede
const char* password = "32379089";//                     // senha da rede
byte ContWifi = 0;        //variavel usada para contar as tentativas de conectar no wifi
int SinalWifiM = 0;       // variavel de memoria para a intencidade do sinal do wifi

//Define Firebase data object
FirebaseData firebaseData1;  //referente aos comando enviado
FirebaseData firebaseData2;  // referente aos comando recebidos
//variaveis com o caminho para o Firebase
String path1 = "/APP_LG/Comandos";
String path2 = "/APP_LG/Leitura Sensores";
///String path3 = "/APP_LG/Status Comandos";
String path4 = "/APP_LG/ACK";

//variavel par receber informação
String RXDispositivo = "";    //recebe a informação de cada dispositivo em todos os comandos
String RXStatus = "";         //recebe o estatos do comando ( ligado, desligado e etc)

// Serial utilizada para comunicação com o SerialESP32 (Tx3 e RX3)
///#define SerialESP32 Serial2                 // Pinos 16 RX e 17TX //Para receber precida apenas do 16

//Biblioteca sensor de temperatura DS18b20
#define ONE_WIRE_BUS 15                     //define o pino  como entrada do sensor de temperatura
#include <DallasTemperature.h>              //biblioteca do sensor de temperatura DS18B20
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//endereço dos sensores de temperatura
DeviceAddress termometro1 = { 0x28, 0xFF, 0xB0, 0x58, 0x61, 0x15, 0x01, 0x80};    //interno                                 { 0x28, 0xFF, 0xC1, 0xCF, 0x37, 0x16, 0x04, 0x87};
DeviceAddress termometro2 = { 0x28, 0xFF, 0x77, 0x41C, 0x61, 0x15, 0x01, 0x1D};    //externo //DeviceAddress termometro2 = { 0x28, 0xFF, 0x79, 0x42, 0x38, 0x16, 0x04, 0xEd};    //externo TALVES DEFEITO

//variaveis sensor de temperatura
float TemperaturaExterna = 0;
float TemperaturaExternaMaxima = 0;
float TemperaturaExternaMinima = 99;
float TemperaturaExternaUltimoValor = 0;
float TemperaturaInterna = 0;
float TemperaturaInternaMaxima = 0;
float TemperaturaInternaMinima = 99;
float TemperaturaInternaUltimoValor = 0;
bool FlagErroExterno = true;
bool FlagErroInterno = true;
unsigned long TimeTemperaturaRequerida = 0;   //Tempo entre cada aquisição de temperatura. faz uma solicitação e se espera x segundos para buscar a resposta do sensor

//Biblioteca sensor de umidade DHT11
#include <DHT.h>
#define DHTPIN 14                           // Pino de entrada do sensor DHT11
#define DHTTYPE    DHT22                    // DHT 11
DHT dht(DHTPIN, DHTTYPE);
//variaveis sensor de umidade
float UmidadeSensor = 0;
float UmidadeSensorMaxima = 0;
float UmidadeSensorMinima = 99;
float UmidadeSensorM = 0;

// Biblioteca alexa

#define ESPALEXA_MAXDEVICES 9    //set maximum devices add-able to Espalexa
#include <Espalexa.h>
// funções de retorno de chamada
// novo tipo de retorno de chamada, contém o ponteiro do dispositivo

void Iluminacao1(EspalexaDevice* dev);
void Iluminacao2(EspalexaDevice* dev);
void Iluminacao3(EspalexaDevice* dev);
void Computador1(EspalexaDevice* dev);
void Janela1(EspalexaDevice* dev);
void Ventilador1(EspalexaDevice* dev);
void Ambiente(EspalexaDevice* dev);
void Umidificador1(EspalexaDevice* dev);
void Aquecedor1(EspalexaDevice* dev);

Espalexa espalexa;

//variaveis conputador
byte Computador = 2;

//variaveis exaustor
//byte Exaustor = 0;
//byte ExaustorDeslizador = 0;
//float ExaustorTemperaturaMaxima = 0;
//float ExaustorTemperaturaMinima = 0;

//variaveis
bool ReiniciaLeitura = false;     //variavel auxiliar para chamar a função de reiniciar as leituras
bool ZeraContagemFalhas = false;  //variavel auxiliar que chama a função que zera a contagem de reenicilizaçoes

//variaveis umidificador
float UmidadeMaxima = 0;
float UmidadeMinima = 0;
byte Umidificador = 0;
float UmidificadorTempoLigaACada = 0;
float UmidificadorTempoLigadoPor = 0;
byte UmidificadorTemporisado = 0;
unsigned int TimeLigaACada = 0;
unsigned int  TimeLigadoPor = 0;
bool LigadoPorFlag = false;
//bool UmidificadorFlag = false;
bool UmidificadorEstado = false;
bool UmidificadorEstadoM = false;

//Variaveis Aquecedor
byte Aquecedor = 0;
float AquecedorTemperaturaMinima = 0;
float AquecedorTemperaturaMaxima = 0;
bool AquecedorEstadoM = false;
bool AquecedorEstado = false;

//variaveis ventilador
byte Ventilador = 0;
byte VentiladorDeslizador = 0;
float VentiladorTemperaturaMaxima = 0;
float VentiladorTemperaturaMinima = 0;
byte VelocidadeVentilador = 0;
byte VelocidadeVentiladorM = 0;
bool VentiladorJaFoiLigado = false; //variavel auxiliar que permite iniciar o ventilador em plena tensao na partida por algunns segundos

//variaveisToque
unsigned long TimeToque1 = 0;                          //Váriavel para guardar o tempo do ultimo toque no sensor da parede.
unsigned long TimeToque2 = 0;                          //Váriavel para guardar o tempo do ultimo toque no sensor da mesa.
volatile bool FlagLerSaidas = false;

//Variaveis janela
byte Janela = 0;                      //comandos
byte JanelaDeslizador = 0;            //valor do deslizador no aplicativo
float JanelaTemperaturaMaxima = 0;    //referencia de temperatura
float JanelaTemperaturaMinima = 0;    //referencia de temperatura
const byte AberturaTotal = 100;       //numero maximo de passos que o motor pode dar para abir a janela sem acabar o fuso
byte ContJanela = AberturaTotal;                //conta cada passo completo do motor de passo
byte PosicaoJanela = AberturaTotal;             //recebe o valor convertido do deslizador de 0 a 100% para um valor de 0 a 1707
byte AberturaJanela = 100;            //recebe o valor convertido do numero de passos de 0 a 1707 para um valor de 0 a 100% para ser mostrado no app
byte AberturaJanelaM = 100;           //memoria
int delayTask = 1000;                 //intervalo de tempo para a Task de controle da janela quando esta movimentar a janela deley grande quado esta movendo delay 0
byte Flag_Janela = 3;                 //variavel auxiliar
byte JanelaAbertura = 3;              //variavel que tranfere a informação abri ou fechar da Task1 para a Task2
byte JanelaAberturaTask = 3;          //variavel que recebe a informação abri ou fechar da Task1 para a Task2
bool FlagAberturaJanela = true;
unsigned long TimeStepJanela = 0;
bool FlagTimeStepJanela = true;

//Motor de passo
int FrequanciaStepe = 1300; // tempo entre cada passo do motor
int PeriodoStepe = 801;
// Variavel de Histerese usado na janela e ventilador
float Histerese = 0.30;                      // Histerese de temperatura para janela e ventilador

//Media movel
//#define n 25        //número de pontos da média móvel
//long MediaMovel();       //Função para filtro de média móvel
int numbers[200];        //vetor com os valores para média móvel ( ajustaver valor caso necessario)
//Sensor de chuva
int Chuva = 0;                              //valor lido do sensor de chuva
byte SensibilidadeSensorDeChuva = 2 ;       //limite de chuva para se mandar fechar a janela
byte ChuvaM = 0;

//Variaveis auxiliares
int loopalexa = 0;            // usadi no while da alexa para dedicar processamento para ela
int ContLoop = 0;            //conta o loop para chamar menos vezes cada cunção
byte ContLoop2 = 0;            //conta o loop para chamar menos vezes cada cunção
bool Iniciando = false;           //variavel para nao deicar rodar alguns comando quando se esta iniciando o esp
bool FlagTask_1 = false;          //para mandar iniciar a Task apenas umavez
bool FlagTask_2 = false;          //para mandar iniciar a Task apenas umavez

//Variaveis sensor de tensão
float TensaoM = 0;

//variavel LDR
int ValorLDRM = 1;

//teste de comunicação
unsigned long TimeComunicacao = 0;            //se maior que x segundos manda reconecar ou manda reiniciar o esp
unsigned long TimeTesteComunicacao = 0;       //testa se o esp e firebase estao ativos e comunicando a cada x segundos
bool FlagACK = false;                             //manda um caracter para o firibase toda vez que recebe um comando
bool FlagACKcomuta = false;                       //manda um caracter para o firibase toda vez que recebe um comando. comuta o caracter enviado
bool ContESP32ativo  = false;                     //testa se o esp e firebase estao ativos e comunicando a cada x segundos

// variavel comunicação serial 2
///int ValorRSSI_BLE  = 0;
///bool StatusBLE = false;
///bool StatusIP = false;
///unsigned long TimeIP = 0;
///byte M_IP = 0;
///bool StatusFeito = true ;
///unsigned long TimeIniciouAgora = 0;

//Variaveis sensor de presença
//bool ComputadorPresenca = false;
//bool ExaustorPresenca = false;
///bool Iluminacao1Presenca = false;
///bool Iluminacao2Presenca = false;
///bool IluminacaoMesaPresenca = false;
///bool IluminacaoIndiretaPresenca = false;
///bool JanelaPresenca = false;
//bool UmidificadorPresenca = false;
///bool VentiladorPresenca = false;
//bool ComputadorPresencaEstado = false;
//byte ExaustorPresencaEstado = 0;
///bool Iluminacao1PresencaEstado = false;
///bool Iluminacao2PresencaEstado = false;
///bool IluminacaoMesaPresencaEstado = false;
///bool IluminacaoIndiretaPresencaEstado = false;
///byte JanelaPresencaEstado = 0;
//byte UmidificadorPresencaEstado = 0;
//bool UmidificadorTemporisadoPresencaEstado = false;
///byte VentiladorPresencaEstado = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//define as saidas/entrados
///////numeros dos pinos / função ///////
//Entradas analogicas
#define EntradaTensao     36 //pino de leitura de tensão                
#define EntradaLDR        39 //Porta analógica utilizada pelo LDR
#define EntradaChuva      35 //pino de leitura de tensão
//Entradas digitais
#define JanelaFechada     27 // sensor fim de curso
#define SensorComputador  34 // sensor computador ligado ou desligado
//Saidas digitais
//  #define saida1           // saida um modificada
#define saida2            19 //iluminação 1 quarto
#define saida3            18 //iluminação 2 quarto
#define saida4            23 //iluminação mesa
#define saida5            0  //iluminação indireta
#define saida6            13 // computador
#define saida7            2  //umidificador
#define saida8            32 // Aquecedor
//  #define saida9
#define saidaPWM1         5  //Ventilador  
//portas motor de PASSO
//portas motor de passo
#define DirJanela           26
#define StepJanela          25
#define EnableJanela        33

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//void printResult(FirebaseData &data);
void printResult(StreamData &data);
void streamCallback (StreamData data) { //recebe comandos do bamco de dados
  TimeComunicacao = millis();           // se nao conectado reseta o time de teste de comunicação
  //Serial.println("Stream Data1 disponível...");
  //Serial.println("CAMINHO DA STREAM: " + data.streamPath());
  //Serial.println("CAMINHO DO EVENTO: " + data.dataPath());
  //Serial.println("TIPO DE DADOS: " + data.dataType());
  //Serial.println("TIPO DE EVENTO: " + data.eventType());
  //Serial.print("VALOR: ");
  //Serial.println(data.stringData());
  if (data.dataType() == "json") {            //quando acaba de iniciar uma conexao recebe o estatus de todos os dispositivos do firebase
    //Serial.println("####### inicio da inicialização");
    Iniciando = false;                            // variavel auxiliar para nao acionar as tasks das janela antes do loop princiapal
    printResult(data);
    //Serial.println("#######");
    Iniciando = true;
    delay(100);
  }
  if (data.dataType() == "string") {
    RXDispositivo = data.dataPath();
    RXStatus = data.stringData();
    //Serial.println();
    //Serial.println("_______Recebido :__________");
    //Serial.print("Dispositivo: ");
    //Serial.println(RXDispositivo);
    //Serial.print("Status: ");
    //Serial.println(RXStatus);
    //Serial.println();

    if (RXDispositivo.equals("/Z ESP32 ativo")) {             //teste de comunicação ativa
      return;
    } else {
      AtivaComandos();
    }
  }
}//recebe comandos do bamco de dados
void streamTimeoutCallback(bool timeout) {
  /* if (timeout)
    {
     Serial.println();
     Serial.println("Tempo limite de transmissão, retomar transmissão ...");
     Serial.println();
    }*/
}
//watchdog/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
hw_timer_t *timer1 = NULL; //faz o controle do temporizador (interrupção por tempo)
hw_timer_t *timer2 = NULL; //faz o controle do temporizador (interrupção por tempo)
//função que o temporizador irá chamar, para reiniciar o ESP32
void IRAM_ATTR resetModule1() {
  ets_printf("(#####watchdog 1#####)\n"); //imprime no log de erros
  esp_restart(); //reinicia o chip
}
void IRAM_ATTR resetModule2() {
  ets_printf("(#####watchdog 2#####)\n"); //imprime no log de erros
  esp_restart(); //reinicia o chip
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //Serial.begin(115200);                     //serial USB
  // Iniciamos a serial 2 de comunicação com o ESP com o time de tempo morto de 100 milesegundos
  ///  SerialESP32.begin(115200);                //serial de comunicação entre os ESPs
  ///  SerialESP32.setTimeout(100);              //tempo morto
  ///  delay(100);

  //Crias Tascks////////////////////////////////////////////////////////////////////////////////////////////////////////////
  xTaskCreatePinnedToCore(
    Task1code,    /* função que implementa a tarefa */
    "Task1",      /* nome da tarefa */
    12000,        /* número de palavras a serem alocadas para uso com a pilha da tarefa */
    NULL,         /* parâmetro de entrada para a tarefa (pode ser NULL) */
    7,            /* prioridade da tarefa (0 a N) */
    &Task_1,      /* referência para a tarefa (pode ser NULL) */
    1);           /* Núcleo que executará a tarefa */
  delay(500);
  vTaskSuspend(Task_1);

  xTaskCreatePinnedToCore( //Abrir Janela
    Task2code,    /* função que implementa a tarefa */
    "Task2",      /* nome da tarefa */
    10000,        /* número de palavras a serem alocadas para uso com a pilha da tarefa */
    NULL,         /* parâmetro de entrada para a tarefa (pode ser NULL) */
    7,            /* prioridade da tarefa (0 a N) */
    &Task_2,      /* referência para a tarefa (pode ser NULL) */
    0);           /* Núcleo que executará a tarefa */
  delay(500);
  vTaskSuspend(Task_2);
  /*  xTaskCreatePinnedToCore( //Fechar Janela
      Task3code,    // função que implementa a tarefa
      "Task3",      // nome da tarefa
      8000,         // número de palavras a serem alocadas para uso com a pilha da tarefa
      NULL,         // parâmetro de entrada para a tarefa (pode ser NULL)
      6,            // prioridade da tarefa (0 a N)
      &Task_3,      // referência para a tarefa (pode ser NULL)
      0);           // Núcleo que executará a tarefa
    delay(500);
    vTaskSuspend(Task_3);

    xTaskCreatePinnedToCore( //Manual Janela
      Task4code,    // função que implementa a tarefa
      "Task4",      // nome da tarefa
      10000,        // número de palavras a serem alocadas para uso com a pilha da tarefa
      NULL,         // parâmetro de entrada para a tarefa (pode ser NULL)
      7,            // prioridade da tarefa (0 a N)
      &Task_4,      // referência para a tarefa (pode ser NULL)
      0);           // Núcleo que executará a tarefa
    delay(500);
    vTaskSuspend(Task_4);

    xTaskCreatePinnedToCore(
      Task5code,   // função que implementa a tarefa
      "Task5",     // nome da tarefa
      10000,       // número de palavras a serem alocadas para uso com a pilha da tarefa
      NULL,        // parâmetro de entrada para a tarefa (pode ser NULL)
      5,           // prioridade da tarefa (0 a N)
      &Task_5,     // referência para a tarefa (pode ser NULL)
      0);          // Núcleo que executará a tarefa
    delay(500);
    vTaskSuspend(Task_5);  */
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  vSemaphoreCreateBinary(holy1);              //cria semáforo binário//deslixador da janela
  //xSemaphoreTake(holy1,0);                  //pega
  xSemaphoreGive(holy1);                      //libera
  vSemaphoreCreateBinary(holy2);              //cria semáforo binário//abertura da janela
  //xSemaphoreTake(holy2,0);                  //pega
  xSemaphoreGive(holy2);                      //libera
  vSemaphoreCreateBinary(holy3);              //cria semáforo binário//comando da janela
  //xSemaphoreTake(holy3,0);                  //pega
  xSemaphoreGive(holy3);                      //libera
  //inicia o Wifi
  WiFi.begin(ssid, password);
  //Serial.print("Connectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    TimeComunicacao = millis();
    delay(300);
    if (ContWifi >= 200) {
      //Serial.print("Wifi não conecta, reiniciando o ESP");
      delay(300);
      esp_restart(); //reinicia o chip
    }
    ContWifi = ContWifi + 1;
  }
  //Serial.println();
  //Serial.print("Connectado com o endereço IP: ");
  //Serial.println(WiFi.localIP());
  //Serial.println();

  //inicia o Firebase
  //Configure a credencial do Firebase em setup ()
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  //Opcional, defina a reconexão do AP em setup ()
  Firebase.reconnectWiFi(true);
  // Opcional, defina o número de novas tentativas automáticas ao ler / armazenar dados
  //Firebase.setMaxRetry (firebaseData1, 3 );                                                     //******%%%%% teste
  //Firebase.setMaxRetry (firebaseData2, 3 );
  //inicia a função do Callback que recebe os dados do Faribase
  Firebase.beginStream(firebaseData2, path1 );
  Firebase.setStreamCallback(firebaseData2, streamCallback, streamTimeoutCallback);

  // inicializa os dispositivos da alexa
 
  espalexa.addDevice("Iluminação Amarela", Iluminacao1, EspalexaDeviceType::onoff); //non-dimmable device Iluminação Amarela
  espalexa.addDevice("Iluminação Branca", Iluminacao2, EspalexaDeviceType::onoff); //non-dimmable device Iluminação Branca
  espalexa.addDevice("Iluminação Mesa", Iluminacao3, EspalexaDeviceType::onoff); //non-dimmable device Iluminação Mesa
  espalexa.addDevice("Computador", Computador1, EspalexaDeviceType::onoff); //non-dimmable device Iluminação Indireta
  espalexa.addDevice("Janela", Janela1, EspalexaDeviceType::dimmable, 100); //non-dimmable device
  espalexa.addDevice("Ventilador", Ventilador1, EspalexaDeviceType::dimmable, 100); //non-dimmable device
  espalexa.addDevice("Ambiente", Ambiente, EspalexaDeviceType::dimmable, 100); //non-dimmable device
  espalexa.addDevice("Umidificador", Umidificador1, EspalexaDeviceType::dimmable, 100); //non-dimmable device
  espalexa.addDevice("Aquecedor", Aquecedor1, EspalexaDeviceType::dimmable, 100); //non-dimmable device
  espalexa.begin();

  //Toque. configura a interrupição realisada pelo toque
  touchAttachInterrupt(12, Toque1, 35);       // (pino , função , sensibilidade )Atribui uma função toque quando for detectado um valor menor de (10) ao pino (14).
  touchAttachInterrupt(4, Toque2, 15);        //(pino , função , sensibilidade )Atribui uma função toque quando for detectado um valor menor de (10) ao pino (4).

  //inicialisa sensor de temperatura
  sensors.begin();     //Inicialisa sensor de temperatra
  sensors.setResolution(termometro1, 12);   // ajusta resoluçao do sensor 9 a 12
  sensors.setResolution(termometro2, 12);   // ajusta resoluçao do sensor 9 a 12
  sensors.requestTemperatures();            //sensores de temperatura
  TimeTemperaturaRequerida = millis();

  // inicialisa DHT 11 sensor de temperatura e umidade
  dht.begin();

  // pino fim de cusrso janela fechada
  pinMode(JanelaFechada, INPUT);            //27
  // Sensor de computador ligado ou desligado
  pinMode(SensorComputador, INPUT);         //0
  //Saidas motor de passo
  //Pinos de saida do motor de passo
  pinMode(DirJanela, OUTPUT);         //25
  pinMode(StepJanela, OUTPUT);        //26
  pinMode(EnableJanela, OUTPUT);      //33

  //deixa as bobinas do motor de passo desenergisada
  //digitalWrite(StepJanela, LOW);
  digitalWrite(DirJanela, LOW);
  digitalWrite(EnableJanela, HIGH);

  //define os pinos como saidas
  //    pinMode(saida1,OUTPUT);
  pinMode(saida2, OUTPUT);                  //19 iluminação 1 quarto
  pinMode(saida3, OUTPUT);                  //17 iluminação 2 quarto
  pinMode(saida4, OUTPUT);                  //5 iluminação mesa
  pinMode(saida5, OUTPUT);                  //18 iluminação indireta
  pinMode(saida6, OUTPUT);                  //13 computador
  pinMode(saida7, OUTPUT);                  //0  humidificador
  pinMode(saida8,OUTPUT);                   //16 aquecedor
  //    pinMode(saida9,OUTPUT);
  //    pinMode(saida8,OUTPUT);

  //inicialisa as saidas com valores
  //digitalWrite(saida1,LOW);
  //digitalWrite(saida2, HIGH);             //19 iluminação 1 quarto
  //digitalWrite(saida3, HIGH);             //17 iluminação 2 quarto
  //digitalWrite(saida4, HIGH);             //5 iluminação mesa
  //digitalWrite(saida5, HIGH);             //18 iluminação indireta
  digitalWrite(saida6, LOW);                //13 computador
  //digitalWrite(saida7,HIGH);              //0umidificador
  //digitalWrite(saida8,LOW);
  //digitalWrite(saida9,LOW);

  //PWM configuraçãp
  pinMode(saidaPWM1, OUTPUT);
  ledcAttachPin(saidaPWM1, 2);              //Atribuimos (pino, canal de 0 a 15) .
  ledcSetup(2, 699, 10);                    //Atribuimos (canal, frequencia, resolução 2^x)
  ledcWrite(2, 1024);                       //Atribuimos (canal, valor da resolução desejada)

  ledcAttachPin(StepJanela, 1);             //Atribuimos (pino, canal de 0 a 15) .
  ledcSetup(1, FrequanciaStepe, 1);         //Atribuimos (canal, frequencia, resolução 2^x)
  ledcWrite(1, 0);                          //Atribuimos (canal, valor da resolução desejada)

  //chama a função que recupera os valores das variaveis, funcionando como memoria apos reiniciar
  RecuperaValores();
  delay(100);

  TimeStepJanela = millis();
  TimeToque1 = millis();
  TimeToque2 = millis();
  TimeComunicacao = millis();
  TimeTesteComunicacao = millis();
  ///  TimeIniciouAgora = millis();
  ///  TimeIP = millis();
  //  SerialESP32.println("123");               // manda codigo para o segundo espe para que responda com o status do BLE
  //watchdog//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //watchdog task 1
  timer1 = timerBegin(0, 80, true); //timerID 0, div 80
  //timer, callback, interrupção de borda
  timerAttachInterrupt(timer1, &resetModule1, true);
  //timer, tempo (us), repetição
  timerAlarmWrite(timer1, 60000000, true);
  timerAlarmEnable(timer1); //habilita a interrupção
  //watchdog task 2
  timer2 = timerBegin(2, 80, true); //timerID 0, div 80
  //timer, callback, interrupção de borda
  timerAttachInterrupt(timer2, &resetModule2, true);
  //timer, tempo (us), repetição
  timerAlarmWrite(timer2, 60000000, true);
  timerAlarmEnable(timer2); //habilita a interrupção

}// fim void setup()
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Task1code( void * pvParameters ) {      //Loop principal
  //Serial.print("Task1 running on core ");
  //Serial.println(xPortGetCoreID());
  vTaskDelay(pdMS_TO_TICKS(10000));

  while (true) {
    timerWrite(timer1, 0); //reseta o temporizador (alimenta o watchdog)
    //Serial.println("Task 1");

    espalexa.loop();
    while (loopalexa < 20000) {
      espalexa.loop();
      loopalexa ++;
    }

    if (!FlagLerSaidas) {

      if (WiFi.status() == WL_CONNECTED) {
        //Serial.println(" Conectado ao wifi");
        if (FlagACK) {
          ACK();
          TimeTesteComunicacao = millis();
        }
        else if ((millis() - TimeTesteComunicacao ) > 10000) {
          ESP32ativo();                           //escreve no Faribase a cada ciclo do lupe para se identificar falha de comunicação
          TimeTesteComunicacao = millis();
        }
        //ComputadorAcionar();                    //testa se o computador esta ligado ou nao e manda para o FB. Aciona o computador
        if (ContLoop == 200) {
          SensorUmidade();                      //realisa leitura de umidade relativa do ambiente
          ContLoop = ContLoop + 1;
        }
        else if (ContLoop == 400) {
          Sinalwifi();                          // verifica i nivel de sinal do Wifi
          ContLoop = ContLoop + 1;
        }
        else if (ContLoop == 800) {
          Tensao();                             //verifica o nivel de tensao de alimentação do esp
          ContLoop = ContLoop + 1;
        }
        else if (ContLoop == 1000) {
          Luminosidade();                       //verifica a luminosidade do anbiente
          ContLoop = ContLoop + 1;
        }
        else if (ContLoop > 1000) {
          ContLoop = 0;
        }
        else {
          ContLoop = ContLoop + 1;
        }
      }
      else {
        TimeComunicacao = millis();           // se nao conectado reseta o time de teste de comunicação
      }


      if (ReiniciaLeitura) {             //quando recebe o comando de reiniciar leturas chama função que apaga os maximos e minimos das leituras
        Reenicialeituras();                   //função que apaga os maximos e minimos das leituras
      }
      if (ZeraContagemFalhas) {
        ReeniciaContagemFalhas();
      }
      SensorTemperatura();                    //verifica a temperatura ambiente
    }//if(!FlagLerSaidas)
    
    ControleVentilador();                   //função de controle do ventilador
    SensorChuva();                          //verifica se esta chovendo
    ControleJanela();                       //função de controle da janela
    ControleUmidificador();                 //função de controle do umidificador
    ControleAquecedor ();                   //função de controle do aquecedor
    ComputadorAcionar();                    //função de controle do computador
   
    ///RecebeSerial2();    //verifica se recebeu alguma coisa do segundo esp. nivel de sinal e se esta presente ou nao o dispositivo
    
    if (FlagLerSaidas) {
      ContLoop2 = ContLoop2 + 1;
      if (( (touchRead(12)) >= 16) && ( (touchRead(4)) >= 16)) {     // depois que foi realisado algum toque no sensor de toque atualisa o estarus da iluminação no faribase
        if (ContLoop2 >= 20) {
          LerSaidas();                        //chama função que le cada saida do esp vinculadas ao sensor de toque e atualisa status do firebasa
          ContLoop2 = 0;
        }
      }
    }

    //vTaskSuspend(NULL);
    //Serial.println("Task 1 fim");
    vTaskDelay(pdMS_TO_TICKS(25));           //delay na tasque
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Task2code( void * pvParameters ) {     //Abrir Janela
  //Serial.print("Task2 running on core ");
  //Serial.println(xPortGetCoreID());
  vTaskDelay(pdMS_TO_TICKS(10000));
  while (true) {
    timerWrite(timer2, 0); //reseta o temporizador (alimenta o watchdog)
    //Serial.println("     Task 2");
    JanelaPosicao();
    //vTaskSuspend(NULL);
    vTaskDelay(pdMS_TO_TICKS(delayTask));
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*void Task3code( void * pvParameters ) {     // Fechar janela
  Serial.print("Task3 running on core ");
  Serial.println(xPortGetCoreID());
  vTaskDelay(pdMS_TO_TICKS(20000));
  while (true) {
    //Serial.println("Task 3");
    FecharJanela();
    //vTaskSuspend(NULL);
    vTaskDelay(pdMS_TO_TICKS(delayTask));
  }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Task4code( void * pvParameters ) {     //coloca janela na posição desejada
  Serial.print("Task4 running on core ");
  Serial.println(xPortGetCoreID());
  vTaskDelay(pdMS_TO_TICKS(10000));
  while (true) {
    timerWrite(timer2, 0); //reseta o temporizador (alimenta o watchdog)
    //Serial.println("     Task 4");
    JanelaPosicao();
    //vTaskSuspend(NULL);
    vTaskDelay(pdMS_TO_TICKS(delayTask));
  }
  }
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void Task5code( void * pvParameters ) {   //reserva
  Serial.print("Task5 running on core ");
  Serial.println(xPortGetCoreID());
  vTaskDelay(pdMS_TO_TICKS(25000));
  while (true) {
    //Serial.println("Task 5");
    vTaskSuspend(NULL);
    vTaskDelay(pdMS_TO_TICKS(4000));
  }
  }*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {                               //testa a conexão do wifi se falhar chama função conect
  //codigo para o esp nao ficar reiniciando com a função microssegundos
  TIMERG0.wdt_wprotect = TIMG_WDT_WKEY_VALUE;
  TIMERG0.wdt_feed = 1;
  TIMERG0.wdt_wprotect = 0;

  if (WiFi.status() == WL_CONNECTED) { //testa se conectado
    if ((millis() - TimeComunicacao + 50) > 90000) {
      connect();
    }
  }
  if ((millis() - TimeComunicacao + 50) > 300000) { // reinicia o esp se nao comunica por x minutos
    //Serial.println("Reinicia por tempo morto de comunicação LOOP");
    delay(100);
    ets_printf("(***falha de comunicação***)\n"); //imprime no log de erros
    esp_restart(); //reinicia o chip
  }
  if (!FlagTask_1) {
    timerWrite(timer1, 0); //reseta o temporizador (alimenta o watchdog)
    timerWrite(timer2, 0); //reseta o temporizador (alimenta o watchdog)
    vTaskResume(Task_1); //inicia a task 1 responsavel pelo controle de tudo
    FlagTask_1 = true;
  }
  delay(2500);
}

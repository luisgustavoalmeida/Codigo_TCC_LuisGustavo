//our callback functions
void Iluminacao1(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()) {
    //Serial.println("ON");
    digitalWrite(saida2, LOW);  //19 iluminação 1 quarto
  }
  else {
    //Serial.println("OFF");
    digitalWrite(saida2, HIGH);  //19 iluminação 1 quarto
  }
  FlagLerSaidas = true;
  loopalexa = 0;
}
void Iluminacao2(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()) {
    //Serial.println("ON");
    digitalWrite(saida3, LOW);   //17 iluminação 2 quarto
  }
  else {
    //Serial.println("OFF");
    digitalWrite(saida3, HIGH);   //17 iluminação 2 quarto
  }
  FlagLerSaidas = true;
  loopalexa = 0;
}
void Iluminacao3(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()) {
    //Serial.println("ON");
    digitalWrite(saida4, LOW);  //5 iluminação mesa
  }
  else {
    //Serial.println("OFF");
    digitalWrite(saida4, HIGH);  //5 iluminação mesa
  }
  FlagLerSaidas = true;
  loopalexa = 0;
}
void Computador1 (EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  if (d->getValue()) {
    Computador = 1;    
    //Serial.println("ON");
    //digitalWrite(saida5, HIGH);    //18 iluminação indireta    
  }
  else {
    Computador = 0;
    //Serial.println("OFF");
    //digitalWrite(saida5, LOW);    //18 iluminação indireta
  }
  FlagLerSaidas = true;
  loopalexa = 0;
  //ComputadorAcionar();
}
void Janela1(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required
  uint8_t percent = d->getPercent();
  if (percent == 1) { //abrir
    Janela = 1;
    xSemaphoreTake(holy1, 0);
    JanelaDeslizador = 100;     //converte um string para uma int
    xSemaphoreGive(holy1);
  }
  else if (percent == 0) {//fechar
    Janela = 0;
  }
  else if (percent == 2) {//automatico
    Janela = 2;//automatico
  }
  else if (percent == 3) {//Manter frio
    Janela = 3;
  }
  else if (percent == 4) {//manter quente
    Janela = 4;
  }
  else if ( (percent >15) &&(percent < 29)) {
    JanelaTemperaturaMaxima = percent + 0.25;
    JanelaTemperaturaMinima = percent - 0.25;
    Janela = 2;//automatico
  }
  else {
    xSemaphoreTake(holy1, 0);
    JanelaDeslizador = percent;     //converte um string para uma int
    xSemaphoreGive(holy1);

  }
   
    FlagLerSaidas = true;
    loopalexa = 0;
    //ControleJanela();
}
void Ventilador1(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  uint8_t percent = d->getPercent();

  if (percent == 1) {//ligado
    Ventilador = 1;
    VentiladorDeslizador = 100;
  }
  else if (percent == 0) {//Desligado
    Ventilador = 0;
  }
  else if (percent == 2) { //automatico
    Ventilador = 2;//automatico
    VentiladorDeslizador = 100;
  }
  else if ( (percent >15) &&(percent < 29)) {//manter quente
    VentiladorTemperaturaMaxima = percent + 0.25;
    VentiladorTemperaturaMinima = percent - 0.25;
    VentiladorDeslizador = 100;
    Ventilador = 2;
  }
  else {
    VentiladorDeslizador = percent;
  }
    FlagLerSaidas = true;
    loopalexa = 0;
    //ControleVentilador();
}

void Aquecedor1(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  uint8_t percent = d->getPercent();

  if (percent == 1) {//ligado
    Aquecedor = 1;
  }
  else if (percent == 0) {//Desligado
    Aquecedor = 0;
  }
  else if (percent == 2) { //automatico
    Aquecedor = 2;
  }
  else {
    AquecedorTemperaturaMaxima = percent + 0.25;
    AquecedorTemperaturaMinima = percent - 0.25;
    Aquecedor = 2;//automatico
  }
  FlagLerSaidas = true;
  loopalexa = 0;
  //ControleAquecedor();
}

void Ambiente(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  //uint8_t percent = d->getPercent();
  uint8_t percent = d->getDegrees();
  //uint8_t percent = d->getCt();
  
  VentiladorTemperaturaMaxima = percent + 0.75 + Histerese;
  VentiladorTemperaturaMinima = percent + 0.25 + Histerese;
  Ventilador = 2;//automatico
  VentiladorDeslizador = 100;
  
  JanelaTemperaturaMaxima = percent + 0.25;
  JanelaTemperaturaMinima = percent - 0.25;
  Janela = 2;//automatico
  JanelaDeslizador = 100;
    
  AquecedorTemperaturaMaxima = percent - 0.25 - Histerese;
  AquecedorTemperaturaMinima = percent - 0.75 - Histerese;  
  Aquecedor = 2;//automatico
  
  FlagLerSaidas = true;
  loopalexa = 0;
}
void Umidificador1(EspalexaDevice* d) {
  if (d == nullptr) return; //this is good practice, but not required

  uint8_t percent = d->getPercent();

  if (percent == 1) {//ligado
    Umidificador = 1;
  }
  else if (percent == 0) {//Desligado
    Umidificador = 0;
  }
  else if (percent == 2) { //automatico
    Umidificador = 2;
  }
  else {
    UmidadeMaxima = percent;
    UmidadeMinima = percent - 5;
    Umidificador = 2;
  }
  FlagLerSaidas = true;
  loopalexa = 0;
  //ControleUmidificador();
}

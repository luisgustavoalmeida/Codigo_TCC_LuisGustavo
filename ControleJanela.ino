//Core 1
void ControleJanela() {                     //controla a janela //(Janela) == (  0 = fechar/ 1 = manual/ 2 = automatico/ 3 = manter frio/ 4 = manter quente )

  if ((Janela == 0) || ( Chuva > SensibilidadeSensorDeChuva)) { // se janela fechar ou se chuva FECHA
    ControleJanelaFechar();
  }
  else if (Janela == 1) { //se janela em manual
    ControleJanelaAbrir();
  }
  else if (Janela == 2) { //se janela automatico // Mantem em uma faixa de temperatura
    if (TemperaturaInterna <= JanelaTemperaturaMinima) { // se dentro esta mais frio que o minimo
      // Manter quente
      if ((TemperaturaInterna + Histerese) < TemperaturaExterna) {//abrir();
        ControleJanelaAbrir();
      }
      else if ((TemperaturaInterna - Histerese) > TemperaturaExterna) { //fechar();
        ControleJanelaFechar();
      }
    }
    // Manter frio
    else if ( TemperaturaInterna >= JanelaTemperaturaMaxima ) { // se dentro esta mais quente que o maximo // Manter frio
      if ((TemperaturaInterna - Histerese) > TemperaturaExterna) {//abrir();
        ControleJanelaAbrir();
      }
      else if ((TemperaturaInterna + Histerese ) < TemperaturaExterna) {//fechar();
        ControleJanelaFechar();
      }
    }
  }//Fim do mantem na faixa
  //Mantem frio
  else if ( Janela == 3 ) { //mantem o mais frio possivel
    if ((TemperaturaInterna - Histerese) > TemperaturaExterna) { //se temperatura interna maior que externa, abre a janela //abrir();
      ControleJanelaAbrir();
    }
    else if ((TemperaturaInterna + Histerese ) < TemperaturaExterna) { //se temperatura externa maior que interna, fecha a janela //fechar();
      ControleJanelaFechar();
    }
  }
  //Mantem quente
  else if (Janela == 4) { //mantem o mais quente possivel
    if ((TemperaturaInterna + Histerese) < TemperaturaExterna) { //se temperatura interna menor que externa, abre a janela //abrir();
      ControleJanelaAbrir();
    }
    else if ((TemperaturaInterna - Histerese) > TemperaturaExterna) { //se temperatura externa menor que interna, fecha a janela //fechar();
      ControleJanelaFechar();
    }
  }
  if (xSemaphoreTake(holy2, 0)) {
    if (AberturaJanelaM != AberturaJanela) {
      if (Firebase.setInt(firebaseData1, path2 +  "/Abertura janela" , AberturaJanela)) {
        AberturaJanelaM = AberturaJanela;
      }
    }
    xSemaphoreGive(holy1);
  }
  if (!FlagTask_2) {
    vTaskResume(Task_2);//inicia a task responsavel pelo controle da janela
    FlagTask_2 = true;
  }
}
void ControleJanelaFechar() {
  if (Flag_Janela != 0) {
    xSemaphoreTake(holy3, 0);
    JanelaAbertura = 0;
    xSemaphoreGive(holy3);
    Flag_Janela = 0;
  }
}
void ControleJanelaAbrir() {
  if ( Chuva <= (SensibilidadeSensorDeChuva * 0.8)){
    if (Flag_Janela != 1) {
      xSemaphoreTake(holy3, 0);
      JanelaAbertura = 1;
      xSemaphoreGive(holy3);
      Flag_Janela = 1;
    }
  }
}
//Core 0
void JanelaPosicao() {                       //controle de posição da janela em manual
  if (xSemaphoreTake(holy3, 0)) {
    JanelaAberturaTask = JanelaAbertura;
    xSemaphoreGive(holy3);
  }
  if (JanelaAberturaTask == 1) {
    if (xSemaphoreTake(holy1, 0)) {
      PosicaoJanela = JanelaDeslizador;
      xSemaphoreGive(holy1);
    }
    if (ContJanela == PosicaoJanela) {
      //codigo parar
      digitalWrite(EnableJanela, HIGH); // LOW para ligar HIGH para desligar
      ledcWrite(1, 0);
      if (FlagAberturaJanela) {
        xSemaphoreTake(holy2, 0);
        AberturaJanela = ContJanela; //mapeia o valor lido  de 0% a 100%
        xSemaphoreGive(holy2);
        if (Firebase.setInt(firebaseData1, path2 +  "/Abertura janela" , AberturaJanela)) {
          FlagAberturaJanela = false;
        }
      }
      delayTask = 1000;
    }
    else if (ContJanela < PosicaoJanela) {                      //se contagem de abertura menor que deslizador
      delayTask = 0;
      AbrirJanela();
    }
    else if (ContJanela > PosicaoJanela) {                   //se contagem de abertura maior que deslizador
      delayTask = 0;
      FecharJanela();
    }
  }
  else if (JanelaAberturaTask == 0) {
    if (ContJanela == 0) {
      //codigo parar
      digitalWrite(EnableJanela, HIGH); // LOW para ligar HIGH para desligar
      ledcWrite(1, 0);
      if (FlagAberturaJanela) {
        xSemaphoreTake(holy2, 0);
        AberturaJanela = 0;
        xSemaphoreGive(holy2);
        if (Firebase.setInt(firebaseData1, path2 +  "/Abertura janela" , 0)) {
          FlagAberturaJanela = false;
        }
      }
      delayTask = 1000;
    }
    else if (ContJanela > 0) {                   //se contagem de abertura maior que deslizador
      delayTask = 0;
      FecharJanela();
    }
  }
  else {
    //codigo parar
    digitalWrite(EnableJanela, HIGH); // LOW para ligar HIGH para desligar
    ledcWrite(1, 0);
    delayTask = 1000;
  }
}
void AbrirJanela() {                        //executa sequancia de abertura da janela
  if (digitalRead(JanelaFechada) == 0) {
    ContJanela = 0 ;
    xSemaphoreTake(holy2, 0);
    AberturaJanela = 0;
    xSemaphoreGive(holy2);
  }
  if (ContJanela < AberturaTotal) {
    delayTask = 0;
    //codigo abrir
    ledcWrite(1, 1);
    digitalWrite(DirJanela, HIGH);  //direção
    digitalWrite(EnableJanela, LOW); // LOW para ligar HIGH para desligar
    if (FlagTimeStepJanela) {
      TimeStepJanela = millis();
      FlagTimeStepJanela = false;
    }
    if ((millis() - TimeStepJanela) >= PeriodoStepe) {
      ContJanela = ContJanela + 1;
      TimeStepJanela = millis();
    }

  } else {
    //codigo parar
    digitalWrite(EnableJanela, HIGH); // LOW para ligar HIGH para desligar
    ledcWrite(1, 0);
    delayTask = 1000;
  }
  xSemaphoreTake(holy2, 0);
  AberturaJanela = ContJanela; //mapeia o valor lido  de 0% a 100%
  xSemaphoreGive(holy2);
  FlagAberturaJanela = true;
}//AbrirJanela
void FecharJanela() {                       //execututa sequancia de fechamento da janela
  if (digitalRead(JanelaFechada) == 0) {
    ledcWrite(1, 0);
    ContJanela = 0 ;
    xSemaphoreTake(holy2, 0);
    AberturaJanela = 0;
    xSemaphoreGive(holy2);
  }
  if ( ContJanela > 0 ) {
    delayTask = 0;
    //codigo fechar
    ledcWrite(1, 1);
    digitalWrite(DirJanela, LOW);  //direção
    digitalWrite(EnableJanela, LOW); // LOW para ligar HIGH para desligar
    if (!FlagTimeStepJanela) {
      TimeStepJanela = millis();
      FlagTimeStepJanela = true;
    }
    if ((millis() - TimeStepJanela) >= PeriodoStepe) {
      ContJanela = ContJanela - 1;
      TimeStepJanela = millis();
    }
    if (ContJanela <= 0 ) {
      if (digitalRead(JanelaFechada) == 0) {
        ContJanela = 0 ;
      } else {
        ContJanela = 1;
      }
    }
  } else {
    //codigo parar
    digitalWrite(EnableJanela, HIGH); // LOW para ligar HIGH para desligar
    ledcWrite(1, 0);
    delayTask = 1000;
  }
  xSemaphoreTake(holy2, 0);
  AberturaJanela = ContJanela; //mapeia o valor lido  de 0% a 100%
  xSemaphoreGive(holy2);
  FlagAberturaJanela = true;

}//FecharJanela

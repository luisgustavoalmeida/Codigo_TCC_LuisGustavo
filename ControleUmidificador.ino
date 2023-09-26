void ControleUmidificador() {               //comtrola o umidificador em função da umidade e temporisado
  if ((Umidificador == 0) && (UmidificadorTemporisado == 0)) { //umidificador desligar
    //Serial.println("Manda desligar o umidificador");
    digitalWrite(saida7, HIGH); //desliga umidificador
    UmidificadorEstado = false;
  }
  else {
    if ((Umidificador == 1) && (UmidificadorTemporisado == 0)) { //umidificador ligado em manual
      //Serial.println("Manda ligar o umidificador");
      digitalWrite(saida7, LOW); //liga umidificador
      UmidificadorEstado = true;
    }
    else if ((Umidificador == 2) && (UmidificadorTemporisado == 0)) { //umidificador em automatico. funciona em função da umidade relativa do ambiente
      //Serial.println("Umidificador em automatico");
      if (UmidadeSensor <= UmidadeMinima)  {
        //Serial.println("Manda ligar o umidificador em automatico");
        digitalWrite(saida7, LOW); //liga umidificador
        UmidificadorEstado = true;
      }
      else if ( UmidadeSensor >= UmidadeMaxima) {
        //Serial.println("Manda desligar o umidificador em automatico");
        digitalWrite(saida7, HIGH); //desliga umidificador
        UmidificadorEstado = false;
      }
    }
    else if ((Umidificador == 0) && (UmidificadorTemporisado == 1)) { //funciona temporisado. liga a cada x tempo e fica ligado por y tempo
    //Serial.println("Umidificador em temporisao");
    //Serial.println((millis() - TimeLigaACada));
    if ((millis() - TimeLigaACada) > (UmidificadorTempoLigaACada * 60000)) {
        //Serial.println("Umidificador em temporisado&&&");
        if (!LigadoPorFlag) {
          LigadoPorFlag = true;
          TimeLigadoPor = millis();
          //Serial.println("####Manda ligar o umidificador em temporisado");
          digitalWrite(saida7, LOW); //liga umidificador
          UmidificadorEstado = true;
        }
        else if ((millis() - TimeLigadoPor) > (UmidificadorTempoLigadoPor * 60000)) {
          //Serial.println("****Manda desligar o umidificador em temporisado");
          TimeLigaACada = millis();
          LigadoPorFlag = false;
          digitalWrite(saida7, HIGH); //desliga umidificador
          UmidificadorEstado = false;
        }
      }
    }
    else if ((Umidificador == 2) && (UmidificadorTemporisado == 1)) { //automatico e temporisado
    if (UmidadeSensor <= UmidadeMinima)  {
        //Serial.println("Manda ligar o umidificador em automatico");
        digitalWrite(saida7, LOW); //liga umidificador
        UmidificadorEstado = true;
        TimeLigaACada = UmidificadorTempoLigaACada * (-60000);
        LigadoPorFlag = false;
      }
      else if ((millis() - TimeLigaACada) > (UmidificadorTempoLigaACada * 60000)) {
        //Serial.println("Umidificador em temporisado&&&");
        if (!LigadoPorFlag) {
          LigadoPorFlag = true;
          TimeLigadoPor = millis();
          //Serial.println("####Manda ligar o umidificador em temporisado");
          digitalWrite(saida7, LOW); //liga umidificador
          UmidificadorEstado = true;
        }
        else if ((millis() - TimeLigadoPor) > (UmidificadorTempoLigadoPor * 60000)) {
          //Serial.println("****Manda desligar o umidificador em temporisado");
          TimeLigaACada = millis();
          LigadoPorFlag = false;
          digitalWrite(saida7, HIGH); //desliga umidificador
          UmidificadorEstado = false;
        }
      }
    }
  }
  if (UmidificadorEstadoM != UmidificadorEstado) {
    if (UmidificadorEstado) {
      if (Firebase.setString(firebaseData1, path2 +  "/Umidificador estado" , "ligado")) {
        UmidificadorEstadoM = UmidificadorEstado;
      }
    } else {
      if (Firebase.setString(firebaseData1, path2 +  "/Umidificador estado" , "desligado")) {
        UmidificadorEstadoM = UmidificadorEstado;
      }
    }
  }
}

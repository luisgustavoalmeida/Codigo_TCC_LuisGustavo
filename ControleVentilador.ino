void ControleVentilador  () {                 //controla ventilador manualmente e automaticamente
  //bool VentiladorJaFoiLigado ;
  const int PWMmaximo = 280;                      // valor de PWm que o ventilador quase nao roda // 0 velocidade maxima //1024 desligado
  int VentiladorPWM ;
  if (Ventilador == 0) {                    // Ventilador desligado
    ledcWrite(2, 1024);
    VelocidadeVentilador = 0 ;
    VentiladorJaFoiLigado = false;
  }
  else if (Ventilador == 1) {               // ventilado manual
    VentiladorPWM = map(VentiladorDeslizador, 100, 0, 0, PWMmaximo); // ajusta velor do deslizador com o a faixa de PWM
    VelocidadeVentilador = map(VentiladorPWM, 0, PWMmaximo, 100, 1); // ajusta o valor do PWM para um valode ente 0% a 100% para indicar a velocidade no APP
    if (!VentiladorJaFoiLigado) {
      ledcWrite(2, 0);
      delay(3000);
    }
    ledcWrite(2, VentiladorPWM);
    VentiladorJaFoiLigado = true;
  }
  else if (Ventilador == 2) {               //ventilador em automatico ajusta velocidade dentro de uma faixa de temperatura
    if (TemperaturaInterna < (VentiladorTemperaturaMinima - Histerese)) { // desliga o ventilador // ajuste da Histerese -  Histerese = 0.20;
      ledcWrite(2, 1024);// desliga
      VelocidadeVentilador = 0 ;
      VentiladorJaFoiLigado = false;
    }
    else if ((TemperaturaInterna >= VentiladorTemperaturaMinima) && (TemperaturaInterna < VentiladorTemperaturaMaxima)) {
      VentiladorPWM = map(VentiladorDeslizador, 100, 0 , 0, PWMmaximo); // ajusta valor do deslizador com o a faixa de PWM para limitar a velocidade maxima
      VentiladorPWM = map((TemperaturaInterna * 1000),  (VentiladorTemperaturaMinima * 1000), (VentiladorTemperaturaMaxima * 1000) , PWMmaximo , VentiladorPWM);
      VelocidadeVentilador = map(VentiladorPWM, 0, PWMmaximo, 100, 1); // ajusta o valor do PWM para um valode ente 0% a 100% para indicar a velocidade no APP
      if (!VentiladorJaFoiLigado) {
        ledcWrite(2, 0);
        delay(3000);
      }
      ledcWrite(2, VentiladorPWM);
      VentiladorJaFoiLigado = true;
    }
    else if (TemperaturaInterna >= VentiladorTemperaturaMaxima) {
      VentiladorPWM = map(VentiladorDeslizador, 100, 0, 0, PWMmaximo); // ajusta velor do deslizador com o a faixa de PWM
      VelocidadeVentilador = map(VentiladorPWM, 0, PWMmaximo, 100, 1); // ajusta o valor do PWM para um valode ente 0% a 100% para indicar a velocidade no APP
      if (!VentiladorJaFoiLigado) {
        ledcWrite(2, 0);
        delay(3000);
      }
      ledcWrite(2, VentiladorPWM);
      VentiladorJaFoiLigado = true;
    }
    else if ((TemperaturaInterna >= (VentiladorTemperaturaMinima - Histerese)) && (TemperaturaInterna < VentiladorTemperaturaMinima) && (VentiladorJaFoiLigado)) {
      VelocidadeVentilador = 1 ;
      ledcWrite(2, PWMmaximo);
      //VentiladorJaFoiLigado = true;
    }
    else if ((TemperaturaInterna >= (VentiladorTemperaturaMinima - Histerese)) && (TemperaturaInterna < VentiladorTemperaturaMinima) && (!VentiladorJaFoiLigado)) {
      VelocidadeVentilador = 0 ;
      ledcWrite(2, 1024);
      VentiladorJaFoiLigado = false;
    }
  }
  if (VelocidadeVentiladorM != VelocidadeVentilador) {
    if (Firebase.setInt(firebaseData1, path2 +  "/Velocidade ventilador" , VelocidadeVentilador)) {
      VelocidadeVentiladorM = VelocidadeVentilador;
    }
  }
}

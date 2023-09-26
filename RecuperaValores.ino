void RecuperaValores() {                    //assim que termina de inicialisar o esp busca os valores de algumas fariaveis fincionando como uma memoria
  if (Firebase.getInt(firebaseData1, path2 +  "/Reinicializações")) {
    int ContReinicia = (firebaseData1 . intData ()) + 1;
    Firebase.setInt(firebaseData1, path2 +  "/Reinicializações" , ContReinicia);
  } else {
    if (Firebase.getString(firebaseData1, path2 +  "/Reinicializações")) {
      if ((firebaseData1 .stringData ()).equals("0")) {
        Firebase.setInt(firebaseData1, path2 +  "/Reinicializações" , 1);
      }
    }
  }
  // Firebase.setInt(firebaseData1, path2 +  "/Watchdog" , ContWatchdog);
  if (Firebase.getInt(firebaseData1, path2 +  "/Abertura janela" )) {
    ContJanela = firebaseData1 . intData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura externa")) {
    TemperaturaExternaUltimoValor = TemperaturaExterna = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura externa máxima")) {
    TemperaturaExternaMaxima = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura externa mínima")) {
    TemperaturaExternaMinima = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura interna")) {
    TemperaturaInternaUltimoValor = TemperaturaInterna = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura interna máxima")) {
    TemperaturaInternaMaxima = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Temperatura interna mínima")) {
    TemperaturaInternaMinima = firebaseData1 . floatData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Umidade")) {
     UmidadeSensor = firebaseData1 . intData ();
     UmidadeSensorM = UmidadeSensor;     
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Umidade máxima")) {
    UmidadeSensorMaxima = firebaseData1 . intData ();
  }
  if (Firebase.getFloat(firebaseData1, path2 +  "/Umidade mínima")) {
    UmidadeSensorMinima = firebaseData1 . intData ();
  }

/*  
   if (Firebase.getString(firebaseData1, path2 +  "/Sensor de presença" )) {
    if ((firebaseData1 . stringData ()).equals("Sim")) {
      StatusFeito = false;
      StatusBLE = true;
      StatusIP = true;
    } else {
      StatusFeito = true;
      StatusBLE = false;
      StatusIP = false;
    }
  }
  if (Iluminacao1Presenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Iluminação 1")) {
      if ((firebaseData1 .stringData ()).equals("ligar")) {
        Iluminacao1PresencaEstado = true;
      }
    }
  }
  if (Iluminacao2Presenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Iluminação 2")) {
      if ((firebaseData1 .stringData ()).equals("ligar")) {
        Iluminacao2PresencaEstado = true;
      }
    }
  }
  if (IluminacaoMesaPresenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Iluminação mesa")) {
      if ((firebaseData1 .stringData ()).equals("ligar")) {
        IluminacaoMesaPresencaEstado = true;
      }
    }
  }
  if (IluminacaoIndiretaPresenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Iluminação indireta")) {
      if ((firebaseData1 .stringData ()).equals("ligar")) {
        IluminacaoIndiretaPresencaEstado = true;
      }
    }
  }
  if (VentiladorPresenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Ventilador")) {
      if ((firebaseData1 .stringData ()).equals("ligar")) {
        VentiladorPresencaEstado = 1;
      }
      else if ((firebaseData1 .stringData ()).equals("automático")) {
        VentiladorPresencaEstado = 2;
      }
    }
  }
  if (JanelaPresenca) {
    if (Firebase.getString(firebaseData1, path3 +  "/Janela")) {
      if ((firebaseData1 .stringData ()).equals("abrir")) {
        JanelaPresencaEstado = 1;
      }
      else if ((firebaseData1 .stringData ()).equals("automático")) {
        JanelaPresencaEstado = 2;
      }
      else if ((firebaseData1 .stringData ()).equals("manter-frio")) {
        JanelaPresencaEstado = 3;
      }
      else if ((firebaseData1 .stringData ()).equals("manter-quente")) {
        JanelaPresencaEstado = 4;
      }
    }
  }
  */
  /*if(UmidificadorPresenca){
      if(Firebase.getString(firebaseData1, path3 +  "/Umidificador")){
        if ((firebaseData1 .stringData ()).equals("ligar")) {
          UmidificadorPresencaEstado = 1;
        }
        else if ((firebaseData1 .stringData ()).equals("automático")) {
          UmidificadorPresencaEstado = 2;
        }
      }
        if(Firebase.getString(firebaseData1, path3 +  "/Umidificador temporisado")){
        if ((firebaseData1 .stringData ()).equals("ligar")) {
          UmidificadorTemporisadoPresencaEstado = true;
        }
        }
    }
  */
}

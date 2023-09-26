void SensorTemperatura () {                 //verifica a temperatura interna e externa
  if ( (millis() - TimeTemperaturaRequerida) > 8000) {
    float SensorTemperaturaExterno = sensors.getTempC(termometro2);    // sensor externo
    float SensorTemperaturaInterno = sensors.getTempC(termometro1);    //sensor interno
    //temperatura externas
    if (SensorTemperaturaExterno != -127.00 && SensorTemperaturaExterno != 85.00 && SensorTemperaturaExterno > TemperaturaExternaUltimoValor - 1.5 && SensorTemperaturaExterno < TemperaturaExternaUltimoValor + 1.5) { //desconsidera valores que indicam erro
      if (TemperaturaExterna != SensorTemperaturaExterno) {
        Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa" , SensorTemperaturaExterno);
        TemperaturaExterna = SensorTemperaturaExterno;
        if (TemperaturaExternaMaxima < SensorTemperaturaExterno) {
          if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa máxima" , SensorTemperaturaExterno)) {
            TemperaturaExternaMaxima = SensorTemperaturaExterno;
            Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura externa máxima hora" );
          }
        }
        else if (TemperaturaExternaMinima > SensorTemperaturaExterno) {
          if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa mínima" , SensorTemperaturaExterno)) {
            TemperaturaExternaMinima = SensorTemperaturaExterno;
            Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura externa mínima hora" );
          }
        }
        TemperaturaExternaUltimoValor  = SensorTemperaturaExterno;
      }
      if (FlagErroExterno) {
        if (Firebase.setString(firebaseData1, path2 +  "/Temperatura externa sensor" , "ok" )) {
          FlagErroExterno = false;
        }
      }
    } else {
      TemperaturaExternaUltimoValor  = SensorTemperaturaExterno;
      //Serial.println("Falha na leitura do sensor de temperatura Externo!");
      if (!FlagErroExterno) {
        if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa sensor" , SensorTemperaturaExterno)) {
          FlagErroExterno = true;
        }
      }
    }//temperaturas externas

    //temperatura internas
    if (SensorTemperaturaInterno != -127.0 && SensorTemperaturaInterno != 85.00 && SensorTemperaturaInterno > TemperaturaInternaUltimoValor - 1.5 && SensorTemperaturaInterno < TemperaturaInternaUltimoValor + 1.5) { //desconsidera valores que indicam erro
      if (TemperaturaInterna != SensorTemperaturaInterno) {
        Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna" , SensorTemperaturaInterno);
        TemperaturaInterna = SensorTemperaturaInterno;
        if (TemperaturaInternaMaxima < SensorTemperaturaInterno) {
          if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna máxima" , SensorTemperaturaInterno)) {
            TemperaturaInternaMaxima = SensorTemperaturaInterno;
            Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura interna máxima hora" );
          }
        }
        else if (TemperaturaInternaMinima > SensorTemperaturaInterno) {
          if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna mínima" , SensorTemperaturaInterno)) {
            TemperaturaInternaMinima = SensorTemperaturaInterno;
            Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura interna mínima hora" );
          }
        }
        TemperaturaInternaUltimoValor = SensorTemperaturaInterno;
      }
      if (FlagErroInterno) {
        if (Firebase.setString(firebaseData1, path2 +  "/Temperatura interna sensor" , "ok" )) {
          FlagErroInterno = false;
        }
      }
    } else {
      TemperaturaInternaUltimoValor = SensorTemperaturaInterno;
      if (!FlagErroInterno) {
        if (Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna sensor" , SensorTemperaturaInterno )) {
          FlagErroInterno = true;
        }
      }
    }//temperaturas internas
    sensors.requestTemperatures();            //requisita os sensores de temperatura e aguarda x segundos para pegar o valor
    TimeTemperaturaRequerida = millis();
  }
}

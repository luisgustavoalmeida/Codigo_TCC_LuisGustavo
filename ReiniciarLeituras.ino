void Reenicialeituras  () {                   //apaga os valores de maximos e minimos das leituras
  if (Firebase.setString(firebaseData1, path1 +  "/Z Reinicia leituras" , "0" )) {
    TemperaturaExternaMaxima = TemperaturaExterna;
    TemperaturaExternaMinima = TemperaturaExterna;
    TemperaturaInternaMaxima = TemperaturaInterna;
    TemperaturaInternaMinima = TemperaturaInterna;
    UmidadeSensorMaxima = UmidadeSensorM;
    UmidadeSensorMinima = UmidadeSensorM;
    Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa máxima" , TemperaturaExternaMaxima);
    Firebase.setFloat(firebaseData1, path2 +  "/Temperatura externa mínima" , TemperaturaExternaMinima);
    Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna máxima" , TemperaturaInternaMaxima);
    Firebase.setFloat(firebaseData1, path2 +  "/Temperatura interna mínima" , TemperaturaInternaMinima);
    Firebase.setFloat(firebaseData1, path2 +  "/Umidade máxima" , UmidadeSensorMaxima);
    Firebase.setFloat(firebaseData1, path2 +  "/Umidade mínima" , UmidadeSensorMinima);
    Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura externa máxima hora" );
    Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura externa mínima hora" );
    Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura interna máxima hora" );
    Firebase. setTimestamp (firebaseData1, path2 + "/Temperatura interna mínima hora" );
    Firebase. setTimestamp (firebaseData1, path2 + "/Umidade máxima hora" );
    Firebase. setTimestamp (firebaseData1, path2 + "/Umidade mínima hora" );
    ReiniciaLeitura = false;
  }
}

void SensorUmidade () {                     //lê valores de umidade do ar
  UmidadeSensor = dht.readHumidity();
  //Serial.println(dht.readTemperature());
  if (isnan(UmidadeSensor)) {
    //Serial.println("Falha na leitura do sensor DHT!");
    //Firebase.setString(firebaseData1, path2 +  "/Umidade sensor" , "erro" );
    return;
  } else  if (1 <= UmidadeSensor <= 99) {
    if (UmidadeSensorM != UmidadeSensor) {
      if (Firebase.setFloat(firebaseData1, path2 +  "/Umidade" , UmidadeSensor)) {
        UmidadeSensorM = UmidadeSensor;
      }
      if (UmidadeSensorMinima > UmidadeSensor) {
        if (Firebase.setFloat(firebaseData1, path2 +  "/Umidade mínima" , UmidadeSensor)) {
          UmidadeSensorMinima = UmidadeSensor;
          Firebase. setTimestamp (firebaseData1, path2 + "/Umidade mínima hora" );
        }
      }
      else if (UmidadeSensorMaxima < UmidadeSensor) {
        if (Firebase.setFloat(firebaseData1, path2 +  "/Umidade máxima" , UmidadeSensor)) {
          UmidadeSensorMaxima = UmidadeSensor;
          Firebase. setTimestamp (firebaseData1, path2 + "/Umidade máxima hora" );
        }
      }
    }
    //Firebase.setString(firebaseData1, path2 +  "/Umidade sensor" , "ok" );
  }
}

void connect() {                            //quando se perde a conexão com o Faribase tenta reconectar ao Wifi, se continuar falhar reinicia o esp
  //Serial.println("Função conecta");
  int Count_Conect = 0;
  WiFi.begin(ssid, password);
  //Serial.print("Connectando ao Wi-Fi apos falha");
  while (WiFi.status() != WL_CONNECTED && Count_Conect <= 20 ) {
    delay(300);
    //Serial.print(".");
    Count_Conect = Count_Conect + 1;
  }
  if (WiFi.status() == WL_CONNECTED) {
    //inicia o Firebase
    //Configure a credencial do Firebase em setup ()
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    //Opcional, defina a reconexão do AP em setup ()
    Firebase.reconnectWiFi(true);
    //inicia a função do Callback que recebe os dados do Faribase
    Firebase.beginStream(firebaseData2, path1 );
    Firebase.setStreamCallback(firebaseData2, streamCallback, streamTimeoutCallback);
  }
}

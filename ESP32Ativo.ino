void ESP32ativo () {                         //testa periodicamente a conexão com o Faribase, se tem falha manda reiniciar o esp
  if (ContESP32ativo) {
    Firebase.setString (firebaseData1, path1 +  "/Z ESP32 ativo" , "o" );
    ContESP32ativo  = false;
  } else {
    Firebase.setString (firebaseData1, path1 +  "/Z ESP32 ativo" , "O" );
    ContESP32ativo  = true;
  }
  if ((millis() - TimeComunicacao ) > 300000) { // reinicia o esp se nao comunica por x minutos
    //Serial.println("Reinicia por tempo morto de comunicação");
    delay(100);
    //ets_printf("(***falha de comunicação***)\n"); //imprime no log de erros
    esp_restart(); //reinicia o chip
  }
}

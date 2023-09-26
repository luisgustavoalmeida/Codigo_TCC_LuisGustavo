void printResult (StreamData &data) {        //função chamada quando se inicia uma nova conexao, recebe o estatus de todos os dispositivos
  FirebaseJson *json = data.jsonObjectPtr();
  //Serial.println("Printe dados JSON :");
  String jsonStr;
  json->toString(jsonStr, true);
  size_t len = json->iteratorBegin();
  int type = 0;
  for (size_t i = 0; i < len; i++) {
    json->iteratorGet(i, type, RXDispositivo, RXStatus);
    //Serial.print(i);
    //Serial.print(", ");
    //Serial.print("Type: ");
    //Serial.print(type == JSON_OBJECT ? "object" : "array");
    //if (type == JSON_OBJECT) {
      //Serial.print(", Dispositivo: ");
      //Serial.print(RXDispositivo );
      ///////////////////////////////////ao iniciar busca todos os valores e atualiza as variveis
    //}
    //Serial.print(", Status: ");
    //Serial.println(RXStatus);
    ///////////////////////////////////ao iniciar busca todos os valores e atualiza as variveis
    AtivaComandos();                                 //////////////////////////////////chama a função atualizar que atualiza as variaveis e os estado das saidas do esp
  }
  json->iteratorEnd();
}

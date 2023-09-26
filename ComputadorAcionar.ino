void ComputadorAcionar  () {                  //liga o computador e manda o status de ligado ou desligado
  if (digitalRead(SensorComputador) == HIGH){ 
    if (Computador == 0 ) {
      Computador = 2;
    digitalWrite(saida6, HIGH);
    delay (800);
    digitalWrite(saida6, LOW);
    }
    if (Computador != 3 ) {
      if (Firebase.setString(firebaseData1, path1 +  "/Z Computador" , "ligado" )) {
        Computador = 3;
      }
    }
  }
  else if (digitalRead(SensorComputador) == LOW){
     if (Computador == 1) {
      Computador = 2;
    digitalWrite(saida6, HIGH);
    delay (800);
    digitalWrite(saida6, LOW);
    }
    if (Computador != 4 ) {  
    if (Firebase.setString(firebaseData1, path1 +  "/Z Computador" , "desligado" )) {
      Computador = 4;
    }
    }
  }
}

void ControleAquecedor () {                 //controla Aquecedor manualmente e automaticamente
  if (Aquecedor == 0) {                    // Aquecedor desligado
    //desliga
    digitalWrite(saida8, LOW);
    AquecedorEstado = false;
  }
  else if (Aquecedor == 1) {               // Aquecedor manual
    //liga
    digitalWrite(saida8, HIGH);
    AquecedorEstado = true;
  }
  else if (Aquecedor == 2) {               //Aquecedor em automatico
    if (TemperaturaInterna <= AquecedorTemperaturaMinima) { // desliga o Aquecedor // ajuste da Histerese -  Histerese = 0.20;
      //liga
      digitalWrite(saida8, HIGH);
      AquecedorEstado = true;
    }
    else if (TemperaturaInterna >= AquecedorTemperaturaMaxima) {
      //desliga
      digitalWrite(saida8, LOW);
      AquecedorEstado = false;
    }
  }
  if (AquecedorEstadoM != AquecedorEstado) {
    if(AquecedorEstado){
    if (Firebase.setString(firebaseData1, path2 +  "/Aquecedor estado" , "ligado")) {
      AquecedorEstadoM = AquecedorEstado;
    }
    }
    else{
    if (Firebase.setString(firebaseData1, path2 +  "/Aquecedor estado" , "desligado")) {
      AquecedorEstadoM = AquecedorEstado;  
    }
    }
  }
}

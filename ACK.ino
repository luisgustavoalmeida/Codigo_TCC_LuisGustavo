void ACK() {                               //envia para o Firebase as confirmaçoes de recebimentos para ACK em nive de camada de aplicação
  if (!FlagACKcomuta) {
    if (Firebase.setInt(firebaseData1, path4 +  "/ Comanedo recebido" , 0 )) {
      FlagACKcomuta = true;
      FlagACK = false;
    }
  } else {
    if (Firebase.setInt(firebaseData1, path4 +  "/ Comanedo recebido" , 1 )) {
      FlagACKcomuta = false;
      FlagACK = false;
    }
  }
}

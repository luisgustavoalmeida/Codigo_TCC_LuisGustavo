void SensorChuva () {                        //verifica se esta chovendo para fechar a janela
  Chuva = analogRead(EntradaChuva); //le valor do pino do sesor de chuva
  Chuva = map(Chuva, 0, 4095, 100, 0); //mapeia o valor lido no ldr de 0% a 100%
  Chuva = MediaMovel(Chuva,200); // manda para a função de media movel o valor a ser filtrado e o numero de interações
  if (ChuvaM != Chuva ) {
    if (Firebase.setInt(firebaseData1, path2 +  "/Chuva" , Chuva)) {
      ChuvaM = Chuva;
    }
  }
}

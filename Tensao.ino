void Tensao() {                             //lê os valores de tensão 5V que alimenta o ESP
  float Tensao = analogRead(EntradaTensao);
  Tensao = ((Tensao * 6.6) / 4094) + 0.19;
  if ((Tensao < (TensaoM - 0.05)) || (Tensao > (TensaoM + 0.05))) {
    if (Firebase.setFloat(firebaseData1, path2 +  "/Tensão alimentação" , Tensao)) {
      TensaoM = Tensao;
    }
  }
}

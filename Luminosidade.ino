void Luminosidade () {                       //lê a luminosidade do ambiente
  int ValorLDR = analogRead(EntradaLDR); //le valor do LDR
  ValorLDR =  map(ValorLDR, 0, 4094, 0, 100); //mapeia o valor lido no ldr de 0% a 100%
  if ( (ValorLDR < (ValorLDRM - 2)) || (ValorLDR > (ValorLDRM + 2)) ) {
    Firebase.setInt(firebaseData1, path2 +  "/Luminosidade" , ValorLDR);
    ValorLDRM = ValorLDR;
  }
}

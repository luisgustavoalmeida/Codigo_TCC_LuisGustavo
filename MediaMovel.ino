long MediaMovel(int valor, int n) {
  //desloca os elementos do vetor de média móvel
  for (int i = n - 1; i > 0; i--) numbers[i] = numbers[i - 1];

  numbers[0] = valor; //posição inicial do vetor recebe a leitura original

  long acc = 0;          //acumulador para somar os pontos da média móvel

  for (int i = 0; i < n; i++) acc += numbers[i]; //faz a somatória do número de pontos


  return acc / n; //retorna a média móvel


}

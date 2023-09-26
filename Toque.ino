void Toque1() {                              //sensor de toque da parede função que foi atribuida para o evento do touch.
  //Serial.println(touchRead(12));//Mostra o valor do touch no monitor.
  //Serial.println("          1");
  if ((millis() - TimeToque2) > 1000) {
    if ((millis() - TimeToque1) > 3000) { //Verifica se o ultimo toque faz mais de 150mS
      TimeToque1 = millis();//Salva o ultimo tempo em que foi tocado.
      if ( (!digitalRead(saida2)) || (!digitalRead(saida3)) || (!digitalRead(saida4)) ) {
        digitalWrite(saida2, HIGH);//desliga iluminação 1
        digitalWrite(saida3, HIGH);//desliga iluminação 2
        digitalWrite(saida4, HIGH);//desliga iluminação da mesa
      }
      else { // se saida ligada manda desligar     if ( (digitalRead(saida2)) && ( digitalRead(saida3)) )
        digitalWrite(saida2, LOW); //liga iluminação 1
        digitalWrite(saida3, LOW);//liga iluminação 2
      }
    }
    else if ( ((millis() - TimeToque1) < 1500) && ( (millis() - TimeToque1) > 750)   ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, HIGH);//desliga iluminação 1
      digitalWrite(saida3, LOW);//desliga iluminação 2
    }
    else if (((millis() - TimeToque1) < 2250) && ((millis() - TimeToque1) > 1500) ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, LOW); //liga iluminação 1
      digitalWrite(saida3, HIGH);//desliga iluminação 2
    }
    else if (((millis() - TimeToque1) < 3000) && ((millis() - TimeToque1) > 2250) ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, HIGH); //liga iluminação 1
      digitalWrite(saida3, HIGH);//desliga iluminação 2
    }
    FlagLerSaidas = true;
  }
}//void Toque função que foi atribuida para o evento do touch.
void Toque2() {                             //sensor de toque da mesa
  //Serial.println(touchRead(4));//Mostra o valor do touch no monitor.
  //Serial.println("                 2");
  if ((millis() - TimeToque1) > 1000) {
    if ((millis() - TimeToque2) > 3750) { //Verifica se o ultimo toque faz mais de 150mS
      TimeToque2 = millis();//Salva o ultimo tempo em que foi tocado.
      if (!digitalRead(saida4)) { // se saida ligada manda desligar
        digitalWrite(saida4, HIGH);//desliga iluminação da mesa
      } else {
        digitalWrite(saida4, LOW);//liga iluminação da mesa
      }
    }
    else if ( ((millis() - TimeToque2) < 1500) && ( (millis() - TimeToque2) > 750)   ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, LOW); //liga iluminação 1
      digitalWrite(saida3, LOW);//liga iluminação 2
    }
    else if (((millis() - TimeToque2) < 2250) && ((millis() - TimeToque2) > 1500) ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, HIGH);//desliga iluminação 1
      digitalWrite(saida3, LOW);//liga iluminação 2
    }
    else if (((millis() - TimeToque2) < 3000) && ((millis() - TimeToque2) > 2250) ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, LOW); //liga iluminação 1
      digitalWrite(saida3, HIGH);//desliga iluminação 2
    }
    else if (((millis() - TimeToque2) < 3750) && ((millis() - TimeToque2) > 3000) ) { //Verifica se o ultimo toque faz mais de 150mS
      digitalWrite(saida2, HIGH); //desliga iluminação 1
      digitalWrite(saida3, HIGH);//desliga iluminação 2
    }
    FlagLerSaidas = true;
  }
}

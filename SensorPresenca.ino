/*
void RecebeSerial2 () {                      //se sinal BLE encontrado pelo outro esp manda pela serial
  //  Se uma nova mensagem foi recebida
  if (SerialESP32.available() > 0) { // Efetua a leitura da mensagem vinda do SerialESP32
    String msg = SerialESP32.readStringUntil('\n');
    //Serial.println(msg);
    int MSG = msg.toInt();
    if (MSG == 0 ) {
      if (StatusBLE == true) {
        StatusBLE = false;
        Presente();
        return;
      }
      //Serial.println("status Ausente");
      //return;
    }
    else if (MSG == 1 ) {
      if (StatusBLE == false) {
        StatusBLE = true;
        Presente();
        return;
      }
      //Serial.println("status Presente");
      //return;
    } else if (MSG < 0 ) {
      if (ValorRSSI_BLE != MSG) {
        if (Firebase.setFloat(firebaseData1, path2 +  "/Sinal bluetooth" , ValorRSSI_BLE)) {
          ValorRSSI_BLE = MSG;
        }
      }
      return;
    }
  } else {
    //Serial.println("sem recebrer");
    return;
  }
  return;
} 
void IPencontrado() {                       //verifica se o IP do celular esta na mesma rede, se encontrado muda o estatus de presente
  bool success = Ping.ping("192.168.31.111", 1);                                 //tenta pingar o endenreço IP
  if (success) {                                                               // imprime se endereço ip esta presente ou nao
    TimeIP = millis();
    //Serial.println("******Ping ok********");
    if (!StatusIP) {
      StatusIP = true;
      Presente();
      M_IP = 0;

    }
    if (M_IP == 0) {
      if (Firebase.setString(firebaseData1, path2 +  "/IP encontrado" , "Sim" )) {
        M_IP = 1;
      }
    }
  } else {
    if (((millis() - TimeIP) > 300000) && (StatusIP)) {  // tem que falhar por 24 minutos = 1440000 millis
      StatusIP = false;
      Presente();
      M_IP = 1;
    }
    //Serial.println("Ping falha!");
    if (M_IP == 1) {
      Firebase.setString(firebaseData1, path2 +  "/IP encontrado" , "Não" );
      M_IP = 0;
    }
  }
}

void SairDaArea() {                         //quado fora de casa desliga os equipamentos
  if (Iluminacao1Presenca) {
    if (digitalRead(saida2)) {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação 1" , "desligar" ); // guarda o estado para voltar quando presente
      Iluminacao1PresencaEstado = false;
    } else {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação 1" , "ligar" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Iluminação 1" , "desligar" );
      Iluminacao1PresencaEstado = true;
    }
  }
  if (Iluminacao2Presenca) {
    if (digitalRead(saida3)) {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação 2" , "desligar" );// guarda o estado para voltar quando presente
      Iluminacao2PresencaEstado = false;
    } else {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação 2" , "ligar" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Iluminação 2" , "desligar" );
      Iluminacao2PresencaEstado = true;
    }
  }
  if (IluminacaoMesaPresenca) {
    if (digitalRead(saida4)) {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação mesa" , "desligar" );// guarda o estado para voltar quando presente
      IluminacaoMesaPresencaEstado = false;
    } else {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação mesa" , "ligar" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Iluminação mesa" , "desligar" );
      IluminacaoMesaPresencaEstado = true;
    }
  }
  if (IluminacaoIndiretaPresenca) {
    if (digitalRead(saida5)) {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação indireta" , "ligar" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Iluminação indireta" , "desligar" );
      IluminacaoIndiretaPresencaEstado = true;

    } else {
      Firebase.setString(firebaseData1, path3 +  "/Iluminação indireta" , "desligar" );// guarda o estado para voltar quando presente
      IluminacaoIndiretaPresencaEstado = false;
    }
  }
  if (VentiladorPresenca) {
    if (Ventilador == 0) {
      Firebase.setString(firebaseData1, path3 +  "/Ventilador" , "desligar" );// guarda o estado para voltar quando presente
      VentiladorPresencaEstado = 0;
    }
    else if (Ventilador == 1) {
      Firebase.setString(firebaseData1, path3 +  "/Ventilador" , "ligar" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "desligar" );
      VentiladorPresencaEstado = 1;
    }
    else if (Ventilador == 2) {
      Firebase.setString(firebaseData1, path3 +  "/Ventilador" , "automático" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "desligar" );
      VentiladorPresencaEstado = 2;
    }
  }
  if (JanelaPresenca) {
    if (Janela == 0) {
      Firebase.setString(firebaseData1, path3 +  "/Janela" , "fechar" );// guarda o estado para voltar quando presente
      JanelaPresencaEstado = 0;
    }
    else if (Janela == 1) {
      Firebase.setString(firebaseData1, path3 +  "/Janela" , "abrir" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "fechar" );
      JanelaPresencaEstado = 1;
    }
    else if (Janela == 2) {
      Firebase.setString(firebaseData1, path3 +  "/Janela" , "automático" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "fechar" );
      JanelaPresencaEstado = 2;
    }
    else if (Janela == 3) {
      Firebase.setString(firebaseData1, path3 +  "/Janela" , "manter-frio" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "fechar" );
      JanelaPresencaEstado = 3;
    }
    else if (Janela == 4) {
      Firebase.setString(firebaseData1, path3 +  "/Janela" , "manter-quente" );// guarda o estado para voltar quando presente
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "fechar" );
      JanelaPresencaEstado = 4;
    }
  }
 // /    if (UmidificadorPresenca) {
//        if (Umidificador == 0) {
//          Firebase.setString(firebaseData1, path3 +  "/Umidificador" , "desligar" );// guarda o estado para voltar quando presente
//          UmidificadorPresencaEstado = 0;
//        }
//        else if (Umidificador == 1) {
//          Firebase.setString(firebaseData1, path3 +  "/Umidificador" , "ligar" );// guarda o estado para voltar quando presente
//          Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "desligar" );
//          UmidificadorPresencaEstado = 1;
 //       }
//        else if (Umidificador == 2) {
//          Firebase.setString(firebaseData1, path3 +  "/Umidificador" , "automático" );// guarda o estado para voltar quando presente
//          Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "desligar" );
//          UmidificadorPresencaEstado = 2;
//        }
//        else if (UmidificadorTemporisado == 0) {
//          Firebase.setString(firebaseData1, path3 +  "/Umidificador temporisado" , "desligar" );// guarda o estado para voltar quando presente
//          UmidificadorTemporisadoPresencaEstado = false;
//        }
//        else if (UmidificadorTemporisado == 1) {
//          Firebase.setString(firebaseData1, path3 +  "/Umidificador temporisado" , "ligar" );// guarda o estado para voltar quando presente
//          Firebase.setString(firebaseData1, path1 +  "/Umidificador temporisado" , "desligar" );
//          UmidificadorTemporisadoPresencaEstado = true;
//        }
//      }
}

void EntrarNaArea() {                       //quando se retorna para casa liga os equipamentos com o estatus que estavam antes de sair
  if (Iluminacao1Presenca) {
    if (Iluminacao1PresencaEstado) {
      digitalWrite(saida2, LOW);        //19 iluminação 1 quarto
      Firebase.setString(firebaseData1, path1 +  "/Iluminação 1" , "ligar" );
    }
  }
  if (Iluminacao2Presenca) {
    if (Iluminacao2PresencaEstado) {
      digitalWrite(saida3, LOW);      //17 iluminação 2 quarto
      Firebase.setString(firebaseData1, path1 +  "/Iluminação 2" , "ligar" );
    }
  }
  if (IluminacaoMesaPresenca) {
    if (IluminacaoMesaPresencaEstado) {
      digitalWrite(saida4, LOW);      //5 iluminação mesa
      Firebase.setString(firebaseData1, path1 +  "/Iluminação mesa" , "ligar" );
    }
  }
  if (IluminacaoIndiretaPresenca) {
    if (IluminacaoIndiretaPresencaEstado) {
      digitalWrite(saida5, HIGH);    //18 iluminação indireta
      Firebase.setString(firebaseData1, path1 +  "/Iluminação indireta" , "ligar" );
    }
  }
  if (VentiladorPresenca) {
    if (VentiladorPresencaEstado == 1) {
      Ventilador = 1;
      ControleVentilador();
      Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "ligar" );
    }
    else if (VentiladorPresencaEstado == 2) {
      Ventilador = 2;
      ControleVentilador();
      Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "automático" );
    }
  }
  if (JanelaPresenca) {
    if (JanelaPresencaEstado == 1) {
      Janela = 1;
      ControleJanela();
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "abrir" );
    }
    else if (JanelaPresencaEstado == 2) {
      Janela = 2;
      ControleJanela();
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "automático" );
    }
    else if (JanelaPresencaEstado == 3) {
      Janela = 3;
      ControleJanela();
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "manter-frio" );
    }
    else if (JanelaPresencaEstado == 4) {
      Janela = 4;
      ControleJanela();
      Firebase.setString(firebaseData1, path1 +  "/Janela" , "manter-quente" );
    }
  }
  //  if (UmidificadorPresenca) {
//      if (UmidificadorPresencaEstado == 1) {
//        Umidificador = 1;
//        Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "ligar" );
//      }
//      else if (UmidificadorPresencaEstado == 2) {
//        Umidificador = 2;
//        Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "automático" );
//      }
//      Firebase.getString(firebaseData1, path3 +  "/Umidificador temporisado");
//      if (UmidificadorTemporisadoPresencaEstado) {
//        UmidificadorTemporisado = 1;
//        Firebase.setString(firebaseData1, path1 +  "/Umidificador temporisado" , "ligar" );
//      }
//      ControleUmidificador();
//    }
}
void Presente() {                           //se entrou ou saiu da area chama a função presente
  if ( (millis() - TimeIniciouAgora) > 30000) {
    if ((StatusBLE || StatusIP) && (StatusFeito)) {
      EntrarNaArea();
      if (Firebase.setString(firebaseData1, path2 +  "/Sensor de presença" , "Sim")) {
        StatusFeito = false;
      }
    }
    else if ((!StatusBLE) && (!StatusIP) && (StatusFeito)) {
      SairDaArea();
      if (Firebase.setString(firebaseData1, path2 +  "/Sensor de presença" , "Não")) {
        StatusFeito = true;
      }
    }
  }
}

*/

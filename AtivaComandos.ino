void AtivaComandos() {                        //recebe comandos do Faribase e atualisa variavis e saidas
  RXDispositivo.replace("/", "");                         //remove lixo
  RXStatus.replace("\\", "");
  RXStatus.replace("\"", "");

  if (RXDispositivo.equals("Histerese")) {
    Histerese = RXStatus.toFloat();     //converte um string para uma float
    //Serial.println(Histerese);
  }
  /*  else if (RXDispositivo.equals("Exaustor")) {
      if (RXStatus.equals("ligar")) {
        Exaustor = 1;
        }
      else if (RXStatus.equals("desligar")) {
        Exaustor = 0;
      }
      else if (RXStatus.equals("automático")) {
        Exaustor = 2;
      }
      else if (RXStatus.equals("manter-frio")) {
        Exaustor = 3;
      }
      else if (RXStatus.equals("manter-quente")) {
        Exaustor = 3;
      }
    }
    else if (RXDispositivo.equals("Exaustor deslizador")) {
      ExaustorDeslizador = RXStatus.toInt();     //converte um string para uma int
    }
    else if (RXDispositivo.equals("Exaustor temperatura máxima")) {
      ExaustorTemperaturaMaxima = RXStatus.toFloat();
    }
    else if (RXDispositivo.equals("Exaustor temperatura mínima")) {
      ExaustorTemperaturaMinima = RXStatus.toFloat();
    }*/
  else if (RXDispositivo.equals("Iluminação 1")) {
    if (RXStatus.equals("ligar")) {
      digitalWrite(saida2, LOW);  //19 iluminação 1 quarto
    }
    else {
      digitalWrite(saida2, HIGH);  //19 iluminação 1 quarto
    }
  }
  else if (RXDispositivo.equals("Iluminação 2")) {
    if (RXStatus.equals("ligar")) {
      digitalWrite(saida3, LOW);   //17 iluminação 2 quarto
    }
    else {
      digitalWrite(saida3, HIGH);   //17 iluminação 2 quarto
    }
  }
  else if (RXDispositivo.equals("Iluminação mesa")) {
    if (RXStatus.equals("ligar")) {
      digitalWrite(saida4, LOW);  //5 iluminação mesa
    }
    else {
      digitalWrite(saida4, HIGH);  //5 iluminação mesa
    }
  }
  else if (RXDispositivo.equals("Iluminação indireta")) {
    if (RXStatus.equals("ligar")) {
      digitalWrite(saida5, HIGH);    //18 iluminação indireta
    }
    else {
      digitalWrite(saida5, LOW);    //18 iluminação indireta
    }
  }
  else if (RXDispositivo.equals("Janela")) {
    if (RXStatus.equals("abrir")) {
      Janela = 1;
    }
    else if (RXStatus.equals("fechar")) {
      Janela = 0;
    }
    else if (RXStatus.equals("automático")) {
      Janela = 2;
    }
    else if (RXStatus.equals("manter-frio")) {
      Janela = 3;
    }
    else if (RXStatus.equals("manter-quente")) {
      Janela = 4;
    }
    if (Iniciando) {// nao roda quando se esta iniciando o esp
      Flag_Janela = 3;
      ControleJanela();
    }
  }
  else if (RXDispositivo.equals("Janela deslizador")) {
    xSemaphoreTake(holy1, 0);
    JanelaDeslizador = RXStatus.toInt();     //converte um string para uma int
    xSemaphoreGive(holy1);
  }
  else if (RXDispositivo.equals("Janela temperatura máxima")) {
    JanelaTemperaturaMaxima = RXStatus.toFloat();
  }
  else if (RXDispositivo.equals("Janela temperatura mínima")) {
    JanelaTemperaturaMinima = RXStatus.toFloat();
  }
  else if (RXDispositivo.equals("Janela velocidade")) {
    FrequanciaStepe = RXStatus.toInt();
    PeriodoStepe = 1090000 / FrequanciaStepe;  // Valor de numero de pusos para se mover 1% da janela vezes 1000(para mudar para segundos
    ledcAttachPin(StepJanela, 1);             //Atribuimos (pino, canal de 0 a 15) .
    ledcSetup(1, FrequanciaStepe, 1);         //Atribuimos (canal, frequencia, resolução 2^x)
    ledcWrite(1, 1);                          //Atribuimos (canal, valor da resolução desejada)
  }
  else if (RXDispositivo.equals("Sensibilidade chuva")) {
    SensibilidadeSensorDeChuva = RXStatus.toInt();
  }
  else if (RXDispositivo.equals("Umidade máxima")) {
    UmidadeMaxima = RXStatus.toFloat();
    //Serial.println(UmidadeMaxima);
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Umidade mínima")) {
    UmidadeMinima = RXStatus.toFloat();
    //Serial.println(UmidadeMinima);
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Umidificador")) {
    if (RXStatus.equals("ligar")) {
      Umidificador = 1;
    }
    else if (RXStatus.equals("desligar")) {
      Umidificador = 0;
    }
    else if (RXStatus.equals("automático")) {
      Umidificador = 2;
    }
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Umidificador tempo liga a cada")) {
    UmidificadorTempoLigaACada = RXStatus.toFloat();
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Umidificador tempo ligado por")) {
    UmidificadorTempoLigadoPor = RXStatus.toFloat();
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Umidificador temporisado")) {
    if (RXStatus.equals("ligar")) {
      UmidificadorTemporisado = 1;
    }
    else {
      UmidificadorTemporisado = 0;
    }
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleUmidificador();
    }
  }
  else if (RXDispositivo.equals("Ventilador")) {
    if (RXStatus.equals("ligar")) {
      Ventilador = 1;
    }
    else if (RXStatus.equals("desligar")) {
      Ventilador = 0;
    }
    else if (RXStatus.equals("automático")) {
      Ventilador = 2;
    }
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleVentilador();
    }
  }
  else if (RXDispositivo.equals("Ventilador deslizador")) {
    VentiladorDeslizador = RXStatus.toInt();     //converte um string para uma int
  }
  else if (RXDispositivo.equals("Ventilador temperatura máxima")) {
    VentiladorTemperaturaMaxima = RXStatus.toFloat();
  }
  else if (RXDispositivo.equals("Ventilador temperatura mínima")) {
    VentiladorTemperaturaMinima = RXStatus.toFloat();
  }
  
  
  else if (RXDispositivo.equals("Aquecedor")) {
    if (RXStatus.equals("ligar")) {
      Aquecedor = 1;
    }
    else if (RXStatus.equals("desligar")) {
      Aquecedor = 0;
    }
    else if (RXStatus.equals("automático")) {
      Aquecedor = 2;
    }
    if (Iniciando) { // nao roda quando se esta iniciando o esp
      ControleAquecedor ();
    }
  }
  else if (RXDispositivo.equals("Aquecedor temperatura máxima")) {
    AquecedorTemperaturaMaxima = RXStatus.toFloat();
  }
  else if (RXDispositivo.equals("Aquecedor temperatura mínima")) {
    AquecedorTemperaturaMinima = RXStatus.toFloat();
  }
  /*  else if (RXDispositivo.equals("Computador presença")) {
      if (RXStatus.equals("ativar")) {
        ComputadorPresenca = true;
      } else {
        ComputadorPresenca = false;
      }
    }
      else if (RXDispositivo.equals("Exaustor presença")) {
        if (RXStatus.equals("ativar")) {
          ExaustorPresenca = true;
        } else {
          ExaustorPresenca = false;
        }
      }*/

  /*
    else if (RXDispositivo.equals("Iluminação 1 presença")) {
      if (RXStatus.equals("ativar")) {
        Iluminacao1Presenca = true;
      } else {
        Iluminacao1Presenca = false;
      }
    }
    else if (RXDispositivo.equals("Iluminação 2 presença")) {
      if (RXStatus.equals("ativar")) {
        Iluminacao2Presenca = true;
      } else {
        Iluminacao2Presenca = false;
      }
    }
    else if (RXDispositivo.equals("Iluminação mesa presença")) {
      if (RXStatus.equals("ativar")) {
        IluminacaoMesaPresenca = true;
      } else {
        IluminacaoMesaPresenca = false;
      }
    }
    else if (RXDispositivo.equals("Iluminação indireta presença")) {
      if (RXStatus.equals("ativar")) {
        IluminacaoIndiretaPresenca = true;
      } else {
        IluminacaoIndiretaPresenca = false;
      }
    }
    else if (RXDispositivo.equals("Janela presença")) {
      if (RXStatus.equals("ativar")) {
        JanelaPresenca = true;
      } else {
        JanelaPresenca = false;
      }
    }
    ///  else if (RXDispositivo.equals("Umidificador presença")) {
    ///      if (RXStatus.equals("ativar")) {
    ///        UmidificadorPresenca = true;
    ///      } else {
    ///        UmidificadorPresenca = false;
    ///      }
    ///    }
    else if (RXDispositivo.equals("Ventilador presença")) {
      if (RXStatus.equals("ativar")) {
        VentiladorPresenca = true;
      } else {
        VentiladorPresenca = false;
      }
    }

  */
  if (Iniciando) {// nao roda quando se esta iniciando o esp
    if (RXDispositivo.equals("Z Computador")) {
      if (RXStatus.equals("ligar")) {
        Computador = 1;
      }
      else if (RXStatus.equals("desligar")) {
        Computador = 0;
      }
      ComputadorAcionar();
    }
    else if (RXDispositivo.equals("Z ESP32 reiniciar")) {
      if (RXStatus.equals("1")) {
        esp_restart(); //reinicia o chip
      }
    }
    /* else if (RXDispositivo.equals("Z Iluminação todas")) {
       if (RXStatus.equals("ligar")) {
         digitalWrite(saida2, LOW);  //19 iluminação 1 quarto
         digitalWrite(saida3, LOW);   //17 iluminação 2 quarto
         FlagLerSaidas = true;
         //LerSaidas();
       }
       else if (RXStatus.equals("desligar")) {
         digitalWrite(saida2, HIGH);  //19 iluminação 1 quarto
         digitalWrite(saida3, HIGH);   //17 iluminação 2 quarto
         digitalWrite(saida4, HIGH);  //5 iluminação mesa
         digitalWrite(saida5, LOW);    //18 iluminação indireta
         FlagLerSaidas = true;
         //LerSaidas();
       }
      }*/
    else if (RXDispositivo.equals("Z Reinicia leituras")) {
      ReiniciaLeitura = true;
    }
    else if (RXDispositivo.equals("Z Zera falhas")) {
      if (RXStatus.equals("1")) {
        ZeraContagemFalhas = true;
      }
    }
    FlagACK = true;
  }// nao roda quando se esta iniciando o esp

  //Serial.println("fim do ativa saidas");
}

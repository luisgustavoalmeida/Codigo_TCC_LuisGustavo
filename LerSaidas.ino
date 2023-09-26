void LerSaidas () {                          //quando aciona osensor de toque manda para o FB os novos estatus das lampadas
  FlagLerSaidas = false;
  if (digitalRead(saida2)) {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação 1" , "desligar" )) {
      FlagLerSaidas = true;
    }
  } else {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação 1" , "ligar" )) {
      FlagLerSaidas = true;
    }
  }
  if (digitalRead(saida3)) {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação 2" , "desligar" )) {
      FlagLerSaidas = true;
    }
  } else {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação 2" , "ligar" )) {
      FlagLerSaidas = true;
    }
  }
  if (digitalRead(saida4)) {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação mesa" , "desligar" )) {
      FlagLerSaidas = true;
    }
  } else {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação mesa" , "ligar" )) {
      FlagLerSaidas = true;
    }
  }
  if (digitalRead(saida5)) {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação indireta" , "ligar" )) {
      FlagLerSaidas = true;
    }
  } else {
    if (!Firebase.setString(firebaseData1, path1 +  "/Iluminação indireta" , "desligar" )) {
      FlagLerSaidas = true;
    }
  }
  //if (!Firebase.setString(firebaseData1, path1 +  "/Z Iluminação todas" , "ok" )) {
  // FlagLerSaidas = true;
  //}
  switch (Janela) {
    case 0:
      if (!Firebase.setString(firebaseData1, path1 +  "/Janela" , "fechar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 1:
      if (!Firebase.setString(firebaseData1, path1 +  "/Janela" , "abrir" )) {
        FlagLerSaidas = true;
      }
      break;
    case 2:
      if (!Firebase.setString(firebaseData1, path1 +  "/Janela" , "automático" )) {
        FlagLerSaidas = true;
      }
      break;
    case 3:
      if (!Firebase.setString(firebaseData1, path1 +  "/Janela" , "manter-frio" )) {
        FlagLerSaidas = true;
      }
      break;
    case 4:
      if (!Firebase.setString(firebaseData1, path1 +  "/Janela" , "manter-quente" )) {
        FlagLerSaidas = true;
      }
      break;

      //default:
      // comando(s)
      // break;
  }
  if (!Firebase.setInt(firebaseData1, path1 +  "/Janela deslizador" , JanelaDeslizador )) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Janela temperatura máxima" , JanelaTemperaturaMaxima )) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Janela temperatura mínima" , JanelaTemperaturaMinima )) {
    FlagLerSaidas = true;
  }
  
  switch (Ventilador) {
    case 0:
      if (!Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "desligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 1:
      if (!Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "ligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 2:
      if (!Firebase.setString(firebaseData1, path1 +  "/Ventilador" , "automático" )) {
        FlagLerSaidas = true;
      }
      break;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Ventilador deslizador" , VentiladorDeslizador )) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Ventilador temperatura máxima" , VentiladorTemperaturaMaxima )) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Ventilador temperatura mínima" , VentiladorTemperaturaMinima )) {
    FlagLerSaidas = true;
  }

   switch (Aquecedor) {
    case 0:
      if (!Firebase.setString(firebaseData1, path1 +  "/Aquecedor" , "desligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 1:
      if (!Firebase.setString(firebaseData1, path1 +  "/Aquecedor" , "ligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 2:
      if (!Firebase.setString(firebaseData1, path1 +  "/Aquecedor" , "automático" )) {
        FlagLerSaidas = true;
      }
      break;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Aquecedor temperatura máxima" , AquecedorTemperaturaMaxima )) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setFloat(firebaseData1, path1 +  "/Aquecedor temperatura mínima" , AquecedorTemperaturaMinima )) {
    FlagLerSaidas = true;
  }

  switch (Umidificador) {
    case 0:
      if (!Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "desligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 1:
      if (!Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "ligar" )) {
        FlagLerSaidas = true;
      }
      break;
    case 2:
      if (!Firebase.setString(firebaseData1, path1 +  "/Umidificador" , "automático" )) {
        FlagLerSaidas = true;
      }
      break;
  }
  if (!Firebase.setInt(firebaseData1, path1 +  "/Umidade máxima" , UmidadeMaxima)) {
    FlagLerSaidas = true;
  }
  if (!Firebase.setInt(firebaseData1, path1 +  "/Umidade mínima" , UmidadeMinima)) {
    FlagLerSaidas = true;
  }


}

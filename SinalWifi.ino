void Sinalwifi() {                          //testa a intencidade o sinal wifi que chega para o esp
  int SinalWifi = int(WiFi.RSSI());
  if ((SinalWifi < (SinalWifiM - 2)) || (SinalWifi > (SinalWifiM + 2))) {
    Firebase.setInt(firebaseData1, path2 +  "/Sinal wifi" , SinalWifi);
    SinalWifiM = SinalWifi;
  }
}

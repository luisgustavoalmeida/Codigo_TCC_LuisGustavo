void ReeniciaContagemFalhas  () {
  if (Firebase.setInt(firebaseData1, path2 +  "/Reinicializações" , 0)) {
    ZeraContagemFalhas = false;
  }
}

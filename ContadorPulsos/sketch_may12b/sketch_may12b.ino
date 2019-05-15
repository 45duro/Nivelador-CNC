void setup() {
  //Declaro los pines de salida
  for(int j = 4; j <= 9; j++){
    pinMode(j,1);
  }

    //Mandamos todos los pines a 0
  for(int j = 4; j <= 9; j++){
    digitalWrite(j,0);
  }

}

void loop() {
  digitalWrite(7,0);
  digitalWrite(4,1);
  digitalWrite(8,0);
  digitalWrite(9,0);
  analogWrite(5, 200);
  analogWrite(6, 0);

}

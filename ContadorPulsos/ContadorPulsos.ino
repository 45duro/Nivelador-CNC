int encoder = 2, encoderPos=0, encoderLast = 0, encoderActual = 0;
int radio = 36;

void setup() {
  pinMode(encoder, INPUT);
  Serial.begin(115200);

  for(int j = 4; j <= 9; j++){
    pinMode(j,1);
  }

  for(int j = 4; j <= 9; j++){
    digitalWrite(j,0);
  }

  digitalWrite(7,1);  //Horario
  digitalWrite(8,0); //Antiorario
  analogWrite(5, 50); //Pwm

}

void loop() {
  encoderActual=digitalRead(encoder);

  if((encoderLast == 0) && (encoderActual == 1)){
    encoderPos++;
    Serial.print("Encoder POS: "); Serial.println(encoderPos);
    //Serial.print("Enc pos rad: "); Serial.println(encoderPos*36);
    //Serial.print("Enc pos real: "); Serial.println(encoderPos*0.2*3.141592*36);
  }

  encoderLast = encoderActual;

  if(encoderActual > 2082){
    analogWrite(5, 0); //Pwm
    while(1);
  }

}

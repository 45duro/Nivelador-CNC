int encoder = 2, encoderPos=0, encoderLast = 0, encoderActual = 0;
int radio = 36;

void setup() {
  pinMode(encoder, INPUT);
  Serial.begin(115200);

}

void loop() {
  encoderActual=digitalRead(encoder);

  if((encoderLast == 0) && (encoderActual == 1)){
    encoderPos++;
    Serial.print("Encoder POS: "); Serial.println(encoderPos);
    Serial.print("Enc pos rad: "); Serial.println(encoderPos*36);
    Serial.print("Enc pos real: "); Serial.println(encoderPos*0.2*3.141592*36);
  }

  encoderLast = encoderActual;

}

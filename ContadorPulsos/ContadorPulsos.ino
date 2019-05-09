//Relacion del motor de 131 con conteo de falnco de 16 tics por vuelta del motor
// lo que quiere decir que para 360 grados de giro o una revolucion se obtendrá
// 131*16 = 2096 tics a la salida

int encoderPos=0, encoderLast = 0, encoderActual = 0;
int radio = 36;
float vueltas = 10;
int potencia = 255;

void setup() {
  //Con este baudiaje se ajusta perfeccto
  Serial.begin(57600);

  //Si o si toca con interrupcion ya que de otromodo lo hace mal, 
  //se queda o puierde pulso y el baudiaje de la comunicación lo vuelve loco
  attachInterrupt(digitalPinToInterrupt(2), Encoder,FALLING);

  //Declaro los pines de salida
  for(int j = 4; j <= 9; j++){
    pinMode(j,1);
  }

  //Mandamos todos los pines a 0
  for(int j = 4; j <= 9; j++){
    digitalWrite(j,0);
  }

  //Arranque de prueba para el motor
  digitalWrite(7,1);  //Horario
  digitalWrite(8,0); //Antiorario
  analogWrite(5, potencia); //Pwm

}

//Funcion para contar
void Encoder(){
  encoderPos++;
  //alcolocarse se realentyiza el sistema y colapsa la mediccion por eso mejor no colocar ningun print
  //Serial.println(encoderPos);
}

void loop() {

  //Determinamos la revolucion que quiero
  if(encoderPos >= (2096*vueltas)){
    digitalWrite(7,1);  //Horario
    digitalWrite(8,1); //Antiorario
    analogWrite(5, potencia); //Pwm
    Serial.println(encoderPos);
    while(1);

  }

}

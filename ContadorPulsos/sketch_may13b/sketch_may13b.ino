//Relacion del motor de 131 con conteo de falnco de 16 tics por vuelta del motor
// lo que quiere decir que para 360 grados de giro o una revolucion se obtendrá
// 131*16 = 2096 tics a la salida

volatile int encoderPos=0;
int vueltas = 1;
int potencia = 2500, flancos=2000;
//Motor
byte giroAdelante = 9, giroAtras = 4, pinVelocidad = 6;


void setup() {
  //Con este baudiaje se ajusta perfeccto
  Serial.begin(9600);

  //Si o si toca con interrupcion ya que de otromodo lo hace mal, 
  //se queda o puierde pulso y el baudiaje de la comunicación lo vuelve loco
  attachInterrupt(digitalPinToInterrupt(2), Encoder,CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), arranque,RISING);

  //Declaro los pines de salida
  pinMode(giroAdelante,1);pinMode(giroAtras,1);pinMode(pinVelocidad,1);


}

//Funcion para contar
void Encoder(){
  encoderPos++;
  //alcolocarse se realentyiza el sistema y colapsa la mediccion por eso mejor no colocar ningun print
  //Serial.println(encoderPos);
}

void inHome(){

  FrenarMotor();
  delay(500);
  pararMotor();
  encoderPos=0;
}

void arranque(){
  encoderPos=0;
  //Arranque de prueba para el motor
  digitalWrite(giroAdelante,1);  //Horario
  digitalWrite(giroAtras,0); //Antiorario
  analogWrite(pinVelocidad, potencia); //Pwm
}

void pararMotor(){
  digitalWrite(giroAdelante,0);  //Horario
  digitalWrite(giroAtras,0); //Antiorario
  analogWrite(pinVelocidad, 0); //Pwm
}

void FrenarMotor(){
  digitalWrite(giroAdelante,1);  //Horario
  digitalWrite(giroAtras,1); //Antiorario
  analogWrite(pinVelocidad, 255); //Pwm
}


void loop() {

  if(encoderPos >= 3900){
    FrenarMotor();
    //Serial.println(encoderPos);
  }



}

//Relacion del motor de 131 con conteo de falnco de 16 tics por vuelta del motor
// lo que quiere decir que para 360 grados de giro o una revolucion se obtendrá
// 131*16 = 2096 tics a la salida

unsigned long encoderPos=0;
float vueltas = 2;
int potencia = 20;
//Motor
byte giroAdelante = 9, giroAtras = 4, pinVelocidad = 6;


void setup() {
  //Con este baudiaje se ajusta perfeccto
  Serial.begin(9600);

  //Si o si toca con interrupcion ya que de otromodo lo hace mal, 
  //se queda o puierde pulso y el baudiaje de la comunicación lo vuelve loco
  attachInterrupt(digitalPinToInterrupt(2), Encoder,FALLING);
  attachInterrupt(digitalPinToInterrupt(3), inHome,RISING);

  //Declaro los pines de salida
  for(int j = 4; j <= 9; j++){
    pinMode(j,1);
  }

  //Mandamos todos los pines a 0
  for(int j = 4; j <= 9; j++){
    digitalWrite(j,0);
  }

  //Arranque de prueba para el motor
  digitalWrite(giroAdelante,1);  //Horario
  digitalWrite(giroAtras,0); //Antiorario
  analogWrite(pinVelocidad, potencia); //Pwm

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

  //Determinamos la revolucion que quiero
  if(encoderPos >= (2096*vueltas)){
    FrenarMotor();
    Serial.println(encoderPos);
    while(1);

  }

}

#include <Wire.h> 
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>


//Variables de LCD
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//Variavles de KEyPAD
const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[ROWS] = {5, 7, 8, 10}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {11, 12, 13}; //connect to the column pinouts of the kpd

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Variables Globales del programa
String alturaChain = "";
int altura = 0,limiteMaximo = 230, limiteMinimo = 1;
byte seleccionador = 0;


/*Variables de Motor
*/
//Relacion del motor de 131 con conteo de falnco de 16 tics por vuelta del motor
// lo que quiere decir que para 360 grados de giro o una revolucion se obtendrá
// 131*16 = 2096 tics a la salida

unsigned long encoderPos=0;
float vueltas = 10, constante = 0.125;
int potencia = 255;

//Motor
byte giroAdelante = 9, giroAtras = 4, pinVelocidad = 6;



void setup()
{
  // initialize the lcd 
  lcd.init();                     
  //Encender la luz de fondo.
  lcd.backlight();

  //Muestre la bienvenida
  mostrarBienvenida();
  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad
  Serial.begin(57600);
  
  
  //Si o si toca con interrupcion ya que de otromodo lo hace mal, 
  //se queda o puierde pulso y el baudiaje de la comunicación lo vuelve loco
  attachInterrupt(digitalPinToInterrupt(2), Encoder,FALLING);
  attachInterrupt(digitalPinToInterrupt(3), inHome,RISING);
  
  //Declaro los pines de salida
  pinMode(giroAdelante,1);pinMode(giroAtras,1);pinMode(pinVelocidad,1);
}

void mostrarBienvenida(){

  //Caracter del la interfaz predeterminado
  byte avion[8] = {
    B00100,
    B00100,
    B01110,
    B11111,
    B10101,
    B00100,
    B00100,
    B01110,
  };

  //Crear caracter
  lcd.createChar (0,avion);
  // Escribimos el Mensaje en el LCD en una posición  central.
  lcd.setCursor(0, 0);
  lcd.write(byte (0));
  lcd.write(byte (0));
  lcd.print(" BIENVENIDO ");
  lcd.write(byte (0));
  lcd.write(byte (0));
  
  lcd.setCursor(5, 1);
  lcd.print("Piloto");


  pinMode(13,1);
  
  delay (5000);
}

/*
String capturaTeclado(){
  char key = keypad.getKey();

    if (key) {
        String m = String(key);
        Serial.println(m);
    }
}*/



void keypadEvent(KeypadEvent key){
    switch (keypad.getState()){
    case PRESSED:
        if (key == '*') {
          //Funcion solo presionar
          alturaChain="";
          lcd.clear();
          
        }

        //Aquí hago una comparativa para saber que presiono numeros y debe sumarlos a la cadena principal
        if (key >= '0' && key <= '9'){
          alturaChain += String(key);
        }
        
        break;

    case RELEASED:
        //hjgjhg
        break;

    case HOLD:
        if (key == '#') {
            //Funciones de enter
            Serial.println(alturaChain);
            if(estaturaValida(alturaChain)){
              //imprima correcto
              altura = alturaChain.toInt();
              lcd.clear();
              lcd.print("Correcto... ");
              seleccionador = 1;
              delay(2000);
              lcd.clear();
              
            }
            
            alturaChain = "";
            
        }
        break;
    }
}

boolean estaturaValida(String altura){
  int flag = altura.toInt();
  if(flag <= limiteMaximo && flag >= limiteMinimo){
    Serial.println("SI valida");
    return true;
  }
  else{
    Serial.println("No valida");
    return false;
  }
}

void loop()
{
  lcd.clear();
  while(seleccionador == 0){
    //Funcion para obtener lo del teclado y activa el listener Event
    char key = keypad.getKey();
    
    lcd.setCursor(0, 0);
    lcd.print("Digite su Altura ");
    lcd.setCursor(0, 1);
    lcd.print(" cm: ");
    lcd.print(alturaChain);
  }
  
  while(seleccionador == 1){
      lcd.setCursor(0,0);
      lcd.print("  Ajustando el  ");
      lcd.setCursor(0,1);
      lcd.print("    Sistema   ");
      seleccionador = 3;

      altura * 10;
      vueltas = constante * altura;
      arrancarMotor();
  }

  while(seleccionador == 3){
    Serial.println(encoderPos);
    if(encoderPos >= (2096*vueltas)){
      FrenarMotor();
      Serial.println(encoderPos);
      seleccionador = 0;
    }
  }
  

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

void arrancarMotor(){
  //Arranque de prueba para el motor
  digitalWrite(giroAdelante,1);  //Horario
  digitalWrite(giroAtras,0); //Antiorario
  analogWrite(pinVelocidad, potencia); //Pwm
}

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
byte rowPins[ROWS] = {10, 9, 8, 7}; //connect to the row pinouts of the kpd
byte colPins[COLS] = {6, 5, 4}; //connect to the column pinouts of the kpd

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

//Variables De TIempo
//unsigned long loopCount =0;
//unsigned long startTime;

//Variables Globales del programa
String alturaChain = "";

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
  
  
  //startTime = millis();
  
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
        if (key == '*') {
            //Funciones de enter
            Serial.println(alturaChain);
            alturaChain = "";
            
        }
        break;
    }
}

String altura = "";

void loop()
{
    //Funcion para obtener lo del teclado y activa el listener Event
  char key = keypad.getKey();
  lcd.setCursor(0, 0);
  lcd.print("Digite su Altura ");
  lcd.setCursor(0, 1);
  lcd.print(" cm: ");
  lcd.print(alturaChain);
  

}

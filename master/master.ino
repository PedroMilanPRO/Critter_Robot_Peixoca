#include <Keypad.h> //Biblioteca para uso de teclados matriciais 

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // Criando um LCD de 16x2 no endereço 0x20

const byte numLinhas = 4; //Quantidade de linhas do teclado
const byte numColunas = 4; //Quantidade de colunas do teclado

int state = 0;
int Analogstate = 0;


#define pinVRx A1
#define pinVRy A2

int valorVRy;
int valorVRx;


int tempoKey = 0;
int tempoJoy = 0;

//Matriz de caracteres referente aos botões do teclado
char teclasMatriz[numLinhas][numColunas] = {
{'1', '2', '3', '4'},
{'5', '6', '7', '8'},
{'9', '0', '*', '+'},
{'#', '$', '%', '@'}
};

byte pinosLinhas[numLinhas] = {9, 8, 7, 6}; //Pinos das linhas
byte pinosColunas[numColunas] = {13, 12, 11, 10}; //Pinos das Colunas

//Cria um objeto do tipo Keypad"
Keypad meuteclado = Keypad(makeKeymap(teclasMatriz), pinosLinhas, pinosColunas, numLinhas, numColunas);

void setup() {
Serial.begin(38400); //Inicia a comunicação serial
bluetooth.begin(38400);

  pinMode(pinVRx, INPUT);
  pinMode(pinVRy, INPUT);

lcd.init();                 // Inicializando o LCD
lcd.backlight();            // Ligando o BackLight do LCD
lcd.print("Ola! (0w0)");
delay(5000);
lcd.clear();
// Exibindo no LED Hello, world!
}

void loop() {
if ((millis() - tempoKey) >= 100){
  char pressionado = meuteclado.getKey(); ///Verifica se alguma tecla foi pressionada
  if(pressionado){
  Serial.println(pressionado);
  bluetooth.write(pressionado);
  if (pressionado == '1'){
      lcd.print("Comando levantar."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();

  }
    if (pressionado == '2'){
      lcd.print("Comando descer."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
  if (pressionado == '3'){
      lcd.print("Comando Tchau."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
    if (pressionado == '4'){
      lcd.print("Comando andar."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
    if (pressionado == '5'){
      lcd.print("Comando Gabigol."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
  if (pressionado == '6'){
      lcd.print("Comando Passo."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
    if (pressionado == '7'){
      lcd.print("Comando Molejo."); // Exibindo no LED Hello, world!
      delay(3000);
      lcd.clear();
  }
  }
  tempoKey = millis();
}
}
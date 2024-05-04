#include <Servo.h>
#include <HCSR04.h>

#include <SoftwareSerial.h>
SoftwareSerial bluetooth(2, 3); // RX, TX

unsigned long tempoUltra = 0;
unsigned long tempoKey = 0;
unsigned long tempoLuz = 0;

//função molejo
unsigned long startTime;
unsigned long interval;

long aleatorio;


#define TRIG_PIN 12
#define ECHO_PIN 13

#define led 11
#define ldr A4
int vldr = 0;

HCSR04 hc(TRIG_PIN, ECHO_PIN);

char analogstate = "";
char state = "";

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int servoposEsquerda = 0;
int servoposDireita = 180;

void setup() {
  
  Serial.begin(38400); //Inicia a comunicação serial
    
  servo1.attach(A0);
  servo2.attach(A1);
  servo3.attach(A2);
  servo4.attach(A3);
  pinMode(ldr, INPUT);
  pinMode(led, OUTPUT);

  randomSeed(analogRead(7));


    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);
  
    bluetooth.begin(38400);

  delay(1000);
}

void molejo(){
   // mover o servo 1 e 2 em 100 graus
    servo1.write(servoposDireita);
    servo2.write(servoposEsquerda);
    delay(500);
    servo3.write(150);
    servo4.write(30);
    delay(300);

 // mover o servo 3 e 4 alternadamente de 0 para 180 por 4 segundos
 startTime = millis();
 interval = 1000 / 4;

 while (millis() - startTime < 3000) {
    servo1.write(40);
    delay(interval);

    servo2.write(160);
    delay(interval);
     
    servo1.write(160);
    delay(interval);

    servo2.write(40);
 }
  delay(500);
    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);

  state = "";

}

char dancar(){
  // Movimento ascendente
  for (int pos = 0; pos <= 180; pos++) {
    servo1.write(pos);
    servo2.write(pos);
    servo3.write(180 - pos);
    servo4.write(180 - pos);

    if (pos == 4) {  // Aproximadamente 400 milissegundos
      servo1.write(0);
      servo2.write(0);
      servo4.write(180);
      delay(90);  // Atraso para manter os servos em 0 por 600 milissegundos
      
    }
    
    delay(4);
  }
  delay(4);
  // Movimento descendente
  for (int pos = 180; pos >= 0; pos--) {
    servo2.write(pos);
    servo3.write(180 - pos);

    if (pos == 0) {
      servo1.write(0);
      servo4.write(0);
    }
   
  }
}

char andar(){
  // Movimento ascendente
  for (int pos = 0; pos <= 180; pos++) {
    servo1.write(180 - pos);
    servo2.write(pos);
    servo3.write(pos);
    servo4.write(180 - pos);

    if (pos == 4) {  // Aproximadamente 400 milissegundos
      servo1.write(0);
      servo2.write(0);
      servo4.write(180);
      servo3.write(180);

      delay(90);  // Atraso para manter os servos em 0 por 600 milissegundos
      
    }
    
    delay(10);
  }
  delay(4);
  // Movimento descendente
  for (int pos = 100; pos >= 0; pos--) {
    servo2.write(180 - pos);
    servo3.write(180 - pos);

    if (pos == 0) {
      servo1.write(0);
      servo4.write(0);
    }
   
  }

  state = "";

}

void levantar() {
    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);
    
    state = "";
    }

void descer() {
    servo1.write(servoposDireita);
    servo2.write(servoposEsquerda);
    servo3.write(90);
    servo4.write(90);

    state = "";
    }

void gabigol() {
    servo1.write(servoposDireita);
    servo2.write(servoposEsquerda);
    servo3.write(150);
    servo4.write(30);

    delay(5000);

    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);

    state = "";
    }

 void tchau() {
  servo2.write(90);
  servo3.write(90);
  servo1.write(180);
  servo4.write(180);
  delay(500);
  
  int duration = 2500; // 5 segundos
  int delayBetweenPositions = 300; // Tempo de espera entre cada passo (ajuste conforme necessário)
  int steps = duration / (2 * delayBetweenPositions);

  for (int i = 0; i < steps; i++) {
    servo4.write(100); // Move para a posição 0
    delay(delayBetweenPositions);
    servo4.write(180); // Move para a posição 180
    delay(delayBetweenPositions);
  }

  delay(500);
  // Retorna o servo 4 para a posição inicial (0)

    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);

    state = "";
 }



void loop() {
  if ((millis() - tempoKey) >= 100){
  if (bluetooth.available()){
     state = char(bluetooth.read());
     Serial.println(state);
  }
  
   // Verifica se a tecla pressionada é '1' e chama a função andar
    if (state == '1') {
      levantar();
    }
    if (state == '2') {
      descer();
    }
    if (state == '3') {
      tchau();
    }
    if(state == '4'){
      dancar();
    } 
     if (state == '5') {
      gabigol();
     }
      if (state == '6') {
      andar();
     }
      if (state == '7') {
      molejo();
     }
     tempoKey = millis();
  }

   if ((millis() - tempoUltra) >= 1000){
     Serial.print("Valor do Ultrassonico: ");
    Serial.println(hc.dist());
    if (hc.dist() <= 7 && hc.dist() > 3){
    if (random(1, 3) == 1){
    servo1.write(servoposDireita);
    servo2.write(servoposEsquerda);
    servo3.write(servoposEsquerda);
    servo4.write(servoposDireita);
    
    delay(5000);
        
    servo1.write(servoposEsquerda);
    servo2.write(servoposDireita);
    servo3.write(90);
    servo4.write(90);
    }
    else if (random(1, 3) == 2){
      tchau();
    }
    }
    tempoUltra = millis();
  }

    vldr = analogRead(ldr);
    if (vldr < 200) {
      digitalWrite(led, HIGH);
    }else{
      digitalWrite(led, LOW);
    }
    Serial.print("Valor do LDR: ");
    Serial.println(vldr);
    delay(100);
}
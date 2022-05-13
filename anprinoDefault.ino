#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 4
#define ENA 10
#define ENB 3
#define TRIGGER_PIN  13
#define ECHO_PIN     12
char opcao;
float distancia;
Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
SoftwareSerial mySerial(5, 6); // RX, TX
void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (mySerial.available()) {
 
    opcao = mySerial.read();
    Serial.println(opcao);
    switch (opcao) {
      case 'F': moveF();
        break;
      case 'B': moveB();
        break;
      case 'R': moveR();
        break;
      case 'L': moveL();
        break;
      case 'S': moveSTOP();
        break;
      case 'X':
        do {
          autonomo();
          opcao = mySerial.read();
        } while (opcao != 'x' );
           Serial.println(opcao);
        break;
    }
  }
}

void moveF() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}
void moveB() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void moveL() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

}
void moveR() {
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

}
void moveSTOP() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

}
void autonomo() {
  long microsec = ultrasonic.timing();
  distancia = ultrasonic.convert(microsec, Ultrasonic::CM);
  moveF();
  if (distancia < 30) {
    moveSTOP();
    delay (1000);
    moveR();
    delay (700);
  }
}

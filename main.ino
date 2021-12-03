#define BLYNK_USE_DIRECT_CONNECT

#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX

#define BLYNK_PRINT DebugSerial

/* Fill-in your Template ID (only if using Blynk.Cloud) */
//#define BLYNK_TEMPLATE_ID   "YourTemplateID"


#include <BlynkSimpleSerialBLE.h>

char auth[] = "UWlLJttCzGXtU22-9rw-MwlP6kSLHJx0";

#define roda_d_f_1 A4
#define roda_d_f_2 A5
#define roda_d_t_1 3
#define roda_d_t_2 5

#define roda_e_f_1 8
#define roda_e_f_2 9
#define roda_e_t_1 11
#define roda_e_t_2 6

#define en1a 7
#define en2a 10
#define en1b 4
#define en2b 2

void frente();
void tras();
void direita();
void esquerda();
void parar();

unsigned long time = 0;

#include <dht.h>   //biblioteca do sensor de umidade e temperatura

#define dht_pin 13   //pino de sinal do dht11 ligado no digital 13

dht   my_dht;   //objeto para o sensor

int    temperatura = 0x00,   //armazena a temperatura em inteiro
       umidade     = 0x00;   //armazena a umidade em inteiro

#define pinLedAzul A12 //azul
#define pinLedVermelho A14 //vermelho
#define pinLedAmarelo A15 //amarelo
#define pinLedVerde A13 //verde

//unsigned long timeLed = 0;
//int ledAtual = 1;

#define pinBuzzer 47

#include <NewPing.h>
#define TRIGGER_PIN  25  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     23  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

#define pinJoystick V0
#define pinTemperatura V1
#define pinUmidade V2

int joyX, joyY;

BLYNK_WRITE(pinJoystick) {
  joyX = param[0].asInt();
  joyY = param[1].asInt();
}


void setup()
{
  // Debug console
  DebugSerial.begin(9600);

  DebugSerial.println("Waiting for connections...");

  // Blynk will work through Serial
  // 9600 is for HC-06. For HC-05 default speed is 38400
  // Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);

  Serial.begin(9600);
  pinMode(en1a, OUTPUT);
  digitalWrite(en1a, HIGH);
  pinMode(en2a, OUTPUT);
  digitalWrite(en2a, HIGH);
  pinMode(en1b, OUTPUT);
  digitalWrite(en1b, HIGH);
  pinMode(en2b, OUTPUT);
  digitalWrite(en2b, HIGH);
  pinMode(roda_e_f_1, OUTPUT);
  pinMode(roda_e_f_2, OUTPUT);
  pinMode(roda_e_t_1, OUTPUT);
  pinMode(roda_e_t_2, OUTPUT);
  pinMode(roda_d_f_1, OUTPUT);
  pinMode(roda_d_f_2, OUTPUT);
  pinMode(roda_d_t_1, OUTPUT);
  pinMode(roda_d_t_2, OUTPUT);
}

void loop() {
  Blynk.run();
  if (joyY > 100 && joyY < 150) {
    if (joyX > 128) direita();
    else if (joyX < 128) esquerda();
    else frente();
  }
  else if (joyY >= 150) frente();
  else if (joyY <= 100) tras();
  if ((joyX == 0 && joyY == 0) || sonar.ping_cm() < 20.0) parar();
  
  my_dht.read11(dht_pin);
  temperatura = my_dht.temperature;
  umidade     = my_dht.humidity;
  Blynk.virtualWrite(V1, temperatura);
  Blynk.virtualWrite(V2, umidade);
  /*if(millis() >= timeLed + 500){
      timeLed += 500;
      trocarLed();
    }*/
}

void frente() {
  digitalWrite(roda_e_f_1, LOW);
  digitalWrite(roda_e_f_2, HIGH);
  digitalWrite(roda_e_t_1, HIGH);
  digitalWrite(roda_e_t_2, LOW);
  digitalWrite(roda_d_f_1, LOW);
  digitalWrite(roda_d_f_2, HIGH);
  digitalWrite(roda_d_t_1, LOW);
  digitalWrite(roda_d_t_2, HIGH);
}

void tras() {
  digitalWrite(roda_e_f_1, HIGH);
  digitalWrite(roda_e_f_2, LOW);
  digitalWrite(roda_e_t_1, LOW);
  digitalWrite(roda_e_t_2, HIGH);
  digitalWrite(roda_d_f_1, HIGH);
  digitalWrite(roda_d_f_2, LOW);
  digitalWrite(roda_d_t_1, HIGH);
  digitalWrite(roda_d_t_2, LOW);
}

void direita() {
  digitalWrite(roda_e_f_1, LOW);
  digitalWrite(roda_e_f_2, HIGH);
  digitalWrite(roda_e_t_1, HIGH);
  digitalWrite(roda_e_t_2, LOW);
  digitalWrite(roda_d_f_1, HIGH);
  digitalWrite(roda_d_f_2, LOW);
  digitalWrite(roda_d_t_1, HIGH);
  digitalWrite(roda_d_t_2, LOW);
}

void esquerda() {
  digitalWrite(roda_e_f_1, HIGH);
  digitalWrite(roda_e_f_2, LOW);
  digitalWrite(roda_e_t_1, LOW);
  digitalWrite(roda_e_t_2, HIGH);
  digitalWrite(roda_d_f_1, LOW);
  digitalWrite(roda_d_f_2, HIGH);
  digitalWrite(roda_d_t_1, LOW);
  digitalWrite(roda_d_t_2, HIGH);
}

void parar() {
  digitalWrite(roda_e_f_1, LOW);
  digitalWrite(roda_e_f_2, LOW);
  digitalWrite(roda_e_t_1, LOW);
  digitalWrite(roda_e_t_2, LOW);
  digitalWrite(roda_d_f_1, LOW);
  digitalWrite(roda_d_f_2, LOW);
  digitalWrite(roda_d_t_1, LOW);
  digitalWrite(roda_d_t_2, LOW);
}

/*void trocarLed(){
  switch(ledAtual){
    case 1:
      analogWrite(pinLedAzul, 0);
      analogWrite(pinLedVermelho, 128);
      ledAtual++;
      break;
    case 2:
      analogWrite(pinLedVermelho, 0);
      analogWrite(pinLedAmarelo, 128);
      ledAtual++;
      break;
    case 3:
      analogWrite(pinLedAmarelo, 0);
      analogWrite(pinLedVerde, 128);
      ledAtual++;
      break;
    case 4:
      analogWrite(pinLedVerde, 0);
      analogWrite(pinLedAzul, 128);
      ledAtual = 1;
  }
}*/

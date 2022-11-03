
// notas musicais 
#include "pitches.h"


#define LDR_PIN 16
#define LED1 1
#define LED2 2
#define LED3 4
#define LED4 5
#define setbtn 6
#define playbtn 7
#define buzzer 13

// listas para salvar o historico 
int lista [10][4] = {};
int lista_sons [10] = {};

//para seguir um index
int x = -1;



void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(setbtn, INPUT_PULLUP);
  pinMode(playbtn, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);


}

// funcao para mostar o array nos leds com os valores binarios
void mostrar(){
  for (int i = 0; i <= x; i++) {
    if (lista[i][0] == 1){
      digitalWrite(LED1, HIGH);
    }
    if (lista[i][1] == 1){
      digitalWrite(LED2, HIGH);
    }
    if (lista[i][2] == 1){
      digitalWrite(LED3, HIGH);
    }
    if (lista[i][3] == 1){
      digitalWrite(LED4, HIGH);
    }
    tone(buzzer, lista_sons[x]);
    delay(1000);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    noTone(buzzer);

}
}

//limpar o array apos ser mostrado
void limpar(){
  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < 4; j++) {
      lista[i][j] = 0;
    }
  }
}

//funcao para transformar o valor recebido em um valor binario e armazenar em um array
void trans_binary(){
  int analogValue = analogRead(LDR_PIN);

  // fazer com que o valor recebido do sensor esteja em uma escala de 15 numeros
  if(analogValue > 100 && analogValue < 3500){
    analogValue = (analogValue - 100)/226;
    Serial.println(analogValue);
  }
  else if(analogValue < 100){
    analogValue = 0;
    Serial.println(analogValue);
  }
  else if(analogValue > 3500){
    analogValue = 15;
    Serial.println(analogValue);
  }
  // transformar o numero que esta em uma escala de 1-15 em um numero binario
  int valor_binario[4] = {analogValue / 8, (analogValue % 8) / 4, ((analogValue % 8)%4)/2,(((analogValue % 8)%4)%2)};

  //ter um fedback do valor que sera colocado dentro do array
  if (valor_binario[0] == 1){
    digitalWrite(LED1, HIGH);
  }
  if (valor_binario[1] == 1){
    digitalWrite(LED2, HIGH);
  }
  if (valor_binario[2] == 1){
    digitalWrite(LED3, HIGH);
  }
  if (valor_binario[3] == 1){
    digitalWrite(LED4, HIGH);
  }
  
  
  // fazer com que cada valor tenha alguma nota musical para ser tocado no buzzer
  int buzzerValue;
  switch (analogValue){
    case 0:
      buzzerValue = NOTE_G3;
    case 1:
      buzzerValue = NOTE_E3;
    case 2:
      buzzerValue = NOTE_A3;
    case 3:
      buzzerValue = NOTE_B3;
    case 4:
      buzzerValue = NOTE_C3;
    case 5:
      buzzerValue = NOTE_D3;
    case 6:
      buzzerValue = NOTE_F3;
    case 7:
      buzzerValue = NOTE_G2;
    case 8:
      buzzerValue = NOTE_A2;
    case 9:
      buzzerValue = NOTE_B2;
    case 10:
      buzzerValue = NOTE_C2;
    case 11:
      buzzerValue = NOTE_D2;
    case 12:
      buzzerValue = NOTE_E2;
    case 13:
      buzzerValue = NOTE_F2;
    case 14:
      buzzerValue = NOTE_A4;
    case 15:
      buzzerValue = NOTE_B4;
  }

  //dar um feadback sonoro
  tone(buzzer, buzzerValue);

  // desligar as luzes e o buzzer
  delay(1500); 
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  noTone(buzzer);

  //colocar o valor dentro de um array
  x = x+1;
  lista[x][0] = valor_binario[0];
  lista[x][1] = valor_binario[1];
  lista[x][2] = valor_binario[2];
  lista[x][3] = valor_binario[3];
  
  // colocar o valor da frequencia buzzer dentro de um array
  lista_sons [x] = buzzerValue;


}





void loop() {
  //para armazenar o valor
  if (analogRead(setbtn) == LOW){
  trans_binary();
  }
  // para mostrar e limpar o valor
  if (analogRead(playbtn) == LOW){
  mostrar();
  limpar();
  }
  
  delay(500);




}
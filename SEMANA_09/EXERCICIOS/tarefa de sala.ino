#include <WiFi.h>
#include <string>
#include <HTTPClient.h>
#include <Wire.h>
#include <iostream>
#include <ArduinoJson.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bits/stdc++.h>
#include <set>
using namespace std;
// // internet/wifi config
const char* ssid = "Inteli-COLLEGE";
const char* password = "QazWsx@123";
//server routes
const char* updateRoute = "https://ur524n-3000.preview.csb.app/teobaldo";
// time interval 5 seconds (5000)
unsigned long lastTime = 0;
unsigned long timerDelay = 2000;
bool movimento = 0;  //1=TRUE, 0=FALSE
string alfabeto = "abcdefghijklmnopqrstuvwxyz";
string mensagem = "guto";
string mensagem_criptografada;
string resultado = "";
void criptografia(){
  for (int i = 0; i < mensagem.length(); i++) {
    for (int j = 0; j < 26; j++) {
        if (mensagem[i] == alfabeto[j]){
            mensagem_criptografada[i] = alfabeto[j + 1];
        }
        
    }
  }
  for (int i = 0; i < mensagem.length(); i++) {
      resultado += mensagem_criptografada[i];
  }
}
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  criptografia();
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;
      http.begin(updateRoute);
      http.addHeader("Content-Type", "application/json");
      // Envio de dados do acelerometro para o servidor em JSON
      StaticJsonDocument<200>
        doc;
      doc["Nome do Aluno"] = "Luiz Augusto Ferreira";
      doc["Turma"] = "3";
      doc["Grupo"] = "3";
      doc["Mensagem de Texto"] = mensagem;
      doc["Criptografada"] = resultado;
      String requestBody;
      serializeJson(doc, requestBody);
      int httpResponseCode = http.POST(requestBody);
      if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        Serial.print("HTTP Response Body: ");
        Serial.println(response);
        deserializeJson(doc, response);
      }
      // Free resources
      http.end();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
void loop() {
}



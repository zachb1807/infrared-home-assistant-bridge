#include <IRremote.hpp>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>
#include "private_constants.h"

#define IR_RECEIVE_PIN 4

long lCode = 0;
long cCode = 0;
int repeat = 0;

HardwareSerial SerialPort2(2); // use UART2

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.println("Intializing Network");
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);  // Start the receiver
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Ready to receive IR commands.");
  SerialPort2.begin(15200, SERIAL_8N1, 16, 17);
}

void loop() {
  if (IrReceiver.decode()) {
    cCode = IrReceiver.decodedIRData.decodedRawData;
    
    if (cCode == 0) {
      Serial.println("Detected Repeat");
      SerialPort2.println("0");
    }
    else  {
      Serial.println(IrReceiver.decodedIRData.decodedRawData);
      SerialPort2.println(IrReceiver.decodedIRData.decodedRawData);
      lCode = cCode;
      
      repeat = 0;
      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        http.begin(client, serverURL);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", token);
        String httpRequestData = "{\"code\": \"" + String(IrReceiver.decodedIRData.decodedRawData) + "\"}";
        int httpResponseCode = http.POST(httpRequestData);
        http.end();

      } else {
        Serial.println("WiFi Disconnected");
      }
    }

    IrReceiver.resume();  // Enable receiving of the next value
  }
}

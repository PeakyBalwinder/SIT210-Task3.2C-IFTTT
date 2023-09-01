#include "arduino_secrets.h" 
#include <SPI.h>
#include <WiFiNINA.h>
int light;

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASSWORD;


WiFiClient client;


char   HOST_NAME[] = "maker.ifttt.com";

String PATH_NAME   = "/trigger/light_intensity/with/key/HzLUQ8bfByW0UZKx5gOeQCY7OgEvKh048fTBmXZhjV"; // EVENT-NAME and YOUR-KEY must be changed here.

String queryString = "?value1=57&value2=25";


void setup() {

  // WiFi connection initialization

  WiFi.begin(ssid, pass);


  Serial.begin(9600);

  while (!Serial);


  // connect to web server on port 80:

  if (client.connect(HOST_NAME, 80)) {

    // if connected:

    Serial.println("Connected to server");

  }

  else {// if not connected:

    Serial.println("connection failed");

  }

}


void loop() {

  light = analogRead(A4);
  Serial.println(light);
  if (light > 650) {


    // make a HTTP request:

    // send HTTP header

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");

    client.println("Host: " + String(HOST_NAME));

    client.println("Connection: close");

    client.println(); // end HTTP header



    while (client.connected()) {

      if (client.available()) {

        // reads incoming byte from the server and print it to serial monitor:

        char c = client.read();

        Serial.print(c);

      }

    }

    // the server's disconnected, stop the client:

    client.stop();

    Serial.println();

    Serial.println("Mail Sent successfully");

  }
  
  delay(1000);

}
#include <VirtualWire.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht (DHTPIN, DHTTYPE);

const int dataPin = 9;

String cadenaHT;

void setup() {
  //Inicializar el serial
  Serial.begin(9600);

    
  dht.begin();

  vw_setup(2000);
  vw_set_tx_pin(dataPin);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  Serial.print("Humedad: ");
  Serial.println(h);
  Serial.print("Temperatura: ");
  Serial.println(t);

  char envio [VW_MAX_MESSAGE_LEN];

  /*** Humedad ***/
  cadenaHT = "h" + String(h);

        
  cadenaHT.toCharArray(envio, sizeof(envio) );
  
  digitalWrite(pinLed, HIGH);
  vw_send((uint8_t *)envio, strlen(envio));
  Serial.println(envio);
  vw_wait_tx();

  /*** Humedad ***/
  cadenaHT = "t" + String(t);

        
  cadenaHT.toCharArray(envio, sizeof(envio) );
  
  digitalWrite(pinLed, HIGH);
  vw_send((uint8_t *)envio, strlen(envio));
  vw_wait_tx();
  Serial.println(envio);

  
  delay(50);
  
}

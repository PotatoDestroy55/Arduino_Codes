
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

LiquidCrystal_I2C lcd(0x3F, 16, 2);
DHT dht(DHTPIN, DHTTYPE);

const int pinRele = 3;
int activacion = 0;

void setup() {
  // Inicializar el serial para hacer las pruebas
  Serial.begin(9600);
  lcd.init();
  dht.begin();
  
  pinMode(pinRele, OUTPUT);  
}

void loop() {
  delay(1000);

  float h = dht.readHumidity(); 
  float t = dht.readTemperature();

  lcd.home();
  lcd.print("Humedad: ");
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.println("%");
  lcd.print(h);
  lcd.print ("%");

  lcd.setCursor(0,1);

  lcd.print ("Temp: ");
  lcd.print(t);
  lcd.print(" C");

  Serial.print("Temp: ");
  Serial.print(t);
  Serial.println(" C");
  
  if( t >= 24)
  {

    activacion += 1;
    digitalWrite(pinRele, HIGH);
        
  }else if( t < 24){
    activacion = 0;
    digitalWrite(pinRele, LOW);
  }  

  if(activacion == 1){
    lcd.clear();
    lcd.print("Encendiendo");
    lcd.setCursor(0,1);
    lcd.print("Ventilador");

    Serial.print("Encendiendo motor");

    for(int i = 0; i < 3; i++){
      lcd.noDisplay();
      delay(500);
      
    }

    lcd.clear();
  }
}

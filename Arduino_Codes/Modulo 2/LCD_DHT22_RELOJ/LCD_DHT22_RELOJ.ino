#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "RTClib.h"
#include "DHT.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define CIRCLE 0
#define DHTPIN 2
#define DHTTYPE DHT22


RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);

byte customChar [8] ={
B00100,
B01010,
B00100,
B00000,
B00000,
B00000,
B00000,
B00000
};

void setup() {
  rtc.begin();
  dht.begin();

  Serial.begin(9600);

  lcd.init();

}

void loop() {

  //Creación de los caracteres nuevos.
  lcd.createChar(CIRCLE, customChar);
  
  sensores();
  

}


void sensores(){
  DateTime fecha = rtc.now();

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.home();

  lcd.print(fecha.hour());
  lcd.print(":");
  lcd.print(fecha.minute());


  lcd.print("  ");
  
  lcd.print(fecha.day());
  lcd.print("/");
  lcd.print(fecha.month());
  lcd.print("/");
  lcd.print(fecha.year());
  
  Serial.print(fecha.day() + "/");
  Serial.print(fecha.month() + "/");
  Serial.println(fecha.year() + "/");
  
  lcd.setCursor(0,1);

  lcd.print("Hum:");
  lcd.print((int) h); 
  lcd.print ("%");


  
  lcd.print(" Temp:");
  lcd.print((int) t); 
  lcd.write(CIRCLE);

}
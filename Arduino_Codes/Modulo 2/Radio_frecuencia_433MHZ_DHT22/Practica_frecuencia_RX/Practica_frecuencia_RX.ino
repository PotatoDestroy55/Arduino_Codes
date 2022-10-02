#include <VirtualWire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16 ,2);

#define CIRCLE 0
#define TEMP 1
#define HUM 2

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

byte customChar2 [8] ={
B00100,
B01110,
B01110,
B01110,
B01110,
B11101,
B11101,
B01110
};

byte customChar3 [8] ={
B00100,
B00100,
B01110,
B01010,
B10001,
B10001,
B01110,
B00000
};


const int dataPin = 9;
float recHum = 0.0;
float recTemp = 0.0;
String datoCon =  "";


void setup() {
  // Inicialización del serial y la pantalla lcd.
  lcd.init();
  Serial.begin(9600);

//Impresión de los resultados.
lcd.print("Receptor Datos");
Serial.println("Receptor Datos");
lcd.setCursor(0,1);

lcd.print("Hum. y Temp.");
Serial.println("Hum. y Temp.");
delay(1500);

//Creación de los caracteres nuevos.
lcd.createChar(CIRCLE, customChar);
lcd.createChar(TEMP, customChar2);
lcd.createChar(HUM, customChar3);

vw_setup(2000);
vw_set_rx_pin(dataPin);
vw_rx_start();

}

void loop() {
  // put your main code here, to run repeatedly:
uint8_t receptor[VW_MAX_MESSAGE_LEN];
uint8_t receptorLen = VW_MAX_MESSAGE_LEN;


if(vw_get_message((uint8_t *)receptor, &receptorLen)){
  if((char)receptor[0] =='h'){
    for(int i =1; i < receptorLen; i++){
      datoCon.concat((char)receptor[i]);
    }
    recHum = datoCon.toFloat();
    Serial.println(datoCon);
    lcd.home();
    lcd.print("HUM: ");
    lcd.print(recHum);
    lcd.print(" % ");
    lcd.write(HUM);

  }else if((char)receptor[0]=='t'){
    for(int i=1; i < receptorLen; i++){
        datoCon.concat((char)receptor[i]);
    }  

    recTemp = datoCon.toFloat();

    lcd.setCursor(0,1);
    lcd.print("Temp: ");
    lcd.print(recTemp);
    lcd.print(" ");
    lcd.write(CIRCLE);
    lcd.print("C ");
    lcd.write(TEMP);
    }
    datoCon = "";
  } 
} 

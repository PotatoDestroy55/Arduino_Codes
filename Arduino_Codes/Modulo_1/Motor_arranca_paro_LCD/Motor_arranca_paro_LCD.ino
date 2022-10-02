//Practica de Arduino - Modulo 1 - Motor Arraca/Paro con display LCD
//importacion de librerias
#include<LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
//Declaracion de variables
const int pinBotonA=6;
const int pinBotonB=7;
const int pinMotor=9;

int contMotor=0;
int velocidad;

int estadoMotor;
int estadoParo;


void setup() {

  Serial.begin(9600);
  // Empezar a inicializar los dispositivos e imprimir en pantalla lo que hace el programa
  lcd.begin(16,2);
  lcd.print("Motor en paro");
  Serial.print("Motor en paro");
  lcd.setCursor(0,1);
  lcd.print("en espera...");
  Serial.println("en espera...");
  // Inicicializar los botones 
  pinMode(pinBotonA, INPUT);
  pinMode(pinBotonB, INPUT);
  pinMode(pinMotor, OUTPUT);

}

void loop() {
  estadoMotor= digitalRead(pinBotonB);
  Serial.println(estadoMotor);

  // Verificar cuando el boton del motor es presionado.
  if(estadoMotor== HIGH){
    delay(500);
    contMotor +=1;

    if(contMotor==1){
      lcd.clear();
      delay(50);
      lcd.print("Motor Girando");
      Serial.println("Motor girando");

      for(velocidad =0; velocidad <=100; velocidad++){
        analogWrite(pinMotor, velocidad);
        delay(50);

        lcd.setCursor(0,1);
        lcd.print(porcentaje(velocidad));
        Serial.println(velocidad);
        lcd.print("%");
      }
    }
   
    if(contMotor==2){
      lcd.clear();
      
      lcd.print("PRECAUCION PARO");
      Serial.println("Precaución paro del motor");
      lcd.setCursor(0,1);
      lcd.print("DEL MOTOR!");


      for(int i=0; i<3; i++){
        lcd.noDisplay();
        delay(400);

        lcd.display();
        delay(1500);
      }

      lcd.clear();
      
      lcd.print("Parando Motor");
      Serial.println("Parando el motor");

      for(velocidad=100; velocidad>=0; velocidad--){
        analogWrite(pinMotor, velocidad);
        delay(50);

        lcd.setCursor(0,1);
        lcd.print(porcentaje(velocidad));
        Serial.print(porcentaje(velocidad));
        Serial.println(" %");
        lcd.print("%");

        if(porcentaje(velocidad)>= 100){
          lcd.setCursor(3,1);
          lcd.print(" ");
        }else if(porcentaje(velocidad)<= 9){
          lcd.setCursor(2,1);
          lcd.print(" ");
        }

      }
        lcd.clear();

        lcd.print("Motor parado");
        Serial.println("Motor parado");
        lcd.setCursor(0,1);
        lcd.print("0%");
        Serial.println("0%");

        contMotor=0;

    }
  }

  estadoParo=digitalRead(pinBotonA);
  // Si se presiona el boton secundario iniciar paro de emergencia
  if(estadoParo==HIGH){
    if(contMotor != 0){
      analogWrite(pinMotor, 0);

      delay(500);
      lcd.clear();
      lcd.print(" PARO DE");
      lcd.setCursor(0,1);
      lcd.print(" EMERGENCIA!");
      Serial.println(" PARO DE EMERGENCIA ");
      delay(1000);

      contMotor=0;

      for(int i=0; i< 15; i++){
        lcd.scrollDisplayLeft();
        delay(250);
      }

      for(int i=0; i< 30; i++){
        lcd.scrollDisplayRight();
        delay(250);
      }

      for(int i=0; i< 15; i++){
        lcd.scrollDisplayLeft();
        delay(250);
      }
    }
  }
}
// Metodo que calcula el porcentaje de velocidad del motor, uso para impresion del mismo.
int porcentaje(int vel){
  int operacion=vel*100;
  int resultado = operacion/255;

  return resultado;
}
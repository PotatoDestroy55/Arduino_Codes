#include <stdio.h>

const int pinLed = 12;
const int pinBuzzer = 11;
const int pinLDR = A0;
int valorLDR = 0;
int calorLDR = 0;

void sonido(){
	digitalWrite (pinBuzzer, HIGH);
	digitalWrite (pinLed, HIGH);
	delay (1000);
	digitalWrite (pinBuzzer, LOW);
	delay(500);
  
}

void setup() {
  // put your setup code here, to run once:
  pinMode	(pinLed, OUTPUT);
	pinMode (pinBuzzer, OUTPUT);
	pinMode (pinLDR, INPUT);

	//digitalWrite(pinLaser, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  valorLDR =  analogRead(pinLDR);

	if(valorLDR <= 100){
		
		for(int i = 1; i <= 3; i++){
      
			

		}

	}
  

}

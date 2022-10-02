

// Conseguir el pin en que estan conectado los dispositivos.
const int pinBoton = 2 ;
const int pinMotor = 3;
const int pinLed = 4;

int velocidad;
boolean encendido = false;
void setup() {
  // Inicializar los botones y el motor
  pinMode(pinBoton, INPUT);
  pinMode(pinMotor, OUTPUT);
  pinMode(pinLed, OUTPUT);

  Serial.begin(9600);

  // Empezar a pedir instrucciones
  Serial.println("\n\nPresione el boton");

}

void loop() {


  while(digitalRead(pinBoton)==LOW);
  // Encender el motor al presionar el boton
  if(encendido == false){
    Serial.println("Arrancando Motor:");
    digitalWrite(pinLed, HIGH);

    for(velocidad = 0; velocidad <= 255; velocidad++){
      analogWrite(pinMotor, velocidad);
      delay(30);
      Serial.println(porcentaje(velocidad));
      Serial.print("%");
    }

    Serial.println("Motor arrancando al 100%");

    for(int i=1; i <=3; i++){
      estadoLed();
    }

    digitalWrite(pinLed, HIGH);
    encendido = true;

  }else{
    // Si es que se pasa el primer ciclo de encendido, entonces para el motor prodeduralmente.
    Serial.println("Parando motor:");
    for(velocidad = 255; velocidad >= 0; velocidad--){
      analogWrite(pinMotor, velocidad);
      delay(30);
      Serial.println(porcentaje(velocidad));
      Serial.print("%");
    }
    digitalWrite(pinLed, LOW);
    encendido = false;
  }

}
//Metodo que calcula el porcentaje de la velocidad
int porcentaje (int velocidad){
  int operacion = velocidad * 100;
  int resultado = operacion / 255;

  return resultado;
}

// Metodo que cambia el color del led, indicando el estado del motor.
void estadoLed(){
  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);
  delay(500);
}

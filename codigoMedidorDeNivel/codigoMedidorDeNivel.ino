#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

// Solenoide off, no flujo de agua

const uint8_t Trigger = A0;  // Pin digital A0 para el Trigger del sensor
const uint8_t Echo = A1;     // Pin digital A1 para el Echo del sensor

const uint8_t pinNeopixel = 3;
const uint8_t pinBoton = 8;
const uint8_t pinSolenoide = A2;

int distanciaTrigger;  // Valor inicial de distancia mínima
bool botonEstadoAnterior = HIGH;  // Estado anterior del botón

Adafruit_NeoPixel strip(1, pinNeopixel, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);  // Inicializamos la comunicación

  pinMode(Trigger, OUTPUT);    // Pin como salida
  pinMode(Echo, INPUT);        // Pin como entrada
  digitalWrite(Trigger, LOW);  // Inicializamos el pin con 0

  pinMode(pinSolenoide, OUTPUT);
  pinMode(pinBoton, INPUT_PULLUP);

  strip.begin();            // Inicializa el objeto NeoPixel
  strip.show();             // Apaga todos los píxeles
  strip.setBrightness(20);  // Ajusta el brillo al 20% (máximo 255)

  // Leer la distancia mínima almacenada en EEPROM
  distanciaTrigger = EEPROM.read(0);
  if (distanciaTrigger == 255) {  // Si no hay un valor válido almacenado
    distanciaTrigger = 5;         // Asignar un valor por defecto
  }
  Serial.print("Trigger almacenado: ");
  Serial.println(distanciaTrigger);
}

void loop() {

  long t;  // Tiempo que demora en llegar el eco
  long d;  // Distancia en centímetros

  // Enviar un pulso ultrasónico
  digitalWrite(Trigger, HIGH);
  delayMicroseconds(10);  // Enviamos un pulso de 10us
  digitalWrite(Trigger, LOW);

  t = pulseIn(Echo, HIGH);  // Obtenemos el ancho del pulso
  d = t / 59;               // Escalamos el tiempo a una distancia en cm

  Serial.print("Distancia: ");
  Serial.print(d);  // Enviamos serialmente el valor de la distancia
  Serial.println(" cm");

  // Detectar el cambio de estado del botón (flanco descendente)
  bool botonEstadoActual = digitalRead(pinBoton);
  if (botonEstadoAnterior == HIGH && botonEstadoActual == LOW) {
    // Guardar la distancia actual en la EEPROM
    EEPROM.write(0, d);
    distanciaTrigger = d;  // Actualizar la distancia mínima
    Serial.print("Distancia guardada en EEPROM: ");
    Serial.println(d);
    
    strip.setPixelColor(0, strip.Color(0, 255, 0)); //verde para indicar que se guardó la distancia
    strip.show();
    delay(2500);
    strip.clear();
    strip.show();
  }
  botonEstadoAnterior = botonEstadoActual;

  // mucha distancia, nivel bajo de agua, 
  if (d >= distanciaTrigger) {
    digitalWrite(pinSolenoide, HIGH); // Abre el flujo de agua
    strip.setPixelColor(0, strip.Color(50, 45, 0)); // amarillo
  } else {
    digitalWrite(pinSolenoide, LOW);  // Cierra el flujo de agua
    strip.setPixelColor(0, strip.Color(0, 0, 25)); // azul
  }
  strip.show();

  delay(500);  // Hacemos una pausa de 100ms
}

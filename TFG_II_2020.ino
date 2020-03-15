// Nombre: TFG_II_2020.ino 
// Autor: Jorge Navarro Ordoñez
// Fecha: 15/03/2020
// Versión: 1.0
// Descripcion: Este fichero implementa un juego Arduino para corrección de la dislexia 
//              mediante aprendizaje por repeticiçon de los cuatro puntos cardinales

// Bibliotecas incluidas en el proyecto
#include<stdlib.h>
#include<LiquidCrystal.h>

// Definicion de los LEDs según su orientación
#define LED_UP
#define LED_DOWN
#define LED_RIGHT
#define LED_LEFT

// Definicion de los LEDs de comprobación
#define LED_RED
#define LED_GREEN

// Definición de los botones asociados a los LEDs
#define BUTTON_UP
#define BUTTON_DOWN
#define BUTTON_RIGHT
#define BUTTON_LEFT

// Definición de los rangos de pin para asignar las luces
#define MIN_PIN
#define MAX_PIN

// Variables 
int nuevoPin = 0;
int lastPin = 0;
int value = 0;

// Nombre: setup 
// Autor: Jorge Navarro Ordoñez
// Fecha: 15/03/2020
// Versión: 1.0
// Descripcion: Inicialización de la placa Arduino MEGA 2560
void setup(){
  // Configuración de los pines de los LEDs (OUTPUT)
  pinMode(LED_UP, OUTPUT);
  pinMode(LED_DOWN, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // Configuración de los pines de los Botones (INPUT)
  pinMode(BUTTON_UP, INPUT);
  pinMode(BUTTON_DOWN, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  pinMode(BUTTON_LEFT, INPUT);

  // Configuración inicial del estado de los leds (apagados)
  digitalWrite(LED_UP, LOW);
  digitalWrite(LED_DOWN, LOW);
  digitalWrite(LED_RIGHT, LOW);
  digitalWrite(LED_LEFT, LOW);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void loop(){}

// Nombre: generarNumAleatorio
// Autor: Jorge Navarro Ordoñez
// Fecha: 15/03/2020
// Versión: 1.0
// Descripcion: genera un número aleatorio entre un rango inferior y superior
int generarNumAleatorio(int Inf, int Sup){
    int num = 0;  
    num = Inf + (int)(((Sup - Inf + 1.0) * rand()) / (RAND_MAX + 1.0)); 
    return num;
}

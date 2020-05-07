// Nombre: TFG_II_2020.ino 
// Autor: Jorge Navarro Ordoñez
// Fecha: 07/05/2020
// Versión: 1.2
// Descripcion: Este fichero implementa un programa que define un sistema para 
//              proporcionar herramientas de ayuda al tratamiento de la dislexia

// Bibliotecas incluidas en el proyecto
#include <stdlib.h>
#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>

// Definición de los pulsadores direccionales
#define BUTTON_UP 2
#define BUTTON_DOWN 3
#define BUTTON_RIGHT 4
#define BUTTON_LEFT 5

// Inicialización de la pantalla LCD con los pines asignados
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// Inicialización del teclado matricial 4x4
const byte COLUMNAS = 4;  // Cuatro columnas
const byte FILAS = 4;     // Cuatro filas

char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinesFila[FILAS] = {46, 47, 48, 49};
byte pinesColumna[COLUMNAS] = {50, 51, 52, 53};

Keypad teclado = Keypad(makeKeymap(teclas), pinesFila, pinesColumna, FILAS, COLUMNAS); 

// Variables globales


// Nombre: setup 
// Autor: Jorge Navarro Ordoñez
// Fecha: 07/05/2020
// Versión: 1.2
// Descripcion: Configuración inicial de la tarjeta Arduino
void setup(){
    // Configuración inicial de los pines de los Botones (INPUT)
    pinMode(BUTTON_UP, INPUT);
    pinMode(BUTTON_DOWN, INPUT);
    pinMode(BUTTON_RIGHT, INPUT);
    pinMode(BUTTON_LEFT, INPUT);
    
    // Configuración de columnas y filas del LCD 
    lcd.begin(16, 2);
   
}

// Nombre: loop
// Autor: Jorge Navarro Ordoñez
// Fecha: 07/05/2020
// Versión: 1.1
// Descripcion: Programa principal del sistema (se ejecuta infinitamente)
void loop(){
    // Pantalla de inicio

    // Leer de teclado (seleccionar modo de juego)

    // Iniciar juego


}

void juegoDispraxia(){
    // Genera una direccion aleatoria

    // Lee la respuesta del teclado

    // Si es correcta, vuelve de nuevo
    // Si es incorrecta, espera por un nuevo intento
}

void juegoDiscalculia(){
    // Genera dos números aleatorios

    // Calcula el resultado de la operacion

    // Lee la respuesta del teclado

    // Si es correcta, vuelve de nuevo
    // Si es incorrecto, espera por un nuevo intento
}





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

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

// Inicialización de la pantalla LCD con los pines asignados
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

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
    // Configuración de columnas y filas del LCD 
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("NUEVO JUEGO");
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

    juegoDiscalculia();
}

void juegoDispraxia(){
    // Genera una direccion aleatoria

    // Lee la respuesta del teclado

    // Si es correcta, vuelve de nuevo
    // Si es incorrecta, espera por un nuevo intento
}

void juegoDiscalculia(){
    lcd.setCursor(0,1);
    bool siguiente = false;
    bool acierto = false;
    // Bucle para jugar
    while(!siguiente){
      // Genera dos números aleatorios
      int n1 = generarNumAleatorio(0,50);
      int n2 = generarNumAleatorio(0,50);
      lcd.print(n1);
      lcd.print("+");
      lcd.print(n2);
      lcd.print("=");
      // Calcula el resultado de la operacion
      int res = n1 + n2;
      while(!acierto){
        char customKey = teclado.waitForKey();
        int num = String(customKey).toInt();
        // Si es correcta, vuelve de nuevo
        lcd.setCursor(4,1);
        lcd.print(num);
        if(num == res){
          delay(500);
          lcd.clear();
          lcd.print("CORRECTO");
          acierto = true;
          siguiente = true;
        }else{
          delay(500);
          lcd.clear();
          lcd.print("INCORRECTO");
          lcd.setCursor(0,1);
          lcd.print(n1);
          lcd.print("+");
          lcd.print(n2);
          lcd.print("=");
        }
      }
    }
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

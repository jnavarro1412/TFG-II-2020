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

#define ARRIBA 0
#define ABAJO 1
#define DERECHA 2
#define IZQUIERDA 3

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

// Inicialización del joystick direccionable
const int pinJoyX = A0;
const int pinJoyY = A1;

// Variables globales
// Control de la posición del joystick
int Xvalue = 0;
int Yvalue = 0;
// Juego Dispraxia
int direccion = 0;
int respuesta = -1;
// Juego Dislexia 
bool siguiente = false;
bool acierto = false;

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
    juegoDispraxia();
}

void juegoDispraxia(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ELIGE EL LADO");
    siguiente = false;
    acierto = false;
    while(!siguiente){
      // Genera una direccion aleatoria
      direccion = generarNumAleatorio(1, 1000) % 4;
      mostrarDireccion(direccion);
      while(!acierto){
        // Lee la respuesta del joystick
        Xvalue = analogRead(pinJoyX);
        delay(100); // Pausa entre lecturas
        Yvalue = analogRead(pinJoyY);
        // Comprobamos la lectura del joystick
        respuesta = obtenerDireccion(Xvalue, Yvalue);
        if(respuesta == direccion){
          delay(200);
          lcd.clear();
          lcd.print("CORRECTO");
          acierto  = true;
          siguiente = true;
          delay(1000);
        } 
      }
    }
}

void juegoDiscalculia(){
    lcd.setCursor(0,1);
    siguiente = false;
    acierto = false;
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

// Nombre: obtenerDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 09/05/2020
// Versión: 1.0
// Descripcion: obtiene una dirección a partir de la lectura de la posición del joystick
int obtenerDireccion(int valorX, int valorY){
   if(Xvalue == 0 && Yvalue < 750 && Yvalue > 250){
      return ARRIBA;
   }
   else if(Xvalue == 1023 && Yvalue < 750 && Yvalue > 250){
      return ABAJO;
   }
   else if(Yvalue == 0 && Xvalue < 750 && Xvalue > 250){
      return DERECHA;
   }
   else if(Yvalue == 1023 && Xvalue < 750 && Xvalue > 250){
      return IZQUIERDA;
   } 
   else{
      return -1;
   }
}

// Nombre: mostrarDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 09/05/2020
// Versión: 1.0
// Descripcion: muestra por la pantalla LCD la direccion generada
void mostrarDireccion(int direccion){
   lcd.setCursor(0,1);
   if(direccion == ARRIBA){
      lcd.print("ARRIBA");
   } else if(direccion == ABAJO){
      lcd.print("ABAJO");
   } else if(direccion == DERECHA){
      lcd.print("DERECHA");
   } else if(direccion == IZQUIERDA){
      lcd.print("IZQUIERDA");
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

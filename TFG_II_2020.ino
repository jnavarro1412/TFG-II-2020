// Nombre: TFG_II_2020.ino 
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.3
// Descripcion: Este fichero implementa un programa que define un sistema para 
//              proporcionar herramientas de ayuda al tratamiento de la dislexia

// Bibliotecas incluidas en el proyecto
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>

#define CENTRO 0 
#define ARRIBA 1
#define ABAJO 2
#define DERECHA 3
#define IZQUIERDA 4

#define SUMA 0
#define RESTA 1

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
const int buttonJoy = 13;

// Variables globales
int Xvalue = 0;
int Yvalue = 0;
int direccion = 0;
int respuesta = -1;
int intento = 0;
bool pulsado = false;
bool siguiente = false;
bool acierto = false;

// Nombre: setup 
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.3
// Descripcion: Configuración inicial de la tarjeta Arduino
void setup(){
    // Configuración de columnas y filas del LCD 
    lcd.begin(16, 2);
    // Configuración de la resistencia pull up del joystick
    pinMode(buttonJoy , INPUT_PULLUP);
    // Print a message to the LCD.
    lcd.print("NUEVO JUEGO");
}

// Nombre: loop
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.2
// Descripcion: Programa principal del sistema (se ejecuta infinitamente)
void loop(){
    // Pantalla de inicio
    mostarMenuInicial();
    // Leer de teclado (seleccionar modo de juego)
    char modoJuego = teclado.waitForKey();
    // Iniciar juego
    if(modoJuego == '1'){
        juegoDispraxia();
    } else if(modoJuego == '2'){
        juegoDiscalculia();
    }
}

// Nombre: juegoDispraxia
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.2
// Descripcion: función que define el juego contra la dispraxia
void juegoDispraxia(){
    intento = 0;
    while(intento < 10){
        siguiente = false;
        acierto = false;
        while(!siguiente){
            // Genera una direccion aleatoria
            direccion = generarNumAleatorio(1, 10000) % 5;
            mostrarDireccion(direccion);
            // Bucle mientras la respuesta no sea correcta
            while(!acierto){
                pulsado = digitalRead(buttonJoy);
                // Comprobamos la lectura del joystick
                respuesta = obtenerDireccion(Xvalue, Yvalue, pulsado);
                if(respuesta == direccion){
                    delay(200);
                    lcd.clear();
                    lcd.print("CORRECTO");
                    acierto  = true;
                    siguiente = true;
                    delay(1000);
                    intento++;
                }
            }
        }
    }
}

// Nombre: juegoDiscalculia
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.2
// Descripcion: función que define el juego contra la discalculia
void juegoDiscalculia(){
    intento = 0;
    while(intento < 10){
        siguiente = false;
        acierto = false;
        // Bucle para jugar
        while(!siguiente){
            char respuesta[] = {""};
            // Genera dos números aleatorios
            int n1 = generarNumAleatorio(20,49);
            int n2 = generarNumAleatorio(10,49);
            // Genera una operacion matemática (Suma - Resta)
            int operacion = generarNumAleatorio(1, 10000) % 2;
            // Muestra la operación generada
            mostrarOperacion(n1, n2, operacion);
            // Calcula el resultado de la operacion
            int resultado = calcularOperacion(n1, n2, operacion);
            // Mientras no se acierta la respuesta
            while(!acierto){
                // Lee dos números del teclado y los muestra por la pantalla LCD
                respuesta[0] = teclado.waitForKey();
                lcd.setCursor(6,1);
                lcd.print(respuesta[0]);
                respuesta[1] = teclado.waitForKey();
                lcd.setCursor(7,1);
                lcd.print(respuesta[1]);
                // Convierte la respuesta en un numero entero
                int num = String(respuesta).toInt();
                // Comprueba si la respuesta coincide con la correcta
                if(num == resultado){
                    delay(500);
                    lcd.clear();
                    lcd.print("CORRECTO");
                    acierto = true;
                    siguiente = true;
                    intento++;
                }
            }
        }
    }
}

// Nombre: obtenerDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.1
// Descripcion: obtiene una dirección a partir de la lectura de la posición del joystick
int obtenerDireccion(int Xvalue, int Yvalue, bool pulsado){
    // Lee la respuesta del joystick
    Xvalue = analogRead(pinJoyX);
    delay(100); // Pausa entre lecturas
    Yvalue = analogRead(pinJoyY);
    pulsado = digitalRead(buttonJoy);

    // Determina si el joystick apunta hacia arriba
    if(Xvalue == 0 && Yvalue < 750 && Yvalue > 250){
        return ARRIBA;
    }
    // Determina si el joystick apunta hacia abajo
    else if(Xvalue == 1023 && Yvalue < 750 && Yvalue > 250){
        return ABAJO;
    }
    // Determina si el joystick apunta hacia el lado derecho
    else if(Yvalue == 0 && Xvalue < 750 && Xvalue > 250){
        return DERECHA;
    }
    // Determina si el joystick apunta hacia el lado izquierdo
    else if(Yvalue == 1023 && Xvalue < 750 && Xvalue > 250){
        return IZQUIERDA;
    } 
    // Determina si el joystick está centrado y pulsado
    else if(Xvalue < 520 && Xvalue > 500 && Yvalue < 520 && Yvalue > 500 && !pulsado){
        return CENTRO;
    }
    else{
        return -1;
    }
}

// Nombre: calcularOperacion
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.0
// Descripcion: calcula el resultado de la operacion generada
int calcularOperacion(int op1, int op2, int operacion){
    if(operacion == SUMA){
        return (op1 + op2);
    } else if(operacion == RESTA){
        return (op1 - op2);
    } else{
        return -1;
    }
}

// Nombre: mostrarOperacion
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.0
// Descripcion: muestra por la pantalla LCD la operación generada
void mostrarOperacion(int num1, int num2, int op){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULAR");
    lcd.setCursor(0,1);
    lcd.print(num1);
    lcd.setCursor(2,1);
    lcd.print(op);
    lcd.setCursor(3,1);
    lcd.print(num2);
    lcd.setCursor(5,1);
    lcd.print("=");
}

// Nombre: mostrarDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 09/05/2020
// Versión: 1.0
// Descripcion: muestra por la pantalla LCD la direccion generada
void mostrarDireccion(int direccion){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("ELIGE EL LADO");
   lcd.setCursor(0,1);
   if(direccion == ARRIBA){
      lcd.print("ARRIBA");
   } else if(direccion == ABAJO){
      lcd.print("ABAJO");
   } else if(direccion == DERECHA){
      lcd.print("DERECHA");
   } else if(direccion == IZQUIERDA){
      lcd.print("IZQUIERDA");
   } else if(direccion == CENTRO){
      lcd.print("CENTRO");
   }
}

// Nombre: mostrarMenuInicial
// Autor: Jorge Navarro Ordoñez
// Fecha: 10/05/2020
// Versión: 1.0
// Descripcion: muestra el menú principal en la pantalla LCD
void mostarMenuInicial(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("1 - JUEGO 1");
    lcd.setCursor(0,1);
    lcd.print("2 - JUEGO 2");
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

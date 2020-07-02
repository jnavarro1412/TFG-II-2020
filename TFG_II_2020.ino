// Nombre: TFG_II_2020.ino 
// Autor: Jorge Navarro Ordoñez
// Fecha: 21/06/2020
// Versión: 2.0
// Descripcion: Este fichero implementa un programa que define un sistema para 
//              proporcionar herramientas de ayuda al tratamiento de la dislexia

// Bibliotecas incluidas en el proyecto
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <LiquidCrystal.h>
#include <Key.h>
#include <Keypad.h>

// Define los puntos para la orientacion
#define CENTRO           0 
#define ARRIBA           1
#define DERECHA          2
#define ABAJO            3
#define IZQUIERDA        4

// Define operaciones matemáticas
#define SUMA            0
#define RESTA           1
#define MULTIPLICACION  2

// Inicialización de la pantalla LCD con los pines asignados
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

// Inicialización del teclado matricial 4x4
const byte COLUMNAS = 4;  // Cuatro columnas
const byte FILAS    = 4;  // Cuatro filas

// Distribución de caracteres en las teclas 
char teclas[FILAS][COLUMNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Inicialización de pines para Filas y Columnas
byte pinesFila[FILAS] = {46, 47, 48, 49};
byte pinesColumna[COLUMNAS] = {50, 51, 52, 53};

// Instanciación del teclado
Keypad teclado = Keypad(makeKeymap(teclas), pinesFila, pinesColumna, FILAS, COLUMNAS); 

// Inicialización del joystick direccionable
const int pinJoyX   = A0;
const int pinJoyY   = A1;
const int buttonJoy = 13;

// Variables globales
int   Xvalue      = 0;
int   Yvalue      = 0;
int   direccion   = 0;
int   respuesta   = -1;
int   ronda       = 0;
bool  pulsado     = false;
bool  siguiente   = false;
bool  acierto     = false;
int   puntosTotal = 0;

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
    delay(3000);
    // Pantalla de inicio
    mostarMenuInicial();
    // Leer de teclado (seleccionar modo de juego)
    char modoJuego = teclado.waitForKey();
    // Iniciar juego en función del juego seleccionado
    if(modoJuego == '1'){
        juegoDispraxia();   // Inicia el juego para la Dispraxia
    } else if(modoJuego == '2'){
        juegoDiscalculia(); // Inicia el juego para la Discalculia
    }
}

// Nombre: juegoDispraxia
// Autor: Jorge Navarro Ordoñez
// Fecha: 21/06/2020
// Versión: 1.5
// Descripcion: función que define el juego contra la dispraxia
void juegoDispraxia(){
    ronda = 0;
    // 10 rondas de juego
    while(ronda < 10){
        siguiente = false;
        acierto = false;
        // Bucle para jugar
        while(!siguiente){
            // Genera una direccion aleatoria
            direccion = (int)((millis() * generarNumAleatorio(1, 10000)) % 5);
            mostrarDireccion(direccion);
            // Bucle mientras la respuesta no sea correcta
            while(!acierto){
                // Comprobamos la lectura del joystick
                respuesta = obtenerDireccion();
                // Si la respuesta coindice se suman puntos y avanza
                if(respuesta == direccion){
                    delay(200);
                    lcd.clear();
                    lcd.print("CORRECTO");
                    lcd.setCursor(0,1);
                    lcd.print("+10 PUNTOS");
                    puntosTotal += 10;
                    acierto  = true;
                    siguiente = true;
                    delay(1000);
                    ronda++;
                }
            }
        }
    }
    // Muestra la puntuación total acumulada
    mostrarPuntuacion();
}

// Nombre: juegoDiscalculia
// Autor: Jorge Navarro Ordoñez
// Fecha: 24/05/2020
// Versión: 1.4
// Descripcion: función que define el juego contra la discalculia
void juegoDiscalculia(){
    ronda = 0;
    // 10 rondas de juego
    while(ronda < 10){
        int puntos = 10;
        siguiente = false;
        acierto = false;
        // Bucle para jugar
        while(!siguiente){
            int n1 = 0;
            int n2 = 0;
            char respuesta[] = {""};
            // Genera una operacion matemática (Suma - Resta - Multiplicacion)
            int operacion = generarNumAleatorio(1, 10000) % 3;
            // Genera dos números aleatorios en función de la operacion
            if(operacion == SUMA){
                n1 = generarNumAleatorio(5, 25);
                n2 = generarNumAleatorio(5, 25);
            } else if(operacion == RESTA){
                n1 = generarNumAleatorio(21, 49);
                n2 = generarNumAleatorio(1, 20);
            } else if(operacion == MULTIPLICACION){
                n1 = generarNumAleatorio(1, 9);
                n2 = generarNumAleatorio(1, 9);
            }
            // Muestra la operación generada
            mostrarOperacion(n1, n2, operacion);
            // Calcula el resultado de la operacion
            int resultado = calcularOperacion(n1, n2, operacion);
            // Mientras no se acierta la respuesta
            while(!acierto){
                // Lee dos números del teclado y los muestra por la pantalla LCD
                respuesta[0] = teclado.waitForKey();
                // Imprime la respuesta de la suma
                if(operacion == SUMA || operacion == RESTA){
                    lcd.setCursor(7,1);
                    lcd.print(respuesta[0]);
                    respuesta[1] = teclado.waitForKey();
                    lcd.setCursor(8,1);
                    lcd.print(respuesta[1]);
                }
                // Imprime la respuesta de la multiplicacion
                else if(operacion == MULTIPLICACION){
                    lcd.setCursor(5,1);
                    lcd.print(respuesta[0]);
                    respuesta[1] = teclado.waitForKey();
                    lcd.setCursor(6,1);
                    lcd.print(respuesta[1]);
                }
                // Convierte la respuesta en un numero entero
                int num = String(respuesta).toInt();
                // Comprueba si la respuesta coincide con la correcta
                if(num == resultado){
                    delay(500);
                    lcd.clear();
                    lcd.print("CORRECTO");
                    lcd.setCursor(0,1);
                    lcd.print("+");
                    lcd.print(puntos);
                    lcd.print(" PUNTOS");
                    puntosTotal += puntos;
                    acierto = true;
                    siguiente = true;
                    delay(1000);
                    ronda++;
                } else{
                    delay(1000);
                    // Limpia la pantalla para dejar espacio a la nueva respuesta
                    if(operacion == SUMA || operacion == RESTA){
                        lcd.setCursor(7,1);
                    } else if(operacion == MULTIPLICACION){
                        lcd.setCursor(5,1);
                    }
                    lcd.print("  ");
                    if(puntos > 0){
                        puntos -= 5;
                    }
                }
            }
        }
    }
    // Muesta la puntuación total acumulada
    mostrarPuntuacion();
}

// Nombre: obtenerDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 02/06/2020
// Versión: 1.3
// Descripcion: obtiene una dirección a partir de la lectura de la posición del joystick
int obtenerDireccion(){
    int   Xvalue      = 0;
    int   Yvalue      = 0;
    int   direccion   = 0;
    // Lee la respuesta del joystick
    Xvalue = analogRead(pinJoyX);
    delay(100); // Pausa entre lecturas
    Yvalue = analogRead(pinJoyY);
    pulsado = digitalRead(buttonJoy);

    // Determina si el joystick apunta hacia arriba
    if(Yvalue == 0 && Xvalue < 750 && Xvalue > 250){
        return ARRIBA;
    }
    // Determina si el joystick apunta hacia abajo
    else if(Yvalue == 1023 && Xvalue < 750 && Xvalue > 250){
        return ABAJO;
    }
    // Determina si el joystick apunta hacia el lado derecho
    else if(Xvalue == 0 && Yvalue < 750 && Yvalue > 250){
        return IZQUIERDA;
    }
    // Determina si el joystick apunta hacia el lado izquierdo
    else if(Xvalue == 1023 && Yvalue < 750 && Yvalue > 250){
        return DERECHA;
    } 
    // Determina si el joystick está centrado y pulsado
    else if(Xvalue < 520 && Xvalue > 500 && Yvalue < 520 && Yvalue > 500 && !pulsado){
        return CENTRO;
    }
    // En otro caso devuelve -1 
    else{
        return -1;
    }
}

// Nombre: calcularOperacion
// Autor: Jorge Navarro Ordoñez
// Fecha: 24/05/2020
// Versión: 1.1
// Descripcion: calcula el resultado de la operacion generada
int calcularOperacion(int op1, int op2, int operacion){
    // Calcula la suma
    if(operacion == SUMA){
        return (op1 + op2);
    }
    // Calcula la resta 
    else if(operacion == RESTA){
        return (op1 - op2);
    } 
    // Calcula la multiplicacion
    else if(operacion == MULTIPLICACION){
        return (op1 * op2); 
    }
    // Devuelve -1 si la operacion no existe
    else{
        return -1;
    }
}

// Nombre: mostrarOperacion
// Autor: Jorge Navarro Ordoñez
// Fecha: 24/05/2020
// Versión: 1.2
// Descripcion: muestra por la pantalla LCD la operación generada
void mostrarOperacion(int num1, int num2, int op){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("CALCULAR");
    lcd.setCursor(0,1);
    // Imprime las operaciones de suma y resta
    if(op == SUMA || op == RESTA){
        lcd.print(num1);
        lcd.setCursor(2,1);
        // Símbolo de la suma
        if(op == SUMA){
            lcd.print("+");
        } 
        // Símbolo de la resta
        else if(op == RESTA){
            lcd.print("-");
        }
        lcd.setCursor(3,1);
        lcd.print(num2);
        lcd.setCursor(5,1);
        lcd.print("=");
    }
    // Imprime la operacion de multiplicación
    else if(op == MULTIPLICACION){
        lcd.print(num1);
        lcd.setCursor(1,1);
        // Símbolo de la multiplicación
        lcd.print("x");
        lcd.setCursor(2,1);
        lcd.print(num2);
        lcd.setCursor(4,1);
        lcd.print("=");
    }
}

// Nombre: mostrarDireccion
// Autor: Jorge Navarro Ordoñez
// Fecha: 24/05/2020
// Versión: 1.1
// Descripcion: muestra por la pantalla LCD la direccion generada
void mostrarDireccion(int direccion){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("ELIGE EL LADO");
   lcd.setCursor(0,1);
   // Dirección: ARRIBA
   if(direccion == ARRIBA){
      lcd.print("ARRIBA");
   }
   // Dirección: DERECHA
   else if(direccion == DERECHA){
      lcd.print("DERECHA");
   } 
   // Dirección: ABAJO
   else if(direccion == ABAJO){
      lcd.print("ABAJO");
   } 
   // Dirección: IZQUIERDA
   else if(direccion == IZQUIERDA){
      lcd.print("IZQUIERDA");
   } 
   // Dirección: CENTRO
   else if(direccion == CENTRO){
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
    lcd.print("1 - DIRECCIONES");
    lcd.setCursor(0,1);
    lcd.print("2 - CALCULAR");
}

// Nombre: mostrarPuntuacion
// Autor: Jorge Navarro Ordoñez
// Fecha: 11/05/2020
// Versión: 1.0
// Descripcion: muestra la puntuación total de la partida
void mostrarPuntuacion(){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TOTAL PUNTOS:");
    lcd.print(puntosTotal);
    delay(5000);
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

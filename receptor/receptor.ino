#include "Receptor.h"

Receptor * r;

void funcionDePrueba(bool b){
  if(b)
    Serial.println("funcion de prueba encendido");
  else
    Serial.println("funcion de prueba apagado");
}

void setup(){
  
  Serial.begin(9600);
      
  // definir aca los punteros a las funciones que quiero que el receptor 
  // haga: Modo de uso: la funcion a la que debe apuntar debe tener un 
  // parametro bool que indica si el boton fue apretado o levantado
  // si se desea que el boton no haga ninguna accion se comenta la linea
  // puesto que el for de arriba pone los punteros en 0 y mas abajo se sabe
  // que si el puntero es cero no se ejecuta nada
  func_ptr ptr_funciones[10];
  ptr_funciones[L1] = funcionDePrueba;
  ptr_funciones[R1] = funcionDePrueba;
  ptr_funciones[CIRCULO] = funcionDePrueba;
  ptr_funciones[EQUIS] = funcionDePrueba;
  ptr_funciones[CUADRADO] = funcionDePrueba;
  ptr_funciones[TRIANGULO] = funcionDePrueba;
  ptr_funciones[ARRIBA] = funcionDePrueba;
  ptr_funciones[DERECHA] = funcionDePrueba;
  ptr_funciones[ABAJO] = funcionDePrueba;
  ptr_funciones[IZQUIERDA] = funcionDePrueba;
  
  r = new Receptor(ptr_funciones);  
}

void loop(){
  r->loop();
}

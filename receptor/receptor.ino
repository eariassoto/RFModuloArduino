// receptor.ino
//
// Ejemplo que recibe una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

// doc del buffer de entrada: arreglo de 8 caracteres que corresponden a los
// botones
// L1, R1, CIRCULO, EQUIS, CUADRADO, TRIANGULO, MOVIMIENTO, TIPO_DE_MOVIMIENTO
// para los primeros 7 '0' significa apagado y '1' presionado
// el ultimo caracter va de 0-3 que respectivamente indican
// ARRIBA, DERECHA, ABAJO, IZQUIERDA

#include "VirtualWire.h"

#define L1        0
#define R1        1
#define CIRCULO   2
#define EQUIS     3
#define CUADRADO  4
#define TRIANGULO 5
#define MOV       6
#define TIPO_MOV  7

#define ARRIBA    6
#define DERECHA   7
#define ABAJO     8
#define IZQUIERDA 9



// definimos los buffers para los datos
uint8_t buf_ent[VW_MAX_MESSAGE_LEN]; 
uint8_t buflen = VW_MAX_MESSAGE_LEN; 
int i; // contador del for

uint8_t buf_loc[8];

typedef void (*func_ptr)( bool );
func_ptr ptr_funciones[10];

void funcionDePrueba(bool b){
  if(b)
    Serial.println("funcion de prueba encendido");
  else
    Serial.println("funcion de prueba apagado");
}

void setup(){
  // pin 7 en el data del receptor
  
  Serial.begin(9600);
  // mensaje para saber que todo esta bien
  Serial.println("inicios"); 
  
  // Configuramos con la misma frecuencia que la del transmisor
  vw_setup(2000);	 
  vw_rx_start();
  
  // limpio la entrada local
  for(int i = 0; i<8; i++)
    buf_loc[i] = '0';
  
  // limpio los punteros a las funciones
  for(int j = 0; j<10; j++)
    ptr_funciones[j] = 0;
      
  // definir aca los punteros a las funciones que quiero que el receptor 
  // haga: Modo de uso: la funcion a la que debe apuntar debe tener un 
  // parametro bool que indica si el boton fue apretado o levantado
  // si se desea que el boton no haga ninguna accion se comenta la linea
  // puesto que el for de arriba pone los punteros en 0 y mas abajo se sabe
  // que si el puntero es cero no se ejecuta nada

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
}

void ejecutarComando(int btn){
  int indice = btn;
  if(btn == 6){
    // botones de movimiento

    if(buf_ent[7] == 0x6e){
      // debo apagar lo ultimo que hice
      indice += buf_loc[7]-'0';
    }else{
      // debo encender lo primero
      indice += buf_ent[7]-'0';
    }
  }
  if(ptr_funciones[indice]){
    // si tenemos funcion que ejecutar
    if(buf_ent[btn] == '0'){
      ptr_funciones[indice](false);
    }else{
      ptr_funciones[indice](true);
    }
  }
}

void revisarCambios(){
  // ejecuto acciones nuevas solo si hay un cambio
  // en los botones
  for(int i = 0; i<7; i++)
    if(buf_loc[i] != buf_ent[i])
      ejecutarComando(i);
}

void copiarBuffer(){
  // copia el bufer local a la refencia interna, esto
  // para notar los cambios de estado a estado
  for(int i = 0; i<8; i++)
    buf_loc[i] = buf_ent[i];
}

void loop(){
  
  // si el dispositivo recibio algo
  if (vw_get_message(buf_ent, &buflen)){
    revisarCambios();
    copiarBuffer();
  }
}

// transmisor.ino
//
// Ejemplo que transmite una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

#include "VirtualWire.h"
#define LED 3

#define CIRCULO   8
#define EQUIS     7
#define CUADRADO  6
#define TRIANGULO 5

#define L1        4
#define R1        13

#define IZQUIERDA 9
#define ABAJO     10
#define DERECHA   11
#define ARRIBA    12
#define NELEMS(x)  (sizeof(x) / sizeof(x[0]))

const int pinBoton[6] = {L1, R1, CIRCULO, EQUIS, CUADRADO, TRIANGULO};
const int pinMovimiento[4] = {ARRIBA, DERECHA, ABAJO, IZQUIERDA};

bool hayCambio;
bool estadoBoton[6];
bool estadoMovimiento;

int hayComando;
int seleccionMovimiento;

char *buff = "0000000n";

void setup(){
  // pin 2 va al data del transmisor
  Serial.begin(9600);
  // Configurar el modulo para que transmita a 2000 bits por segundo 
  // hace mas extenso el rango de alcance
  vw_setup(2000);
  
  for(int i = 0; i < NELEMS(pinBoton); i++){
    pinMode(pinBoton[i], INPUT);
    estadoBoton[i] = false;
  }
   
  for(int i = 0; i < NELEMS(pinMovimiento); i++)
    pinMode(pinMovimiento[i], INPUT);
    
  hayComando = 0;
  hayCambio = false;
  
  // led para indicar el envio de datos
  pinMode(LED, OUTPUT);	 	 
}

void enviarHilera(char* buf){
  vw_send((uint8_t *)buf, strlen(buf));  
  // espera que la transmision termine
  vw_wait_tx();
}  

void revisarEstadoBotones(){
  for(int i = 0; i < NELEMS(pinBoton); i++){
    if(digitalRead(pinBoton[i]) == LOW){ // se presiono el boton i
      if(estadoBoton[i] == false){       // primera vez
        hayCambio = true;
        estadoBoton[i] = true;
        hayComando++;
      }
    }else{                               // boton sin presionar
      if(estadoBoton[i] == true){        // estaba presionado
        hayCambio = true;
        estadoBoton[i] = false;
        hayComando--;
      }
    }
  }
}

void revisarEstadoMovimientos(){
  for(int i = 0; i < NELEMS(pinMovimiento); i++){
    if(digitalRead(pinMovimiento[i]) == LOW){
      if(!estadoMovimiento){
        hayCambio = true;
        seleccionMovimiento = i;
        estadoMovimiento = true;
        hayComando++;
      }
    }else{
      if(estadoMovimiento && seleccionMovimiento == i){
        hayCambio = true;
        estadoMovimiento = false;
        hayComando--;
      }
    }
  }
}

void actualizarLed(){
  if(hayComando > 0)
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);
}

void revisarCambioGeneral(){
  if(hayCambio){
    for(int i = 0; i < NELEMS(estadoBoton); i++){
      if(estadoBoton[i]){
        buff[i] = '1';
      }else{
         buff[i] = '0';
      }
    }
    if(estadoMovimiento){
      buff[6] = '1';
      buff[7] = 48+seleccionMovimiento;
    }else{
      buff[6] = '0';
      buff[7] = 'n';
    }
    hayCambio = false;
  }
}

void loop(){
  revisarEstadoBotones();
  revisarEstadoMovimientos();
  
  actualizarLed();

  revisarCambioGeneral();
  enviarHilera(buff);
}

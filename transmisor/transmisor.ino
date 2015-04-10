// transmisor.ino
//
// Ejemplo que transmite una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

#include "VirtualWire.h"
#define LED 13

void setup(){
  // pin 12 va al data del transmisor
  
  // Configurar el modulo para que transmita a 2000 bits por segundo 
  // hace mas extenso el rango de alcance
  vw_setup(2000);
  
  // led para probar la duracion de envio de datos
  pinMode(LED, OUTPUT);	 	 
}

void loop(){
  // mensaje que queremos enviar
  const char *buf = "hola mundo";

  // encendemos el led
  digitalWrite(LED, HIGH); 
  
  vw_send((uint8_t *)buf, strlen(buf));
  
  // espera que la transmision termine
  vw_wait_tx(); 
  
  // apagamos el led
  digitalWrite(LED, LOW);
  
  // tiempo de espera entre envio y envio
  delay(200); 
}

// transmisor.ino
//
// Ejemplo que transmite una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

#include "VirtualWire.h"

void setup(){
  
  // Configurar el modulo para que transmita a 2000 bits por segundo hace ms extenso el rango de alcance
  vw_setup(2000);
  
  // led para probar la duracion de envio de datos
  pinMode(8, OUTPUT);	 	 
}

void loop(){
  // mensaje que queremos enviar
  const char *buf = "prueba";

  // encendemos el led
  digitalWrite(8, HIGH); 
  
  vw_send((uint8_t *)buf, strlen(buf));
  
  // espera que la transmision termine
  vw_wait_tx(); 
  
  // apagamos el led
  digitalWrite(8, LOW);
  delay(200); 
}

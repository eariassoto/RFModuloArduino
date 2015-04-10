// receptor.ino
//
// Ejemplo que recibe una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

#include "VirtualWire.h"

// definimos los buffers para los datos
uint8_t buf[VW_MAX_MESSAGE_LEN]; 
uint8_t buflen = VW_MAX_MESSAGE_LEN; 
  
  
void setup(){
  // pin 11 en el data del receptor
  
  Serial.begin(9600);
  // mensaje para saber que todo esta bien
  Serial.println("inicio"); 
  
  // led de control
  pinMode(8, OUTPUT);
  
  // Configuramos con la misma frecuencia que la del transmisor
  vw_setup(2000);	 
  vw_rx_start();
}

void loop(){
  
  // si el dispositivo recibio algo
  if (vw_get_message(buf, &buflen)){
    int i;
    // encendemos el led al iniciar la lectura
    digitalWrite(8, HIGH); 
    
    Serial.print("Recibi: ");
    for (i = 0; i < buflen; i++){
      Serial.print(buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println("");
    
    //apagamos el led al terminar
    digitalWrite(8, LOW); 
  }
}

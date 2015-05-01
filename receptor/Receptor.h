// receptor.h
//
// Ejemplo que recibe una hilera de caracteres usando la 
// biblioteca VirtualWire.h y un transmisor de frecuencia de radio
// 
// Mas info de VirtualWire en http://www.airspayce.com/mikem/arduino/VirtualWire/
// 2015 Emmanuel Arias ariassotoemmanuel@gmail.com 

#ifndef RECEPTOR_H_
#define RECEPTOR_H_
#include "VirtualWire.h"

typedef void (*func_ptr)( bool );
typedef enum {L1=0,R1=1,CIRCULO=2,EQUIS=3,CUADRADO=4,TRIANGULO=5,ARRIBA=6,DERECHA=7,ABAJO=8,IZQUIERDA=9} tipo_boton;
class Receptor{

  public:
  Receptor(func_ptr*);
  void loop();
  
  private:
  uint8_t buflen = VW_MAX_MESSAGE_LEN; 
  int i; // contador del for
  
  // definimos los buffers para los datos
  uint8_t buf_ent[VW_MAX_MESSAGE_LEN]; 
  uint8_t buf_loc[8]; 
  
  func_ptr ptr_funciones[10];
  
  void ejecutarComando(int);
  void revisarCambios();
  void copiarBuffer();
  
};
#endif

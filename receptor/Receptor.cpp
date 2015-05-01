#include "Receptor.h"
Receptor::Receptor(func_ptr fp[10]){
  Serial.println("inicio"); 
  // Configuramos con la misma frecuencia que la del transmisor
  vw_setup(2000);	 
  vw_rx_start();
  
  // limpio la entrada local
  for(int i = 0; i<8; i++)
    buf_loc[i] = '0';
  
  // limpio los punteros a las funciones
  for(int j = 0; j<10; j++)
    ptr_funciones[j] = 0;
}
void Receptor::ejecutarComando(int btn){
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

void Receptor::revisarCambios(){
  // ejecuto acciones nuevas solo si hay un cambio
  // en los botones
  for(int i = 0; i<7; i++)
    if(buf_loc[i] != buf_ent[i])
      ejecutarComando(i);
}

void Receptor::copiarBuffer(){
  // copia el bufer local a la refencia interna, esto
  // para notar los cambios de estado a estado
  for(int i = 0; i<8; i++)
    buf_loc[i] = buf_ent[i];
}

void Receptor::loop(){
  if (vw_get_message(buf_ent, &buflen)){
    revisarCambios();
    copiarBuffer();
  }
}

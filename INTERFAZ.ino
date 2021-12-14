#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

#include "ServerWeb.h"
#include "Caracteres.h"

#define programar 1
#define buzzer 3

byte contador = 0, estadoBrillo = 0, funcion = 0,
     estadoButton = 0, contTiempo = 0, contCambio = 1;

int tiempoEspera = 2000;

unsigned long tiempoInicio = 0;

String datoCambio[9];

void setup() {

  pinMode(programar, INPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(buzzer, LOW);

  EEPROM.begin(512);

  delay(2000);

  iniciarLcd();

  cargarCaracter();
  
  while(digitalRead(programar) == 0){
    contador++;
    delay(500);
    if (contador == 5){
      mostrarCaracter(0, 0, 0);
      mostrarCaracter(15, 0, 0);    
      mostrarCaracter(0, 1, 0);
      mostrarCaracter(15, 1, 0);    
      mostrarMensaje(2, 0, "iverflores6");
      mostrarMensaje(3, 1, "@gmail.com");    
      for (int i = 0 ; i < 2 ; i++) {
        tone(3, 587, 709.720327982);
        delay(788.578142202);
        noTone(3);
        delay(500);
      }   
      delay(2000);    
      limpiarPantalla();      
      mostrarCaracter(14, 0, 5);
      mostrarMensaje(0, 0, "BIENVENIDO(A)"   );
      mostrarMensaje(0, 1, "MODO CONFIGURA." );   
      modoconfiguracion(); 
    }
  }
  limpiarPantalla();      
  mostrarCaracter(14, 0, 0);
  mostrarCaracter(15, 0, 0);  
  mostrarCaracter(15, 1, 4);
  mostrarMensaje(0, 0, "Bienvenido(a)");
  mostrarMensaje(0, 1, "Pasaje " + leerPasaje() + " Bs");  
  arrancarServer();
  funcion = 3;   

}

void loop() { 
  lecturaButton();
  contadorTiempo();
  
  if(contTiempo == 90){ 
    contTiempo = 0;
    apagarPantalla();
    estadoBrillo = 1;
    for(int i = 1 ; i <= 8 ; i++){
      datoCambio[i] = "";
    }   
  }
 
  server.handleClient();
}

void lecturaButton() {
  estadoButton = digitalRead(programar);
  if (estadoButton == LOW) {    
    delay(500);
    while(true){
      estadoButton = digitalRead(programar);
      if (estadoButton == HIGH) {
        if (estadoBrillo == 1) {
          prenderPantalla();
          estadoBrillo = 0;           
          cambioFuncion(0);                     
        }else {
          funcion++;                     
          cambioFuncion(1);            
        }        
        break;
      }
    }
  }
}

void contadorTiempo() {
  if (millis() - tiempoInicio >= tiempoEspera) {
    byte numRandom = 1;
    contTiempo++;
    if(contTiempo > 90){
      contTiempo = 0;     
    }   

    if(estadoPantalla() == 1){
      luszOnPantalla();
      contTiempo = 0;
      guardarPantalla(0);     
      datoCambio[contCambio] = leerCambio();
      contCambio++;
    }

    if(contCambio > 8){
      contCambio = 1;
    }

    numRandom = random(1,8);

    if(!datoCambio[numRandom].equals("")){      
      mostrarMensaje(3, 1, "Cambio =        ");
      mostrarMensaje(12, 1, datoCambio[numRandom]);

      if(datoCambio[numRandom].length() < 2){
        mostrarMensaje(14, 1, "Bs");        
      }
    }
    
    tiempoInicio = millis();
  }
}

void cambiarPasaje(){
  if (funcion == 7) {
    funcion = 1;
  }
}

void cambioFuncion(byte d) {

  limpiarPantalla();
 
  mostrarCaracter(14, 0, 0);
  mostrarCaracter(15, 0, 0);  
  mostrarCaracter(15, 1, 4);
  mostrarMensaje(0, 0, "Bienvenido(a)");

  if(d == 0){
    mostrarMensaje(0, 1, "Pasaje " + leerPasaje() + " Bs");
  }else{
    if (funcion == 7) {
      funcion = 1;
    }
    if(d == 1){
      switch (funcion) {
        case 1:
          guardarPasaje("1.50");
          mostrarMensaje(0, 1, "Pasaje 1.50 Bs");          
          break;
        case 2:
          guardarPasaje("1.80");
          mostrarMensaje(0, 1, "Pasaje 1.80 Bs");          
          break;
        case 3:
          guardarPasaje("2.00");
          mostrarMensaje(0, 1, "Pasaje 2.00 Bs");          
          break;
        case 4:
          guardarPasaje("2.20");
          mostrarMensaje(0, 1, "Pasaje 2.20 Bs");          
          break;
        case 5:
          guardarPasaje("2.60");
          mostrarMensaje(0, 1, "Pasaje 2.60 Bs");          
          break;
        case 6:
          guardarPasaje("2.80");
          mostrarMensaje(0, 1, "Pasaje 2.80 Bs");          
          break;
      }      
    }
  }
}

void mostrarCambio(String dato){
  if(dato.length() < 2){
    mostrarMensaje1(14, 1, "Bs");        
  }
}

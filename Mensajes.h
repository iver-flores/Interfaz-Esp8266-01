LiquidCrystal_I2C lcd1(0x27, 16, 2); 

void limpiarPantalla1(){
  lcd1.clear();  
  lcd1.home();
}

void prenderPantalla1(){  
  lcd1.clear();
  lcd1.home();
  lcd1.backlight();  
}


void mostrarCaracter1(int col, int fil, int numero){
  lcd1.setCursor(col, fil);  // mover el cursor a la posicion (columna=col, fila=fil) 
  lcd1.write(numero);        // mostrar el caracter que se guardo en el espacio numero 
  lcd1.setCursor(col, fil);  // mover el cursor a la posicion (columna=col, fila=fil) 
  lcd1.write(numero);        // mostrar el caracter que se guardo en el espacio numero 
}

void mostrarMensaje1(int col, int fil, String dato){
  lcd1.setCursor(col, fil);  // mover el cursor a la posicion (columna=cal, fila=fil) 
  lcd1.print(dato);          // mostrar el "dato" en la pantalla LCD 
}

void desplazarIzquierda1(){
  lcd1.scrollDisplayLeft(); 
  delay(1000);
}

void desplazarDerecha1(){
  lcd1.scrollDisplayRight(); 
  delay(1000);
}

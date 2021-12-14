#define sda 0
#define scl 2

// establecemos la dirección LCD en 0x27 para una pantalla de 16 caracteres y 2 líneas
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Definicion de caracteres personalizados
byte feliz[] = {
  B00000,
  B01010,
  B01010,
  B00000,
  B00100,
  B00000,
  B10001,
  B01110
};

byte buzzer[] = {
  B00010,
  B00110,
  B01010,
  B10010,
  B10010,
  B01010,
  B00110,
  B00010
};

byte cambio[] = {
  B01110,
  B11111,
  B11011,
  B11011,
  B11011,
  B11011,
  B11111,
  B01110
};

byte llave[] = {
  B01010,
  B10001,
  B10001,
  B01110,
  B00100,
  B00100,
  B00100,
  B00100
};

byte ver[] = {
  B01110,
  B00000,
  B01110,
  B10001,
  B10101,
  B10001,
  B01110,
  B00000
};

byte guardar[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B10101,
  B01110,
  B00100
};

byte nube[] = {
  B01110,
  B10001,
  B11111,
  B00000,
  B00100,
  B01110,
  B10101,
  B00100
};

byte buzOn[] = {
  B00010,
  B01001,
  B00101,
  B10101,
  B10101,
  B00101,
  B01001,
  B00010
};


void cargarCaracter() {
  lcd.createChar (0, feliz);      // crear el caracter personalizado en el numero  0
  lcd.createChar (1, guardar);     // crear el caracter personalizado en el numero  1
  lcd.createChar (2, buzzer);     // crear el caracter personalizado en el numero  2
  lcd.createChar (3, buzOn);      // crear el caracter personalizado en el numero  3
  lcd.createChar (4, cambio);     // crear el caracter personalizado en el numero  4
  lcd.createChar (5, llave);     // crear el caracter personalizado en el numero  5
  lcd.createChar (6, nube);     // crear el caracter personalizado en el numero  6
  lcd.createChar (7, ver);        // crear el caracter personalizado en el numero  7
}


void iniciarLcd() {
  lcd.begin(sda, scl);// preparar la pantalla LCD para su uso con (sda=GPIO0, scl=GPIO2)
  lcd.backlight();    // encender la luz de fondo de la pantalla LCD
  lcd.clear();        // borrar todos los caracteres de la pantalla LCD
  lcd.home();         // mover el cursor a la posicion (0,0) de la pantalla LCD
}

void mostrarCaracter(int col, int fil, int numero) {
  lcd.setCursor(col, fil);  // mover el cursor a la posicion (columna=col, fila=fil)
  lcd.write(numero);        // mostrar el caracter que se guardo en el espacio numero
  lcd.setCursor(col, fil);  // mover el cursor a la posicion (columna=col, fila=fil)
  lcd.write(numero);        // mostrar el caracter que se guardo en el espacio numero
}

void apagarPantalla() {
  lcd.clear();
  lcd.home();
  lcd.noBacklight();
}

void luszOnPantalla() {
  lcd.backlight();
}

void prenderPantalla() {
  lcd.clear();
  lcd.home();
  lcd.backlight();
}

void limpiarPantalla() {
  lcd.clear();
  lcd.home();
}

void mostrarMensaje(int col, int fil, String dato) {
  lcd.setCursor(col, fil);  // mover el cursor a la posicion (columna=cal, fila=fil)
  lcd.print(dato);          // mostrar el "dato" en la pantalla LCD
}

void desplazarIzquierda() {
  lcd.scrollDisplayLeft();
  delay(500);
}

void desplazarDerecha() {
  lcd.scrollDisplayRight();
  delay(500);
}

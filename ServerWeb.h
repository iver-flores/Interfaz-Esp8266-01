#include <ESP8266WebServer.h>
#include "Datos.h"
#include "Mensajes.h"

Datos datos1;

byte estBuz = 0;
byte pantalla = 0;
char camb[8];
char func[10];

String cambioEntrante = "";

ESP8266WebServer server(58491);

int getIpBlock(int index, String str) {
  char separator = '.';
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = str.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (str.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? str.substring(strIndex[0], strIndex[1]).toInt() : 0;
}

void handleRoot() {
  server.send(200, "text/html", "Bienvenido....");
}

void handleNotFound() {
  server.send(404, "text/html", "NO disponible...");
}

int estadoBuzzer(){
 return estBuz;
}

int estadoPantalla(){
 return pantalla;
}

void guardarPantalla(byte panta){
  pantalla = panta;
}

String leerCambio(){
 return cambioEntrante;
}

void cambioBuzzer(int cBuzzer) {
  estBuz = cBuzzer;
}

String leerPasaje(){
  return datos1.leerPasaje();
}

void guardarPasaje(String pasaje){
  datos1.guardarPasaje(pasaje);
}

void setConfig() {
  const String id = datos1.leerId();  
  if (server.arg(String("Conexion")).equals("On")&&server.arg(String("idE")).equals(id)) {
    server.send(200, "text/index", String("POST") + ", idE = " + id + ", Conexion = On" + 
                     ", Pasaje = " + datos1.leerPasaje());                                       
    limpiarPantalla1();
    mostrarCaracter1(14, 0, 5);
    mostrarMensaje1(0, 0, "CONFIGURACION"  );
    mostrarMensaje1(0, 1, "EN CURSO....."  );    
  }else if (server.arg(String("Configuracion")).equals("Guardar")&&server.arg(String("idE")).equals(id)) {                       
      char ip[22], mascara[22], gateway[22], nombre[22], telefono[22], grupo[22], ssid[22], password[22];
      server.arg("ip").toCharArray(ip, sizeof(ip));
      server.arg("mascara").toCharArray(mascara, sizeof(mascara));
      server.arg("gateway").toCharArray(gateway, sizeof(gateway));
      server.arg("nombre").toCharArray(nombre, sizeof(nombre));
      server.arg("telefono").toCharArray(telefono, sizeof(telefono));
      server.arg("grupo").toCharArray(grupo, sizeof(grupo));
      server.arg("ssid").toCharArray(ssid, sizeof(ssid));
      server.arg("password").toCharArray(password, sizeof(password));      
      datos1.guardarDatos(ip, mascara, gateway, nombre, telefono, grupo, ssid, password);      
      server.send(200, "text/index", String("POST") + ", idE = " + id + ", Configuracion = Guardada");                                              
      limpiarPantalla1();
      mostrarCaracter1(14, 0, 1);
      mostrarCaracter1(15, 0, 1);
      mostrarMensaje1(0, 0, "CONFIGURACION"  );
      mostrarMensaje1(0, 1, "GUARDADA....." );            
    }else if (server.arg(String("Ver")).equals("Datos")&&server.arg(String("idE")).equals(id)) {                            
      server.send(200, "text/index", String("POST")      + ", ip = " + datos1.leerIp() + ", mascara = "  + 
                  datos1.leerMascara() + ", gateway = "  + datos1.leerGateway()        + ", nombre = "   + 
                  datos1.leerNombre()  + ", telefono = " + datos1.leerTelefono()       + ", grupo = "    + 
                  datos1.leerGrupo()   + ", ssid = "     + datos1.leerSsid()           + ", password = " + 
                  datos1.leerPassword()+ ", idE = "      + id);          
      
      limpiarPantalla1();
      mostrarCaracter1(13, 0, 7);
      mostrarCaracter1(15, 0, 7);
      mostrarMensaje1(0, 0, "OBSERVANDO"         );
      mostrarMensaje1(0, 1, "CONFIGURACION...");      
    }else if (server.arg(String("Configuracion")).equals("Reiniciar")&&server.arg(String("idE")).equals(id)) {                                 
      server.send(200, "text/index", String("POST") + ", idE = " + id + ", Configuracion = Reiniciar");                                        
      
      limpiarPantalla1();      
      mostrarMensaje1(0, 0, "APAGUE Y PRENDA");
      mostrarMensaje1(0, 1, "EL DISPOSITIVO" );
    }else {
      server.send(200, "text/index", String("POST") + ", Mensaje = Error");          
      
      limpiarPantalla1();
      mostrarMensaje1(0, 0, "CONFIGURACION"  );
      mostrarMensaje1(0, 1, "ERRONEA....." );
    }  
}

void modoconfiguracion() {

  const char *ssidConfiguracion = "ESQ-IVR", *passConfiguracion = "12345678";

  const String valor = "/" + datos1.leerId();
  
  IPAddress ipS(getIpBlock(0, String("192.168.25.40")), 
                getIpBlock(1, String("192.168.25.40")), 
                getIpBlock(2, String("192.168.25.40")),
                getIpBlock(3, String("192.168.25.40")));
                
  IPAddress mascaraS(getIpBlock(0, String("255.255.255.0")), 
                     getIpBlock(1, String("255.255.255.0")),
                     getIpBlock(2, String("255.255.255.0")), 
                     getIpBlock(3, String("255.255.255.0")));
                     
  IPAddress gatewayS(getIpBlock(0, String("192.168.25.1")), 
                     getIpBlock(1, String("192.168.25.1")),
                     getIpBlock(2, String("192.168.25.1")), 
                     getIpBlock(3, String("192.168.25.1")));

  WiFi.softAPConfig(ipS, gatewayS, mascaraS);
  WiFi.softAP(ssidConfiguracion, passConfiguracion);

  server.on("/", handleRoot);
  server.on(valor, HTTP_POST, setConfig);
  server.onNotFound(handleNotFound);
  server.begin();
  
  while (true){    
    server.handleClient();    
  }
}

void setServer() {
  const String id = datos1.leerId();  
  if (server.arg(String("Conexion")).equals("On")&&server.arg(String("idE")).equals(id)) {
    server.send(200, "text/index", String("POST") + ", idE = " + id + ", Conexion = On" + 
                ", Pasaje = " + datos1.leerPasaje());                                          
  }else if (server.arg(String("Buzzer")).equals("On")&&server.arg(String("idE")).equals(id)) {                       
      server.arg(String("Cambio")).toCharArray(camb, sizeof(camb));
      server.arg(String("Funcion")).toCharArray(func, sizeof(func));
      server.send(200, "text/index", String("POST") + ", Buzzer = On, idE = " + id);     

      estBuz = 1;  
      pantalla = 1;

      cambioEntrante = camb;     
      
      prenderPantalla1();
      mostrarCaracter1(0, 1, 2);
      mostrarCaracter1(1, 1, 3);
      mostrarMensaje1(0, 0, "Bajo " + String(func));
      mostrarMensaje1(3, 1, "Cambio = ");
      mostrarMensaje1(12, 1, camb);

      if(server.arg(String("Cambio")).length() < 2){
        mostrarMensaje1(14, 1, "Bs");        
      }                               

      for(int i = 0 ; i < 2 ; i++){
        tone(3, 587, 709.720327982);
        delay(788.578142202);
        noTone(3);
        delay(500);  
      }            
    }else {
      server.send(200, "text/index", String("POST") + ", Mensaje = Error");                
    }  
}

void initServer(){
  String valor = "/" + datos1.leerId();

  server.on("/", handleRoot);
  server.on(valor, HTTP_POST, setServer);
  server.onNotFound(handleNotFound);
  server.begin();  
}

void arrancarServer(){
  String ip = datos1.leerIp(), mascara = datos1.leerMascara(), 
         gateway = datos1.leerGateway(), ssid = datos1.leerSsid(), 
         password = datos1.leerPassword();                  
  
  IPAddress ipS(getIpBlock(0, ip), 
                getIpBlock(1, ip), 
                getIpBlock(2, ip),
                getIpBlock(3, ip));
                
  IPAddress mascaraS(getIpBlock(0, mascara), 
                     getIpBlock(1, mascara),
                     getIpBlock(2, mascara), 
                     getIpBlock(3, mascara));
                     
  IPAddress gatewayS(getIpBlock(0, gateway), 
                     getIpBlock(1, gateway),
                     getIpBlock(2, gateway), 
                     getIpBlock(3, gateway));

  WiFi.softAPConfig(ipS, gatewayS, mascaraS);
  WiFi.softAP(ssid, password);

  initServer();
}

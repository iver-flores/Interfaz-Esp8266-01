#include "Eeprom.h"

Eeprom eeprom1;

class Datos{
  private:
    char id[22], ip[22], mascara[22], gateway[22], nombre[22], 
          telefono[22], grupo[22], ssid[22], password[22], pasaje[22];    
  
  public:
    void guardarDatos(String ipG, String mascaraG, String gatewayG, 
                      String nombreG, String telefonoG, 
                      String grupoG, String ssidG, String passwordG){                        
      eeprom1.grabar(0,  "3I4V10ER");                        
      eeprom1.grabar(22, ipG);
      eeprom1.grabar(44, mascaraG);
      eeprom1.grabar(66, gatewayG);
      eeprom1.grabar(88, nombreG);
      eeprom1.grabar(110, telefonoG);
      eeprom1.grabar(132, grupoG);
      eeprom1.grabar(154, ssidG);
      eeprom1.grabar(176, passwordG);
    }   

    void guardarPasaje(String pasa){
      eeprom1.grabar(198, pasa);
    }
   
    String leerId(){
      eeprom1.leer(0).toCharArray(id, 22);
      return String(id); 
    }

    String leerIp(){
      eeprom1.leer(22).toCharArray(ip, 22);           
      return String(ip); 
    }

    String leerMascara(){
      eeprom1.leer(44).toCharArray(mascara, 22);
      return String(mascara); 
    }

    String leerGateway(){
      eeprom1.leer(66).toCharArray(gateway, 22);
      return String(gateway); 
    }

    String leerNombre(){
      eeprom1.leer(88).toCharArray(nombre, 22);           
      return String(nombre);
    }

    String leerTelefono(){
      eeprom1.leer(110).toCharArray(telefono, 22);
      return String(telefono);
    }

    String leerGrupo(){
      eeprom1.leer(132).toCharArray(grupo, 22);
      return String(grupo);
    }

    String leerSsid(){
      eeprom1.leer(154).toCharArray(ssid, 22);
      return String(ssid);
    }

    String leerPassword(){
      eeprom1.leer(176).toCharArray(password, 22);
      return String(password);
    }

    String leerPasaje(){
      eeprom1.leer(198).toCharArray(pasaje, 22);
      return String(pasaje);
    }
       
};

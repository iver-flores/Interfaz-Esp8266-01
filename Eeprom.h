class Eeprom{
  public:    
    void grabar(int addr, String a){
      int tamano = a.length(); 
      char inchar[22]; 
      a.toCharArray(inchar, tamano+1);
      for (int i = 0; i < tamano; i++){
        if(!leerUno(addr+i).equals(String(inchar[i]))){
          EEPROM.write(addr+i, inchar[i]);  
        }
      }
      for (int i = tamano; i < 22; i++){
        if(!leerUno(addr+i).equals(String(inchar[i]))){
          EEPROM.write(addr+i, 255);
        }
      }
      EEPROM.commit();
    }
    
    String leer(int addr){
      byte lectura;
      String strlectura;
      for (int i = addr; i < addr + 22; i++){
        lectura = EEPROM.read(i);
        if (lectura != 255){
          strlectura += (char)lectura;
        }
      }
      return strlectura;
    }

    String leerUno(int addr){
      byte lectura;
      String strlectura;
      for (int i = addr; i < addr + 1; i++){
        lectura = EEPROM.read(i);
        if (lectura != 255){
          strlectura += (char)lectura;
        }
      }
      return strlectura;
    }
    
};

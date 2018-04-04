#ifndef FI_INTERFACE_H
#define FI_INTERFACE_H

#include <Arduino.h>


class fi_InterfaceClass{
  private:
  public:
    void clear();
    void show(uint8_t _number);
    void precision(uint8_t _min, uint8_t _value);
};

extern fi_InterfaceClass fi_Interface;


#endif

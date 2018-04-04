#ifndef FI_IO_H
#define FI_IO_H

#include <Arduino.h>

#define PIN_LED_1 3
#define PIN_LED_2 4
#define PIN_LED_3 1
#define PIN_LED_4 5

#define PIN_NAV_R 2
#define PIN_NAV_L 0


#define FI_D_RIGHT 1
#define FI_D_LEFT 2

class fi_IOClass{
  private:
  public:
    bool is_input;
    bool is_output;
    void init();
    void input();
    void output();
    void safe(uint8_t _option);
};

extern fi_IOClass fi_IO;

#endif

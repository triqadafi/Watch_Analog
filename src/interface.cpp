#include "interface.h"

#include "io.h"



void fi_InterfaceClass::clear(){
  pinMode(PIN_LED_1, INPUT);
  digitalWrite(PIN_LED_1, LOW);
  pinMode(PIN_LED_2, INPUT);
  digitalWrite(PIN_LED_2, LOW);
  pinMode(PIN_LED_3, INPUT);
  digitalWrite(PIN_LED_3, LOW);
  pinMode(PIN_LED_4, INPUT);
  digitalWrite(PIN_LED_4, LOW);
}
void fi_InterfaceClass::show(uint8_t _number){
  switch (_number) {
    case 1:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, HIGH);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 2:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, HIGH);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 3:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, HIGH);
    break;
    case 4:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, HIGH);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 5:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, HIGH);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 6:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, HIGH);
    break;
    case 7:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, INPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, HIGH);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 8:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, HIGH);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 9:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, HIGH);
      pinMode(PIN_LED_3, OUTPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 10:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, HIGH);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
    case 11:
      pinMode(PIN_LED_1, INPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, LOW);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, OUTPUT);
      digitalWrite(PIN_LED_4, HIGH);
    break;
    case 12:
      pinMode(PIN_LED_1, OUTPUT);
      digitalWrite(PIN_LED_1, LOW);
      pinMode(PIN_LED_2, OUTPUT);
      digitalWrite(PIN_LED_2, HIGH);
      pinMode(PIN_LED_3, INPUT);
      digitalWrite(PIN_LED_3, LOW);
      pinMode(PIN_LED_4, INPUT);
      digitalWrite(PIN_LED_4, LOW);
    break;
  }
}


void fi_InterfaceClass::precision(uint8_t _min, uint8_t _value){
  if(_value != 0){
    uint8_t _next = _min+1;
    fi_InterfaceClass::show(_next);
    delay(250);
    for (uint8_t i = 0; i < _value; i++) {
      fi_InterfaceClass::show(_next);
      delay(250);
      fi_InterfaceClass::clear();
      delay(250);
    }
    fi_InterfaceClass::clear();
    delay(500);
  }
}

fi_InterfaceClass fi_Interface;

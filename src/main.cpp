#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include <TinyWireM.h>                  // I2C Master lib for ATTinys which use USI
#include <TinyRTClib.h>

#include "definition.h"
#include "io.h"
#include "button.h"
#include "interface.h"

RTC_DS1307 rtc;                      // Set up real time clock

unsigned long FI_G_MILLIS = 0;
volatile uint8_t FI_G_MENU = 0;
volatile uint8_t FI_G_MENU_STATE = 0;
volatile uint8_t FI_G_MENU_SLEEP_CALLBACK = 0;
uint8_t FI_G_MENU_CHILD = 0;

uint8_t FI_G_SETTING_HOUR = 0;
uint8_t FI_G_SETTING_MINUTE = 0;

void fi_sleep_init(){
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}
void enter_sleep(){
  sleep_enable();
  sleep_cpu();
}

void fi_adc_disable(){
  ADCSRA &= ~(1<<ADEN);                                                         // Disable ADC
}

void fi_interrupt_enable(){
  GIMSK = 0b00100000;
  PCMSK = 0b00000101; // pb 0 1 4
  sei();
}

void fi_interrupt_disable(){
  // cli();
  GIMSK = 0b00000000;
  PCMSK = 0b00000000; // pb 0 1 4
}

ISR(PCINT0_vect){
  if(FI_NAV_R){
    FI_G_MENU = FI_D_MENU_HOME;
    FI_G_MENU_STATE = 0;
    FI_G_MENU_SLEEP_CALLBACK = 1;
  }
  if(FI_NAV_L){
    FI_G_MENU = FI_D_MENU_HOME;
    FI_G_MENU_STATE = 0;
    FI_G_MENU_SLEEP_CALLBACK = 2;
  }
}
void setup() {
  TinyWireM.begin();                                                            // Begin I2C
  rtc.begin();                                                                  // Begin DS1307 real time clock

  if(!rtc.isrunning()){
    //rtc.adjust(DateTime(__DATE__, __TIME__));                                   // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(2018, 4, 4, 15, 10, 0));
  }

  fi_sleep_init();
  fi_IO.init();
  fi_IO.input();

  fi_adc_disable();

  FI_G_MENU = FI_D_MENU_SLEEP;
  FI_G_MENU_STATE = 0;
}

uint8_t hourvalue, minutevalue, precisionvalue;
void loop() {
  if(FI_G_MENU == FI_D_MENU_HOME){
    if(FI_G_MENU_STATE == 0){
      fi_interrupt_disable();
      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
        if(FI_G_MENU_SLEEP_CALLBACK == 1){
          fi_Interface.show(3);
          fi_IO.safe(FI_D_RIGHT);
          fi_Interface.clear();
          delay(1000);

          FI_G_MENU_STATE = 0;
          FI_G_MENU = FI_D_MENU_HOUR;
        }
        if(FI_G_MENU_SLEEP_CALLBACK == 2){
          fi_Interface.show(9);
          fi_IO.safe(FI_D_LEFT);
          fi_Interface.clear();
          delay(1000);

          FI_G_MENU_STATE = 0;
          FI_G_MENU = FI_D_MENU_MINUTE;
        }
        // if(FI_NAV_L){
        //   fi_Interface.set(1, 0);
        //   fi_IO.safe(FI_D_LEFT);
        //   fi_IO.output();
        //   rtc.adjust(DateTime(2014, 1, 21, 7, 0, 0));
        //   fi_Interface.set(0, 0);
        //   FI_G_MENU_STATE = 0;
        //   FI_G_MENU = FI_D_MENU_HOME;
        // }
    }
  }else if(FI_G_MENU == FI_D_MENU_HOUR){
    if(FI_G_MENU_STATE == 0){
      fi_IO.output();
      DateTime now = rtc.now();           // Get the RTC info
      fi_IO.input();

      hourvalue = now.hour();             // Get the hour
      if(hourvalue > 12) hourvalue -= 12; // This clock is 12 hour, is 13-24, convert to 1-12
      minutevalue = now.minute() / 5;
      precisionvalue = now.minute() % 5;

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      fi_Interface.show(hourvalue);
      delay(500);
      fi_Interface.clear();
      delay(500);

      fi_Interface.show(minutevalue);
      delay(250);
      fi_Interface.clear();
      delay(250);
      fi_Interface.show(minutevalue);
      delay(250);
      fi_Interface.clear();
      delay(250);

      fi_Interface.precision(minutevalue, precisionvalue);
      delay(500);
      fi_Interface.clear();



      FI_G_MENU_STATE = 0;
      if(FI_NAV_R){
        fi_Interface.show(3);
        fi_IO.safe(FI_D_RIGHT);
        delay(1000);
        fi_Interface.clear();
        FI_G_MENU = FI_D_MENU_PROGRAM;
      }else{
        FI_G_MENU = FI_D_MENU_SLEEP;
      }
    }
  }
  // else if(FI_G_MENU == FI_D_MENU_PROGRAM){
  //   if(FI_G_MENU_STATE == 0){
  //     for (uint8_t i = 0; i < 5; i++) {
  //       fi_Interface.set(1, 1);
  //       delay(100);
  //       fi_Interface.set(0, 0);
  //     }
  //     FI_G_MENU_STATE++;
  //   }
  //   if(FI_G_MENU_STATE == 1){
  //     fi_interrupt_disable();
  //     fi_IO.output();
  //   }
  // }
  else if(FI_G_MENU == FI_D_MENU_SLEEP){
    if(FI_G_MENU_STATE == 0){
      delay(800);
      fi_interrupt_enable();
      delay(200);
      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      enter_sleep(); // actually this has an internal loop
    }
  }
  else if(FI_G_MENU == FI_D_MENU_MINUTE){
    if(FI_G_MENU_STATE == 0){
      fi_IO.output();
      DateTime now = rtc.now();           // Get the RTC info
      fi_IO.input();

      minutevalue = now.minute() / 5;
      precisionvalue = now.minute() % 5;

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){
      fi_Interface.show(minutevalue);
      delay(250);
      fi_Interface.clear();
      delay(250);
      fi_Interface.show(minutevalue);
      delay(250);
      fi_Interface.clear();
      delay(250);

      fi_Interface.precision(minutevalue, precisionvalue);
      delay(500);
      fi_Interface.clear();

      FI_G_MENU_STATE = 0;
      if(FI_NAV_R){
        fi_Interface.show(3);
        fi_IO.safe(FI_D_RIGHT);
        delay(1000);
        fi_Interface.clear();
        FI_G_MENU = FI_D_MENU_MENU;
      }else{
        FI_G_MENU = FI_D_MENU_SLEEP;
      }
    }
  }else if(FI_G_MENU == FI_D_MENU_MENU){
    if(FI_G_MENU_STATE == 0){
      fi_IO.input();
      FI_G_MILLIS = millis();

      FI_G_MENU_STATE++;
    }
    if(FI_G_MENU_STATE == 1){

      // ENTER LED ANIMATION HERE


      if(FI_NAV_L){
        fi_Interface.clear();
        fi_IO.safe(FI_D_LEFT);
        if(FI_G_MENU_CHILD < 6){
          FI_G_MENU_CHILD++;
        }else{
          FI_G_MENU_CHILD = 0;
        }
        delay(1000);
        FI_G_MILLIS = millis();
      }
      if(FI_NAV_R){
        fi_Interface.clear();
        fi_IO.safe(FI_D_RIGHT);
        FI_G_MENU_STATE = 0;
        if(FI_G_MENU_CHILD == 5){
          FI_G_MENU = FI_D_MENU_SETTING;
        }else{
          FI_G_MENU = FI_D_MENU_SLEEP;
        }
        delay(1000);
      }
    }
  }
}

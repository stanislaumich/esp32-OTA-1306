#include "SSD1306.h"

// Pin definitions for I2C
#define OLED_SDA    5  // pin 14
#define OLED_SDC    4  // pin 12
#define OLED_ADDR   0x3C


SSD1306  display(0x3c, 5, 4);


void initOled(void){
  display.init();

  //display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10); 

 }
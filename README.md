> ![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)
> #SHT click#
> ##By [MikroElektronika](http://www.mikroe.com)
---

![SHT_click](http://cdn.mikroe.com/knowlegebase/uploads/2016/05/04181934/sht-click-learn-banner-730x410.jpg)

---
[Product Page](http://www.mikroe.com/click/sht/)

[Manual Page](http://docs.mikroe.com/SHT_click)

[Learn Page](http://learn.mikroe.com/leader-humidity-measurement-sht/)

---

### General Description
SHT3x-DIS is the next generation of Sensirion’s temperature and 
humidity sensors. It builds on a new CMOSens sensor chip that is at 
the heart of Sensirion’s new humidity and temperature platform. 
The SHT3x-DIS has increased intelligence, reliability and improved 
accuracy specifications compared to its predecessor. Its functionality 
includes enhanced signal processing, two distinctive and user 
selectable I2C addresses and communication speeds of up to 1 MHz.

---

### Features
* Fully calibrated, linearized, and temperature compensated digital output
* Wide supply voltage range, from 2.4 V to 5.5 V
* I2C Interface with communication speeds up to 1 MHz and two user selectable addresses
* Typical accuracy of 2 % RH and 0.3 °C
* Very fast start-up and measurement time

---

### Installation
Use the package manager to install the library for your architecture.

---

### Example

#### Configuration
* MCU:             STM32F107VC
* Dev.Board:       EasyMx Pro v7
* Oscillator:      72 Mhz internal
* Ext. Modules:    SHT Click
* SW:              MikroC PRO for ARM 4.7.0

```
#include "SHT_hw.h"
#include "resources.h"

/*       Variables
 ****************************/
float temperature, humidity;
char tmp_txt[10];

/*       TFT pins
 ****************************/
unsigned int TFT_DataPort at GPIOE_ODR;
sbit TFT_RST at GPIOE_ODR.B8;
sbit TFT_RS at GPIOE_ODR.B12;
sbit TFT_CS at GPIOE_ODR.B15;
sbit TFT_RD at GPIOE_ODR.B10;
sbit TFT_WR at GPIOE_ODR.B11;
sbit TFT_BLED at GPIOE_ODR.B9;

/*      Prototypes
 ****************************/
void system_init( void );
void display_init( void );
void display_temp( void );
void display_hum( void );

/*      Functions
 ****************************/
void system_init()
{
    I2C1_Init_Advanced( 100000, &_GPIO_MODULE_I2C1_PB67 );
    Delay_ms ( 200 );
}

void display_init()
{
    TFT_Init_ILI9341_8bit( 320, 240 );
    TFT_BLED = 1;
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Brush( 1, CL_WHITE, 0, 0, 0, 0 );
    TFT_Set_Font( TFT_defaultFont, CL_BLACK, FO_HORIZONTAL );
    TFT_Fill_Screen( CL_WHITE );
    TFT_Set_Pen( CL_BLACK, 1 );
    TFT_Line(  20,  46, 300,  46 );
    TFT_Line(  20,  70, 300,  70 );
    TFT_Line(  20, 220, 300, 220 );
    TFT_Set_Pen( CL_WHITE, 1 );
    TFT_Set_Font( &HandelGothic_BT21x22_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "SHT click", 115, 14 );
    TFT_Set_Font( &Tahoma15x16_Bold, CL_BLUE, FO_HORIZONTAL );
    TFT_Write_Text( "SHT3x-DIS", 125, 50 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_BLACK, FO_HORIZONTAL );
    TFT_Write_Text( "EasyMx PRO v7 for STM32", 19, 223 );
    TFT_Set_Font( &Verdana12x13_Regular, CL_RED, FO_HORIZONTAL );
    TFT_Write_Text( "www.mikroe.com", 200, 223 );
    TFT_Set_Font( &Tahoma15x16_Bold, CL_BLACK, FO_HORIZONTAL );
    TFT_Write_Text( "Temperature : ", 60, 100 );
    TFT_Write_Text( "Humidity : ", 60, 135 );
    TFT_Set_Font( &Tahoma15x16_Bold, CL_RED, FO_HORIZONTAL );
}

void display_temp()
{
    temperature = sht_temp_ss();
    Delay_ms( 200 );
    sprintf( tmp_txt, "%3.1f C", temperature );
    TFT_Rectangle( 195, 95, 250, 120 );
    TFT_Write_Text( tmp_txt, 200, 100 );
}

void display_hum()
{
    humidity = sht_hum_ss();
    Delay_ms( 200 );
    sprintf( tmp_txt, "%3.1f", humidity );
    strcat( tmp_txt, " %" );
    TFT_Rectangle( 195, 130, 250, 155 );
    TFT_Write_Text( tmp_txt, 200, 135 );
}

void main() 
{
    system_init();
    display_init();
    sht_init( 0x44 );
    
    while( 1 )
    {
        display_temp();
        display_hum();
    }
}
```

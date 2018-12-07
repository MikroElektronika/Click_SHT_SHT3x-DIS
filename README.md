![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# SHT Click

- **CIC Prefix**  : SHT
- **Author**      : Dusan Poluga
- **Verison**     : 1.0.0
- **Date**        : okt 2018.

---

### Software Support

We provide a library for the SHT Click on our [LibStock](https://libstock.mikroe.com/projects/view/1777/sht-click) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

Library contains basic functions for working with the click board.

Key functions :

- ```void sht_software_rst()``` - Click board software reset function.
- ```float sht_hum_ss()``` - Function for reading the humidity data from the sensor.
- ```float sht_temp_ss()``` - Function for reading temperature data from the sensor.

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initialize GPIO and communication structures.
- Application Initialization - Initialize the communication interface and
                               configure the click board.
- Application Task - Temperature and humidity data is measured and read from
                   the sensor. After the data has been read it is displayed
                   on the serial port.
```.c
void applicationTask()
{
    float temperature;
    float humidity;
    char text[15];

    Delay_ms(1500);
    temperature = sht_temp_ss();
    FloatToStr(temperature,&text[0]);
    mikrobus_logWrite("Temperature: ",_LOG_TEXT);
    mikrobus_logWrite(&text[0],_LOG_TEXT);
    mikrobus_logWrite("°C",_LOG_LINE);
    Delay_ms( 200 );
    humidity = sht_hum_ss();
    FloatToStr(humidity,&text[0]);
    mikrobus_logWrite("Humidity: ",_LOG_TEXT);
    mikrobus_logWrite(&text[0],_LOG_TEXT);
    mikrobus_logWrite("%",_LOG_LINE);
    Delay_ms( 200 );
}
```

${EXAMPLE_ADDITIONAL_FUNCTIONS}

The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/1777/sht-click) page.

Other mikroE Libraries used in the example:

- Conversions library
- C_String library
- I2C library
- UART library

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---

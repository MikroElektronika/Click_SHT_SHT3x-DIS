/*
Example for SHT Click

    Date          : okt 2018.
    Author        : Dusan Poluga

Test configuration TIVA :
    
    MCU              : TM4C129XNCZAD
    Dev. Board       : EasyMx PRO v7 for TIVA ARM
    ARM Compiler ver : v6.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initialize GPIO and communication structures.
- Application Initialization - Initialize the communication interface and
                               configure the click board.
- Application Task - Temperature and humidity data is measured and read from
                   the sensor. After the data has been read it is displayed
                   on the serial port.
*/

#include "Click_SHT_types.h"
#include "Click_SHT_config.h"

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_SHT_I2C_CFG[0] );
    mikrobus_logInit( _LOG_USBUART_A, 9600 );
    Delay_ms( 100 );
}

void applicationInit()
{
    sht_i2cDriverInit( (T_SHT_P)&_MIKROBUS1_GPIO, (T_SHT_P)&_MIKROBUS1_I2C, SHT_I2C_ADDR0 );
    mikrobus_logWrite("System Initialized",_LOG_LINE);
    Delay_ms(100);
}

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

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
    	applicationTask();
    }
}

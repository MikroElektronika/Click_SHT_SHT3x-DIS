#include "SHT_hw.h"

/*       Variables
 ****************************/
float temperature, humidity;
char tmp_txt[15];

/*      Prototypes
 ****************************/
void system_init( void );
void display_temp( void );
void display_hum( void );

/*      Functions
 ****************************/
void system_init()
{
    I2C2_Init( 100000 );
    Delay_ms ( 200 );

    UART2_Init( 57600 );
    Delay_ms( 200 );

    UART2_Write_Text( "Initialization done!\r\n" );
}

void display_temp()
{
    temperature = sht_temp_ss();
    Delay_ms( 200 );
    FloatToStr( temperature, tmp_txt );
    UART2_Write_Text( tmp_txt );
}

void display_hum()
{
    humidity = sht_hum_ss();
    Delay_ms( 200 );
    FloatToStr( temperature, tmp_txt );
    UART2_Write_Text( tmp_txt );
}

void main()
{
    system_init();
    sht_init( 0x44 );

    while( 1 )
    {
        display_temp();
        display_hum();
    }
}
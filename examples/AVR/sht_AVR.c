#include "SHT_hw.h"

sbit SHT_RST_PIN at PORTA6_bit;
sbit SHT_RST_PIN_DIR at DDA6_bit;

/*       Variables
 ****************************/
float temperature, humidity;
char tmp_txt[15];

/*      Prototypes
 ****************************/
void system_init( void );
void display_temp( void );
void display_hum( void );

void system_init()
{
    SHT_RST_PIN_DIR = 1;

    TWI_Init( 100000 );
    Delay_ms ( 200 );

    UART1_Init( 57600 );
    Delay_ms( 200 );

    UART1_Write_Text( "Initialization done!\r\n" );
}

void display_temp()
{
    temperature = sht_temp_pm();
    sprintf( tmp_txt, "%3.1f", temperature );
    UART1_Write_Text( "Temperature : " );
    UART1_Write_Text( tmp_txt );
    UART1_Write_Text( "\r\n" );
}

void display_hum()
{
    humidity = sht_hum_pm();
    sprintf( tmp_txt, "%3.1f", humidity );
    UART1_Write_Text( "Humidity : " );
    UART1_Write_Text( tmp_txt );
    UART1_Write_Text( "\r\n" );
}

void main() 
{
    system_init();
    sht_init( 0x44 );

    while( 1 )
    {
        sht_start_pm();
        Delay_ms( 2000 );
        sht_stop_pm();
        Delay_ms( 1000 );
        display_temp();

        sht_start_pm();
        Delay_ms( 2000 );
        sht_stop_pm();
        Delay_ms( 1000 );
        display_hum();
    }
}
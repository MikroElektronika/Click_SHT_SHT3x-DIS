#include "SHT_hw.h"

sbit SHT_RST_PIN at GPIO_PIN1_bit;

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
    GPIO_Digital_Output( &GPIO_PORT_00_07, _GPIO_PINMASK_1 );
    Delay_ms( 200 );
    
    I2CM1_Init( _I2CM_SPEED_MODE_STANDARD, _I2CM_SWAP_DISABLE );
    Delay_ms ( 200 );

    UART1_Init( 57600 );
    Delay_ms( 200 );

    UART1_Write_Text( "Initialization done!\r\n" );
}

void display_vals()
{
    char tmp_t[ 15 ] = { 0 };
    char tmp_h[ 15 ] = { 0 };
    
    temperature = sht_temp_ss();
    humidity = sht_hum_ss();
    Delay_ms( 1000 );
    
    FloatToStr( temperature, tmp_t );
    FloatToStr( humidity, tmp_h );
    UART1_Write_Text( "Temperature : " );
    UART1_Write_Text( tmp_t );
    UART1_Write_Text( "\r\n" );
    UART1_Write_Text( "Humidity : " );
    UART1_Write_Text( tmp_h );
    UART1_Write_Text( "\r\n" );
}

void main()
{
    system_init();
    sht_init( 0x44 );
    Delay_1sec();
    
    
    while( 1 )
    {
        display_vals();
    }
}
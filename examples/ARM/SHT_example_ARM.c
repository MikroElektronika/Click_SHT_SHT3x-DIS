#include "SHT_hw.h"
#include "resources.h"

/*       Variables
 ****************************/
sbit SHT_RST_PIN at GPIOC_ODR.B2;

float temperature  = 0.0F;
float humidity     = 0.0F;
char tmp_txt[ 10 ] = { 0 };

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
void display_vals( void );

/*      Functions
 ****************************/
void system_init()
{
    GPIO_Digital_Output( &GPIOC_BASE, _GPIO_PINMASK_2 );
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
    char tmp_t[ 15 ] = { 0 };

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
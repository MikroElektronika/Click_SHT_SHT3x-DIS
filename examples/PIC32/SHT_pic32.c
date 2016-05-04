#include "SHT_hw.h"
#include "resources.h"

/*        TFT pins
 *****************************/
char TFT_DataPort at LATE;
sbit TFT_RST at LATD7_bit;
sbit TFT_BLED at LATD2_bit;
sbit TFT_RS at LATD9_bit;
sbit TFT_CS at LATD10_bit;
sbit TFT_RD at LATD5_bit;
sbit TFT_WR at LATD4_bit;
char TFT_DataPort_Direction at TRISE;
sbit TFT_RST_Direction at TRISD7_bit;
sbit TFT_BLED_Direction at TRISD2_bit;
sbit TFT_RS_Direction at TRISD9_bit;
sbit TFT_CS_Direction at TRISD10_bit;
sbit TFT_RD_Direction at TRISD5_bit;
sbit TFT_WR_Direction at TRISD4_bit;

/*       Variables
 ****************************/
sbit SHT_RST_PIN at RC1_bit;
sbit SHT_RST_PIN_DIR at TRISC1_bit;
float temperature, humidity;
char tmp_txt[10];

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
    SHT_RST_PIN_DIR = 0;
    
    I2C2_Init( 100000 );
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
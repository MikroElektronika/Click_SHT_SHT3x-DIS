/*******************************************************************************
* Title                 :   SHT click
* Filename              :   SHT_hw.c
* Author                :   MSV
* Origin Date           :   28/01/2016
* Notes                 :   None
*******************************************************************************/
/*************** MODULE REVISION LOG ******************************************
*
*    Date    Software Version    Initials   Description
*  28/01/16    XXXXXXXXXXX         MSV      Interface Created.
*
*******************************************************************************/
/**
 * @file SHT_hw.c
 * @brief <h3>Hardware Layer</h3>
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "SHT_hw.h"
#include "SHT_hal.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/

/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static uint8_t _i2c_addr;
static bool _clk_stretching;
static RPT_t _repeatability;
static MPS_t _mps;
/******************************************************************************
* Function Prototypes
*******************************************************************************/
/* Single shot measurement */
void _sht_ss( uint8_t raw_measurement );
/* Periodic measurement */
void _sht_pm( void );
/* Verify CRC */
bool _calc_crc( uint8_t crc,
                uint8_t *raw_data );
/* Humidity calculation */
float _calc_hum( uint8_t *raw_data );
/* Temperature calculation */
float _calc_temp( uint8_t *raw_data );
/* Status register reading */
void _read_status( uint8_t *raw_data );
/******************************************************************************
* Function Definitions
*******************************************************************************/
void _sht_ss( uint8_t *raw_measurement )
{
    uint8_t tmp_cmd[ 2 ];

    switch ( _clk_stretching )
    {
        case true :
            tmp_cmd[ 0 ] = STR_ENABLE;

            switch ( _repeatability )
            {

                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x06;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x0D;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x10;
                break;
            }
        break;

        case false :    
            tmp_cmd[ 0 ] = STR_DISABLE;

            switch ( _repeatability )
            {

                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x00;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x0B;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x16;
                break;
            }
        break;
    }
    sht_hal_read( tmp_cmd, raw_measurement, 6 );
}

bool _calc_crc( uint8_t crc,
                uint8_t *raw_data )
{
    uint8_t *end;

    crc ^= 0xFF;
    end = raw_data + 2;

    do {
        crc ^= *( raw_data++ );
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ CRC_POLYNOMIAL : crc >> 1;

    } while ( raw_data < end );

    return crc ^ 0xFF;
}

float _calc_hum( uint8_t *raw_data )
{
    uint16_t raw_humididty;
    uint8_t *tmp_ptr = raw_data;

    raw_humididty = ( *( tmp_ptr + 3 ) << 8 ) & 0xFF00;
    raw_humididty |= *( tmp_ptr + 4 );

    return ( 100.0f * ( ( float )raw_humididty / 65535.0f ) );
}

float _calc_temp( uint8_t *raw_data )
{
    uint16_t raw_temperature;
    uint8_t *tmp_ptr = raw_data;

    raw_temperature = ( *tmp_ptr << 8 ) & 0xFF00;
    raw_temperature |= *( tmp_ptr + 1 );

    return ( ( 175.0f * ( ( float )raw_temperature / 65535.0f ) ) - 45.0f );
}

void _read_status( uint16_t *reg_data )
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 2 ];

    tmp_cmd[ 0 ] = ( READ_STATUS & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = READ_STATUS & 0x00FF;

    sht_hal_read( tmp_cmd, raw_data, 2 );

    *reg_data = raw_data[ 0 ] << 8;
    *reg_data |= raw_data[ 1 ];
}

void sht_init( uint8_t i2c_address )
{
    sht_hal_init( i2c_address );

    _i2c_addr = i2c_address;
    _clk_stretching = false;
    _repeatability = RPT_MEDIUM;
    _mps = MPS_1;
}

void sht_reset()
{
    sht_init( _i2c_addr );
}

void sht_set_clk_strecth( bool clk_stretching )
{
    _clk_stretching = clk_stretching;
}

void sht_set_repeats( RPT_t repeatability )
{
    _repeatability = repeatability;
}

void sht_set_mps( MPS_t measure_per_second )
{
    _mps = measure_per_second;
}

float sht_temp_ss()
{
    uint8_t raw_data[ 6 ];

    do {
        _sht_ss( raw_data );

    } while ( !_calc_crc( raw_data[ 2 ], &raw_data[ 0 ] ) );

    return _calc_temp( raw_data );
}

float sht_hum_ss()
{
    uint8_t raw_data[ 6 ];

    do {
        _sht_ss( raw_data );

    } while ( !_calc_crc( raw_data[ 5 ], &raw_data[ 3 ] ) );

    return _calc_hum( raw_data );
}

void sht_start_pm()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = _mps;

    switch ( _mps )
    {
        case MPS_05 :
            switch ( _repeatability )
            {
                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x32;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x24;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2F;
                break;
            }
        break;

        case MPS_1 :
            switch ( _repeatability )
            {
                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x30;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x26;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2D;
                break;
            }
        break;

        case MPS_2 :
            switch ( _repeatability )
            {
                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x36;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x20;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2B;
                break;
            }
        break;

        case MPS_4 :
            switch ( _repeatability )
            {
                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x34;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x22;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x29;
                break;
            }
        break;

        case MPS_10 :
            switch ( _repeatability )
            {
                case RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x37;
                break;
                case RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x21;
                break;
                case RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2A;
                break;
            }
        break;
    }
    sht_hal_write( tmp_cmd, NULL, 0 );
}

float sht_temp_pm()
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 6 ];

    tmp_cmd[ 0 ] = ( FETCH_DATA  & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = FETCH_DATA & 0x00FF;

    do  {
        sht_hal_read( tmp_cmd, raw_data, 6 );

    } while ( !_calc_crc( raw_data[ 2 ], &raw_data[ 0 ] ) );

    return _calc_temp( raw_data );
}

float sht_hum_pm()
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 6 ];

    tmp_cmd[ 0 ] = ( FETCH_DATA  & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = FETCH_DATA & 0x00FF;

    do {
        sht_hal_read( tmp_cmd, raw_data, 6 );

    } while ( !_calc_crc( raw_data[ 5 ], &raw_data[ 3 ] ) );

    return _calc_hum( raw_data );
}

void sht_stop_pm()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( BREAK & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = BREAK & 0x00FF;

    sht_hal_write( tmp_cmd, NULL, 0 );
}

void sht_software_rst()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( SOFT_RESET & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SOFT_RESET & 0x00FF;

    sht_hal_write( tmp_cmd, NULL, 0 );
}

void sht_heater_control( bool state )
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = HEATER;

    if ( state )
        tmp_cmd[ 1 ] = 0x6D;
    else
        tmp_cmd[ 1 ] = 0x66;

    sht_hal_write( tmp_cmd, NULL, 0 );
}

void sht_clear_status()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( CLEAR_STATUS & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = CLEAR_STATUS & 0x00FF;

    sht_hal_write( tmp_cmd, NULL, 0 );
}

bool sht_alert_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 15 ) & 0x01 ) ? true : false;
}

bool sht_heater_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 13 ) & 0x01 ) ? true : false;
}

bool sht_hum_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 11 ) & 0x01 ) ? true : false;
}

bool sht_temp_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 10 ) & 0x01 ) ? true : false;
}

bool sht_reset_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 4 ) & 0x01 ) ? true : false;
}

bool sht_cmd_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 1 ) & 0x01 ) ? true : false;
}

bool sht_wr_chksum_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 1 ) & 0x01 ) ? true : false;
}
/*************** END OF FUNCTIONS *********************************************/
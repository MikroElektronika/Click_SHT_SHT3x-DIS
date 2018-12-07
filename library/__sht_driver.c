/*
    __sht_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__sht_driver.h"
#include "__sht_hal.c"

/* ------------------------------------------------------------------- MACROS */


/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __SHT_DRV_I2C__
static uint8_t _slaveAddress;
#endif

static uint8_t _clk_stretching;
static uint8_t _repeatability;
//static MPS_t _mps;
static uint8_t _mps;

const uint8_t SHT_I2C_ADDR0 = 0x44;
const uint8_t SHT_I2C_ADDR1 = 0x45;

/**
  * 0.5 measurements per second */
const uint8_t SHT_MPS_05 = 0x20;

 /**
   * 1 measurements per second */
const uint8_t SHT_MPS_1  = 0x21;

/**
  * 2 measurements per second */
const uint8_t SHT_MPS_2  = 0x22;

/**
  * 4 measurements per second */
const uint8_t SHT_MPS_4  = 0x23;

/**
     * 10 measurements per second */
const uint8_t SHT_MPS_10 = 0x27;

 /**
     * High repeatability */
const uint8_t SHT_RPT_HIGH = 0;

/**
  * Medium repeatability */
const uint8_t SHT_RPT_MEDIUM = 1;

/**
  * Low repeatability */
const uint8_t SHT_RPT_LOW = 2;

/**
     * Stretching enabled */
const uint8_t SHT_STR_ENABLE     = 0x2C;
/**
  * Stretching disabled */
const uint8_t SHT_STR_DISABLE    = 0x24;

/* - - - - - - - - - - - - - - - - */
const uint8_t SHT_CRC_POLYNOMIAL = 0x31;

const uint16_t SHT_FETCH_DATA = 0xE000;

const uint16_t SHT_PERIODIC_ART = 0x2B32;

const uint16_t SHT_BREAK = 0x3093;

const uint16_t SHT_SOFT_RESET = 0x30A2;

const uint8_t SHT_HEATER = 0x30;

const uint16_t SHT_READ_STATUS = 0xF32D;

const uint16_t SHT_CLEAR_STATUS1 = 0x3041;
/* - - - - - - - - - - - - - - - - */



/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */
static void sht_hal_write( uint8_t *command, uint8_t *buffer, uint16_t count);
static void sht_hal_read( uint8_t *command, uint8_t *buffer, uint16_t count);


/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */
static void _sht_ss( uint8_t *raw_measurement )
{
    uint8_t tmp_cmd[ 2 ];

    switch ( _clk_stretching )
    {
        case 1 :
            tmp_cmd[ 0 ] = SHT_STR_ENABLE;

            switch ( _repeatability )
            {

                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x06;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x0D;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x10;
                break;
            }
        break;

        case 0 :
            tmp_cmd[ 0 ] = SHT_STR_DISABLE;

            switch ( _repeatability )
            {

                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x00;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x0B;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x16;
                break;
            }
        break;
    }
    sht_hal_read( tmp_cmd, raw_measurement, 6 );
}

static uint8_t _calc_crc( uint8_t crc,
                uint8_t *raw_data )
{
    uint8_t *end;

    crc ^= 0xFF;
    end = raw_data + 2;

    do {
        crc ^= *( raw_data++ );
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;
        crc = crc & 1 ? ( crc >> 1 ) ^ SHT_CRC_POLYNOMIAL : crc >> 1;

    } while ( raw_data < end );

    return crc ^ 0xFF;
}

static float _calc_hum( uint8_t *raw_data )
{
    uint16_t raw_humididty;
    uint8_t *tmp_ptr = raw_data;

    raw_humididty = ( *( tmp_ptr + 3 ) << 8 ) & 0xFF00;
    raw_humididty |= *( tmp_ptr + 4 );

    return ( 100.0f * ( ( float )raw_humididty / 65535.0f ) );
}

static float _calc_temp( uint8_t *raw_data )
{
    uint16_t raw_temperature;
    uint8_t *tmp_ptr = raw_data;

    raw_temperature = ( *tmp_ptr << 8 ) & 0xFF00;
    raw_temperature |= *( tmp_ptr + 1 );

    return ( ( 175.0f * ( ( float )raw_temperature / 65535.0f ) ) - 45.0f );
}

static void _read_status( uint16_t *reg_data )
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 2 ];

    tmp_cmd[ 0 ] = ( SHT_READ_STATUS & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_READ_STATUS & 0x00FF;

    sht_hal_read( tmp_cmd, raw_data, 2 );

    *reg_data = raw_data[ 0 ] << 8;
    *reg_data |= raw_data[ 1 ];
}

static void sht_hal_write( uint8_t *command, uint8_t *buffer, uint16_t count)
{
  hal_i2cStart();
  hal_i2cWrite(_slaveAddress,&command[0],2,END_MODE_STOP);
}

static void sht_hal_read( uint8_t *command, uint8_t *buffer, uint16_t count)
{
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, command, 2, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, buffer, count, END_MODE_STOP );
}
/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __SHT_DRV_I2C__

void sht_i2cDriverInit(T_SHT_P gpioObj, T_SHT_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    _clk_stretching = 1;
    _repeatability = SHT_RPT_MEDIUM;
    _mps = SHT_MPS_1;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
    hal_gpio_rstSet(1);
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */

void sht_reset()
{
    _clk_stretching = 1;
    _repeatability = SHT_RPT_MEDIUM;
    _mps = SHT_MPS_1;
}

void sht_hwReset()
{
    hal_gpio_rstSet(0);
    Delay_100ms();
    hal_gpio_rstSet(1);
    Delay_100ms();
}

uint8_t sht_intGet()
{
    return hal_gpio_intGet();
}

void sht_rstSet(uint8_t state)
{
    hal_gpio_rstSet(state);
}

void sht_set_clk_strecth( uint8_t clk_stretching )
{
    _clk_stretching = clk_stretching;
}

void sht_set_repeats( uint8_t repeatability )
{
    _repeatability = repeatability;
}

void sht_set_mps( uint8_t measure_per_second )
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
        case SHT_MPS_05 :
            switch ( _repeatability )
            {
                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x32;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x24;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2F;
                break;
            }
        break;

        case SHT_MPS_1 :
            switch ( _repeatability )
            {
                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x30;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x26;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2D;
                break;
            }
        break;

        case SHT_MPS_2 :
            switch ( _repeatability )
            {
                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x36;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x20;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2B;
                break;
            }
        break;

        case SHT_MPS_4 :
            switch ( _repeatability )
            {
                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x34;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x22;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x29;
                break;
            }
        break;

        case SHT_MPS_10 :
            switch ( _repeatability )
            {
                case SHT_RPT_HIGH :
                    tmp_cmd[ 1 ] = 0x37;
                break;
                case SHT_RPT_MEDIUM :
                    tmp_cmd[ 1 ] = 0x21;
                break;
                case SHT_RPT_LOW :
                    tmp_cmd[ 1 ] = 0x2A;
                break;
            }
        break;
    }
    sht_hal_write( tmp_cmd, 0, 0 );
}

float sht_temp_pm()
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 6 ];

    tmp_cmd[ 0 ] = ( SHT_FETCH_DATA  & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_FETCH_DATA & 0x00FF;

    do  {
        sht_hal_read( tmp_cmd, raw_data, 6 );

    } while ( !_calc_crc( raw_data[ 2 ], &raw_data[ 0 ] ) );

    return _calc_temp( raw_data );
}

float sht_hum_pm()
{
    uint8_t tmp_cmd[ 2 ];
    uint8_t raw_data[ 6 ];

    tmp_cmd[ 0 ] = ( SHT_FETCH_DATA  & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_FETCH_DATA & 0x00FF;

    do {
        sht_hal_read( tmp_cmd, raw_data, 6 );

    } while ( !_calc_crc( raw_data[ 5 ], &raw_data[ 3 ] ) );

    return _calc_hum( raw_data );
}

void sht_stop_pm()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( SHT_BREAK & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_BREAK & 0x00FF;

    sht_hal_write( tmp_cmd, 0, 0 );
}

void sht_software_rst()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( SHT_SOFT_RESET & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_SOFT_RESET & 0x00FF;

    sht_hal_write( tmp_cmd, 0, 0 );
}

void sht_heater_control( uint8_t state )
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = SHT_HEATER;

    if ( state & 0x01 )
        tmp_cmd[ 1 ] = 0x6D;
    else
        tmp_cmd[ 1 ] = 0x66;

    sht_hal_write( tmp_cmd, 0, 0 );
}

void sht_clear_status()
{
    uint8_t tmp_cmd[ 2 ];

    tmp_cmd[ 0 ] = ( SHT_CLEAR_STATUS1 & 0xFF00 ) >> 8;
    tmp_cmd[ 1 ] = SHT_CLEAR_STATUS1 & 0x00FF;

    sht_hal_write( tmp_cmd, 0, 0 );
}

uint8_t sht_alert_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 15 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_heater_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 13 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_hum_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 11 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_temp_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 10 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_reset_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 4 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_cmd_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 1 ) & 0x01 ) ? 1 : 0;
}

uint8_t sht_wr_chksum_status()
{
    uint16_t status_reg;

    _read_status( &status_reg );

    return ( ( status_reg >> 1 ) & 0x01 ) ? 1 : 0;
}






/* -------------------------------------------------------------------------- */
/*
  __sht_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */
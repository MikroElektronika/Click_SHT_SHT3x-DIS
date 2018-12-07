/*
    __sht_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __sht_driver.h
@brief    SHT Driver
@mainpage SHT Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   SHT
@brief      SHT Click Driver
@{

| Global Library Prefix | **SHT** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **okt 2018.**      |
| Developer             | **Dusan Poluga**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _SHT_H_
#define _SHT_H_

/** 
 * @macro T_SHT_P
 * @brief Driver Abstract type 
 */
#define T_SHT_P    const uint8_t*

/** @defgroup SHT_COMPILE Compilation Config */              /** @{ */

//  #define   __SHT_DRV_SPI__                            /**<     @macro __SHT_DRV_SPI__  @brief SPI driver selector */
   #define   __SHT_DRV_I2C__                            /**<     @macro __SHT_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __SHT_DRV_UART__                           /**<     @macro __SHT_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup SHT_VAR Variables */                           /** @{ */

/**
  * 0.5 measurements per second 
  */
extern const uint8_t SHT_MPS_05; 

 /**
   * 1 measurements per second 
   */
extern const uint8_t SHT_MPS_1;  

/**
  * 2 measurements per second 
  */
extern const uint8_t SHT_MPS_2;  

/**
  * 4 measurements per second 
  */
extern const uint8_t SHT_MPS_4;  

/**
  * 10 measurements per second 
  */
extern const uint8_t SHT_MPS_10; 

 /**
   * High repeatability 
   */
extern const uint8_t SHT_RPT_HIGH ;

/**
  * Medium repeatability 
  */
extern const uint8_t SHT_RPT_MEDIUM;

/**
  * Low repeatability 
  */
extern const uint8_t SHT_RPT_LOW ;

/**
  * Stretching enabled 
  */
extern const uint8_t SHT_STR_ENABLE;

/**
  * Stretching disabled 
  */
extern const uint8_t SHT_STR_DISABLE;

/**
  *  Salve address 0
  */
extern const uint8_t SHT_I2C_ADDR0;

/**
  *  Salve address 1
  */
extern const uint8_t SHT_I2C_ADDR1;


                                                                       /** @} */
/** @defgroup SHT_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup SHT_INIT Driver Initialization */              /** @{ */

#ifdef   __SHT_DRV_I2C__
void sht_i2cDriverInit(T_SHT_P gpioObj, T_SHT_P i2cObj, uint8_t slave);
#endif

                                                                       /** @} */
/** @defgroup SHT_FUNC Driver Functions */                   /** @{ */

/**
  * @brief <h3>Resets device</h3>
  *
  * @par
  * Hardware reset of the device. Calling of this function will also reset the
  * all settings to defaults.
  */
void sht_reset( void );

/**
 * @brief <h3>Sets the clock stretching state</h3>
 *
 * @par
 * When a clock stretching is disabled, the sensor responds to a read header
 * with a not acknowledge (NACK), if no data is present. Otherwise sensor
 * responds to a read header with an ACK and subsequently pulls down the SCL
 * line. The SCL line is pulled down until the measurement is complete. As soon
 * as the measurement is complete, the sensor releases the SCL line and sends
 * the measurement results. By default stretching is disabled after
 * initialization.
 *
 * @note
 * This setting have influence on measurmet in single shot mode.
 *
 * @param[in] clk_stretching - ( true / false )
 */
void sht_set_clk_strecth( uint8_t clk_stretching );

/**
 * @brief <h3>Sets the repeatability value</h3>
 *
 * @par
 * Repeatability setting influences the measurement duration and thus the
 * overall energy consumption of the sensor. RPT_MEDIUM is default value after
 * initialization.
 *
 * @param[in] repeatability - ( RPT_HIGH / RPT_MEDIUM / RPT_LOW )
 */
void sht_set_repeats( uint8_t repeatability );

/**
 * @brief <h3>Measurements per Second</h3>
 *
 * @par
 * Sets the measurement per second value used for periodic type of
 * measurement.
 * <ul>
 * <li>MPS_05 - 1 measurement on every 2 seconds
 * </li>
 * <li>MPS_1 - 1 measurement per second
 * </li>
 * <li>MPS_2 - 2 measurements per second
 * </li>
 * <li>MPS_4 - 4 measurements per second
 * </li>
 * <li>MPS_10 - 10 measurements per second
 * </li>
 * </ul>
 *
 * @note
 * Initialization sets the default value to MPS_1
 *
 * @warning
 * At the highest mps setting self-heating of the sensor might occur.
 *
 * @param[in] measure_per_second - ( MPS_05 / MPS_1 / MPS_2 / MPS_4 / MPS_10 )
 */
void sht_set_mps( uint8_t measure_per_second );

/**
 * @brief <h3>Single Shot Temperature Measurement</h3>
 *
 * @par
 * Returns temperature measurement in single shot mode.
 *
 * @return ( C )
 */
float sht_temp_ss( void );

/**
 * @brief <h3>Single Shot Humidity Measurement</h3>
 *
 * @par
 * Returns humidity measurement in single shot mode.
 *
 * @return ( % )
 */
float sht_hum_ss( void );

/**
 * @brief <h3>Start Periodic Measurement</h3>
 *
 * @par
 * Starts periodic measurement with current settings.
 */
void sht_start_pm( void );

/**
 * @brief <h3>Periodic Mode Temperature</h3>
 *
 * @par
 * Returns temperature measurement in periodic mode.
 *
 * @note
 * Before function call, periodic measurement must be started by calling
 * @link sht_start_pm @endlink
 * or communication error can occurrs.
 *
 * @return ( C )
 */
float sht_temp_pm( void );

/**
 * @brief <h3>Periodic Mode Humidity</h3>
 *
 * @par
 * Returns humidity measurement in periodic mode.
 *
 * @note
 * Before function call, periodic measurement must be started by calling
 * @link sht_start_pm @endlink
 * or communication error can occurrs.
 *
 * @return ( % )
 */
float sht_hum_pm( void );

/**
 * @brief <h3>Stop Periodic Measurement</h3>
 *
 * @par
 * Stops periodic measurement instantly. This must be called before call of
 * any other function except the periodic measurement read functions.
 */
void sht_stop_pm( void );

/**
 * @brief <h3>Software Reset</h3>
 *
 * @par
 * Forces the device into a well-defined state without removing the power
 * supply. This triggers the sensor to reset its system controller and
 * reloads calibration data from the memory.
 */
void sht_software_rst( void );

/**
 * @brief <h3>Heater State</h3>
 *
 * @par
 * Sets the heater state.
 *
 * @note
 * By default heater is disabled.
 *
 * @param[in] state ( true / false )
 */
void sht_heater_control( uint8_t state );

/**
 * @brief <h3>Clears Status Register</h3>
 *
 * @par
 * The status register contains informations about the operational status of
 * the heater, the alert mode and on the execution status of the last command
 * and the last write sequence.
 */
void sht_clear_status( void );

/**
 * @brief <h3>Alert Status</h3>
 *
 * @par
 * Returns does device have pending status about any of posibile error.
 *
 * @retval FALSE - no pending status
 * @retval TRUE - at least one pending alert
 */
uint8_t sht_alert_status( void );

/**
 * @brief <h3>Heater State</h3>
 *
 * @par
 * Returns information about current heater state.
 *
 * @retval FALSE - heater off
 * @retval TRUE - heater on
 */
uint8_t sht_heater_status( void );

/**
 * @brief <h3>Humidity Alert</h3>
 *
 * @par
 * Returns does humididty tracking alert exists.
 *
 * @retval FALSE - no alert
 * @retval TRUE - alert
 */
uint8_t sht_hum_status( void );

/**
 * @brief <h3>Temperature Alert</h3>
 *
 * @par
 * Returns does temperature tracking alert exists.
 *
 * @retval FALSE - no_alert
 * @retval TRUE - alert
 */
uint8_t sht_temp_status( void );

/**
 * @brief <h3>System Reset</h3>
 *
 * @par
 * Returns information does module detected any kind of reset during current
 * power on time.
 *
 * @retval FALSE - no reset detected since last clear
 * @retval TRUE - some kind of ( soft or hard ) reset detected
 */
uint8_t sht_reset_status( void );

/**
 * @brief <h3>Command Status</h3>
 *
 * @par
 * Returns information about last command execution.
 *
 * @retval FALSE - last command executed successfully
 * @retval TRUE - last command not processed
 */
uint8_t sht_cmd_status( void );

/**
 * @brief <h3>Checksum Status</h3>
 *
 * @par
 * Returns information about last cheksum
 *
 * @retval FALSE - checksum of last write was correct
 * @retval TRUE - checksum of last write failed
 */
uint8_t sht_wr_chksum_status( void );






                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_SHT_STM.c
    @example Click_SHT_TIVA.c
    @example Click_SHT_CEC.c
    @example Click_SHT_KINETIS.c
    @example Click_SHT_MSP.c
    @example Click_SHT_PIC.c
    @example Click_SHT_PIC32.c
    @example Click_SHT_DSPIC.c
    @example Click_SHT_AVR.c
    @example Click_SHT_FT90x.c
    @example Click_SHT_STM.mbas
    @example Click_SHT_TIVA.mbas
    @example Click_SHT_CEC.mbas
    @example Click_SHT_KINETIS.mbas
    @example Click_SHT_MSP.mbas
    @example Click_SHT_PIC.mbas
    @example Click_SHT_PIC32.mbas
    @example Click_SHT_DSPIC.mbas
    @example Click_SHT_AVR.mbas
    @example Click_SHT_FT90x.mbas
    @example Click_SHT_STM.mpas
    @example Click_SHT_TIVA.mpas
    @example Click_SHT_CEC.mpas
    @example Click_SHT_KINETIS.mpas
    @example Click_SHT_MSP.mpas
    @example Click_SHT_PIC.mpas
    @example Click_SHT_PIC32.mpas
    @example Click_SHT_DSPIC.mpas
    @example Click_SHT_AVR.mpas
    @example Click_SHT_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __sht_driver.h

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
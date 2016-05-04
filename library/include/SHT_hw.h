/****************************************************************************
* Title                 :   SHT click
* Filename              :   SHT_hw.h
* Author                :   MSV
* Origin Date           :   28/01/2016
* Notes                 :   None
*****************************************************************************/
/**************************CHANGE LIST **************************************
*
*    Date    Software Version    Initials   Description 
*  28/01/16    XXXXXXXXXXX         MSV      Interface Created.
*
*****************************************************************************/
/**
 * @file SHT_hw.h
 * @brief <h3>Hardware Layer</h3>
 *
 * @par
 * Low level functions for
 * <a href="http://www.mikroe.com">MikroElektronika's</a> SHT click board.
 */

/**
 * @page LIB_INFO Library Info
 * @date 28 Jan 2016
 * @author Milos Vidojevic
 * @copyright GNU Public License
 * @version 1.0.0 - Initial testing and verification
 */

/**
 * @page TEST_CFG Test Configurations
 * <h3> Test configuration 1 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             STM32F107VC</li>
 * <li><b>Dev.Board</b> :       EasyMx Pro v7</li>
 * <li><b>Oscillator</b> :      72 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    SHT Click</li>
 * <li><b>SW</b> :              MikroC PRO for ARM 4.7.1</li>
 * </ul>
 *
 * <h3> Test configuration 2 : </h3>
 * @par
 * <ul>
 * <li><b>MCU</b> :             PIC32MX795F512L</li>
 * <li><b>Dev.Board</b> :       EasyPic Fusion v7</li>
 * <li><b>Oscillator</b> :      80 Mhz internal</li>
 * <li><b>Ext. Modules</b> :    SHT Click</li>
 * <li><b>SW</b> :              MikroC PRO for PIC 6.6.2</li>
 * </ul>
 */

/**
 * @mainpage
 * <h3>General Description</h3>
 * @par
 * SHT3x-DIS is the next generation of Sensirion’s temperature and humidity
 * sensors. It builds on a new CMOSens sensor chip that is at the heart of
 * Sensirion’s new humidity and temperature platform. The SHT3x-DIS has
 * increased intelligence, reliability and improved accuracy specifications
 * compared to its predecessor. Its functionality includes enhanced signal
 * processing, two distinctive and user selectable I2C addresses and
 * communication speeds of up to 1 MHz.
 *
 * <h3>Features</h3>
 * @par
 * <ul>
 * <li> Fully calibrated, linearized, and temperature compensated digital
 *      output</li>
 * <li> Wide supply voltage range, from 2.4 V to 5.5 V</li>
 * <li> I2C Interface with communication speeds up to 1 MHz and two user
 *      selectable addresses</li>
 * <li> Typical accuracy of 2 % RH and 0.3 °C</li>
 * <li> Very fast start-up and measurement time</li>
 * <li> Tiny 8-Pin DFN package</li>
 * </ul>
 *
 * <h3>CMOSens Technology</h3>
 * @par
 * <ul>
 * <li> High reliability and long-term stability</li>
 * <li> Industry-proven technology with a track record of more than 15
 *      years</li>
 * <li> Designed for mass production</li>
 * <li> High process capability</li>
 * <li> High signal-to-noise ratio</li>
 * </ul>
 *
 * <h3>Recommended Operating Condition</h3>
 * @par
 * The sensor shows best performance when operated within recommended normal
 * temperature and humidity range of 5 °C – 60 °C and 20 %RH – 80 %RH,
 * respectively. Long-term exposure to conditions outside normal range,
 * especially at high humidity, may temporarily offset the RH signal
 * ( e.g. +3%RH after 60h kept at >80%RH ). After returning into the normal
 * temperature and humidity range the sensor will slowly come back to
 * calibration state by itself. Prolonged exposure to extreme conditions may
 * accelerate ageing.
 *
 * <h3>I2C Communication</h3>
 * @par
 * SCL is used to synchronize the communication between microcontroller and
 * the sensor. The clock frequency can be freely chosen between 0 to 1000 kHz.
 * Commands with clock stretching according to I2C Standard 11 are supported.
 *
 * @par
 * The SDA pin is used to transfer data to and from the sensor. Communication
 * with frequencies up to 400 kHz must meet the I2C Fast Mode 11 standard.
 * Communication frequencies up to 1 Mhz are supported.
 *
 * @par
 * Through the appropriate wiring of the ADDR pin the I2C address can be
 * selected. Aside from hard wiring the ADDR pin to VDD or VSS, it is also
 * possible to use it as a selector pin. This means that the address of the
 * sensor can be changed dynamically during operation by switching the
 * level on the ADDR pin. The only constraint is that the level has to stay
 * constant starting from the I2C start condition until the communication is
 * finished. This allows to connect more than two SHT3x-DIS onto the same bus.
 * The dynamical switching requires individual ADDR lines to the sensors.
 *
 * <ul>
 * <li> I2C address 0 - 0x44 - ADDR connected to Vss</li>
 * <li> I2C address 1 - 0x45 - ADDR connected to Vdd</li>
 * </ul>
 *
 * <h3>Reset pin</h3>
 * @par
 * The RST pin may be used to generate a reset of the sensor. A minimum
 * pulse duration of 350 ns is required to reliably trigger a reset of the
 * sensor.
 *
 * <h3>Interrupt pin</h3>
 * @par
 * The INT pin may be used to connect to the interrupt pin of a microcontroller.
 * The output of the pin depends on the value of the RH/T reading relative to
 * programmable limits.The pin switches high, when alert conditions are met.
 * Be aware that self-heating might occur, depending on the amount of current
 * that flows. Self-heating can be prevented if the INT Pin is only used
 * to switch a transistor.
 *
 * <h3>Single Shot Data Acquistion Mode</h3>
 * @par
 * In this mode one issued measurement command triggers the acquisition of one
 * data pair. Each data pair consists of one 16 bit temperature and one 16 bit
 * humidity value ( in this order ). During transmission each data value is
 * always followed by a CRC checksum.
 *
 * <h3>Periodic Data Acquisition Mode</h3>
 * @par
 * In this mode one issued measurement command yields a stream of data pairs.
 * Each data pair consists of one 16 bit temperature and one 16 bit humidity
 * value. Upon reception of the break command the sensor will finish the
 * ongoing measurement and enter the single shot mode.
 *
 * <h3>Schematic</h3>
 * @image html schematic.jpg width=20
 */
#ifndef SHT_HW_H_
#define SHT_HW_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
/**
 * Polynomial for crc calculation */
#define CRC_POLYNOMIAL                                          0x31
/**
 * Fetch data command */
#define FETCH_DATA                                              0xE000
/**
 * Periodic art command */
#define PERIODIC_ART                                            0x2B32
/**
 * Break command */
#define BREAK                                                   0x3093
/**
 * Software reset command */
#define SOFT_RESET                                              0x30A2
/**
 * Heater command */
#define HEATER                                                  0x30
/**
 * Read status register command */
#define READ_STATUS                                             0xF32D
/**
 * Clear status register command */
#define CLEAR_STATUS                                            0x3041
/******************************************************************************
* Configuration Constants
*******************************************************************************/

/******************************************************************************
* Macros
*******************************************************************************/
        
/******************************************************************************
* Typedefs
*******************************************************************************/
/**
 * @enum RPT_t
 * @brief Repeatability values
 */
typedef enum
{
    /**
     * High repeatability */
    RPT_HIGH,
    /**
     * Medium repeatability */
    RPT_MEDIUM,
    /**
     * Low repeatability */
    RPT_LOW

}RPT_t;

/**
 * @enum STR_t
 * @brief Clock stretching states
 */
typedef enum
{
    /**
     * Stretching enabled */
    STR_ENABLE                                                  = 0x2C,
    /**
     * Stretching disabled */
    STR_DISABLE                                                 = 0x24
}
STR_t;

/**
 * @enum MPS_t
 * @brief Measurements per second values
 */
typedef enum
{
    /**
     * 0.5 measurements per second */
    MPS_05                                                      = 0x20,
    /**
     * 1 measurements per second */
    MPS_1                                                       = 0x21,
    /**
     * 2 measurements per second */
    MPS_2                                                       = 0x22,
    /**
     * 4 measurements per second */
    MPS_4                                                       = 0x23,
    /**
     * 10 measurements per second */
    MPS_10                                                      = 0x27

}MPS_t;
/******************************************************************************
* Variables
*******************************************************************************/

/******************************************************************************
* Function Prototypes
*******************************************************************************/
#ifdef __cplusplus
extern "C"{
#endif

/**
 * @brief <h3>Click board initialization</h3>
 *
 * @par
 * Prepares library for usage and sets repeatability, clock stretching and
 * measurement per second values to default.
 *
 * @note
 * This function must be called first.
 *
 * @param[in] i2c_address - ( 0x44 / 0x45 )
 */
void sht_init( uint8_t i2c_address );

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
void sht_set_clk_strecth( bool clk_stretching );

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
void sht_set_repeats( RPT_t repeatability );

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
void sht_set_mps( MPS_t measure_per_second );

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
void sht_heater_control( bool state );

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
bool sht_alert_status( void );

/**
 * @brief <h3>Heater State</h3>
 *
 * @par
 * Returns information about current heater state.
 *
 * @retval FALSE - heater off
 * @retval TRUE - heater on
 */
bool sht_heater_status( void );

/**
 * @brief <h3>Humidity Alert</h3>
 *
 * @par
 * Returns does humididty tracking alert exists.
 *
 * @retval FALSE - no alert
 * @retval TRUE - alert
 */
bool sht_hum_status( void );

/**
 * @brief <h3>Temperature Alert</h3>
 *
 * @par
 * Returns does temperature tracking alert exists.
 *
 * @retval FALSE - no_alert
 * @retval TRUE - alert
 */
bool sht_temp_status( void );

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
bool sht_reset_status( void );

/**
 * @brief <h3>Command Status</h3>
 *
 * @par
 * Returns information about last command execution.
 *
 * @retval FALSE - last command executed successfully
 * @retval TRUE - last command not processed
 */
bool sht_cmd_status( void );

/**
 * @brief <h3>Checksum Status</h3>
 *
 * @par
 * Returns information about last cheksum
 *
 * @retval FALSE - checksum of last write was correct
 * @retval TRUE - checksum of last write failed
 */
bool sht_wr_chksum_status( void );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* SHT_HW_H_ */

/*** End of File ************************p**************************************/

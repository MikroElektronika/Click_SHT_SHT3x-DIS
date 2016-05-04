/****************************************************************************
* Title                 :   SHT click
* Filename              :   SHT_hal.h
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
 * @file SHT_hal.h
 * @brief <h2> HAL layer </h2>
 *
 * @par
 * HAL layer for <a href="http://www.mikroe.com">MikroElektronika's</a>
 * SHT click board.
 */
#ifndef SHT_HAL_H_
#define SHT_HAL_H_
/******************************************************************************
* Includes
*******************************************************************************/
#include "stdint.h"
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/
//#define STM32
//#define LM
//#define TM

#define ATMEGA
//#define ATXMEGA
/******************************************************************************
* Configuration Constants
*******************************************************************************/
/**
 * Register address size */
#define COMMAND_SIZE            2
/**
 * Maximum buffer size */
#define MAX_BUFF_SIZE           256
/******************************************************************************
* Macros
*******************************************************************************/
        
/******************************************************************************
* Typedefs
*******************************************************************************/

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
 * @brief <h3>HAL Initialization</h3>
 *
 * @par
 * Initialization of HAL layer used to initialize I2C connection and pins needed
 * for proper usage of click board.
 *
 * @param[in] address_id - hardware address
 */
void sht_hal_init( uint8_t address_id );

/**
 * @brief <h3>HAL Reset</h3>
 *
 * @par
 * Resets the module using
 * @link SHT_RST_PIN @endlink .
 */
void sht_hal_reset( void );

/**
 * @brief <h3>HAL Write</h3>
 *
 * @par
 * Generic write function adapted for SHT click.
 *
 * @param[in] command - register address
 * @param[in] buffer - data buffer
 * @param[in] count - data size in bytes
 */
void sht_hal_write( uint8_t *command,
                    uint8_t *buffer,
                    uint8_t count );

/**
 * @brief <h3>HAL Read</h3>
 *
 * @par
 * Generic read function adapted for SHT click.
 *
 * @param[in] command - register address
 * @param[out] buffer - data buffer
 * @param[in] count - data size in bytes
 */
void sht_hal_read( uint8_t *command,
                   uint8_t *buffer,
                   uint8_t count );

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* SHT_HAL_H_ */

/*** End of File **************************************************************/
/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

// TODO Insert appropriate #include <>

// TODO Insert C++ class definitions if appropriate

// TODO Insert declarations

// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation


/* Exported constants ---------------------------------------------------------*/
/************************************************************************************************************************/
#define VOUT_TARGET ((uint16_t) 5000) // This is the user VOUT voltage target in mV that DC/DC converter will apply on V output
/************************************************************************************************************************/
#define BUCK_PWM_PERIOD ((uint16_t) 18432) /* 250kHz */
#define REAL_3V3 ((uint16_t) 3300) /* Measure 3V3 of application and enter it as reference in mV (default value is 3300) */
#define VIN_RESISTOR_RATIO  ((uint16_t) 2012) /* theoretical bridge resistor Vin ratio (6.8K/(6.8K + 27K))*10000: can be adjusted if needed by measuring the real resistors ratio */
#define VOUT_RESISTOR_RATIO  ((uint16_t) 1988) /* theoretical bridge resistor Vout ratio (3.3K/(3.3K + 13.3K))*10000: can be adjusted if needed by measuring the real resistors ratio */

/***************************** DO NOT MODIFY ********************************/
#define MIN_DUTY_A ((int32_t)(BUCK_PWM_PERIOD * 15)/100) // % MinDuty for Buck
#define MAX_DUTY_A ((int32_t)(BUCK_PWM_PERIOD * 90)/100) // % MaxDuty for Buck

#define MIN_DUTY_B ((int32_t)(BUCK_PWM_PERIOD * 5)/100) // % MinDuty for Boost
#define MAX_DUTY_B ((int32_t)(BUCK_PWM_PERIOD * 90)/100) // % MaxDuty for Boost

#define MIN_DUTY_B_MIXED ((int32_t)(BUCK_PWM_PERIOD * 5)/100) // % MinDuty for Mixed
#define MAX_DUTY_B_MIXED ((int32_t)(BUCK_PWM_PERIOD * 45)/100) // % MaxDuty for Mixed

#define SAT_LIMIT ((int32_t)(BUCK_PWM_PERIOD * 50)/100) // PI Integral term saturation value
/****************************************************************************/

/* Compute Vin & Vout, Min 3V, Max 15V with 100mV margin, other corrections are due to resistors bridges and real 3V3 of application */
#define VINMIN          ((uint32_t) (((2900  * VIN_RESISTOR_RATIO) /10000) * 0x1000) / REAL_3V3)  // Minimum admissible Vin = 3V in mV
#define VINMAX          ((uint32_t) (((15100 * VIN_RESISTOR_RATIO) /10000) * 0x1000) / REAL_3V3)  // Maximum admissible Vin = 15V in mV
#define VOUTMIN         ((uint32_t) (((2900  * VOUT_RESISTOR_RATIO) /10000) * 0x1000) / REAL_3V3)// Minimum admissible Vout = 3V in mV
#define VOUTMAX         ((uint32_t) (((15100 * VOUT_RESISTOR_RATIO) /10000) * 0x1000) / REAL_3V3) // Maximum admissible Vout = 15V in mV

#define DT_RISING       ((uint16_t)230) // Dead time rising edge
#define DT_FALLING      ((uint16_t)230) // Dead time falling edge

#define MAX_ERROR     ((uint16_t)1000) // Max number of repetitive errors
#define MAX_RANGE     ((uint16_t)20000) // Max number of repetitive Out of Range Vin or Vout conditions
#define MAX_OVERLOAD  ((uint16_t)100) // Max number of repetitive Overload conditions (X * 1.6ms reaction time)
#define OVERLOAD_MARGIN ((uint16_t)99) // % Margin between standard operation and overload start conditions

/* Exported macro ------------------------------------------------------------*/

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */


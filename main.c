/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.169.0
        Device            :  dsPIC33EP32MC204
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB 	          :  MPLAB X v5.40
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/
#include <libpic30.h>

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr2.h"
#include "mcc_generated_files/tmr3.h"

/*
                         Main application
 */
//#include "stdio.h"
#include "dsp.h"
//#include "defines.h"
//#include "sineTable.h"
#include "libq.h"

#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/uart1.h"


// Full Bridge Duty Cycle
#define FULLBRIDGE_PERIOD               3000      // 20KHz Center Aligne
#define FULLBRIDGE_MIN_DUTY             (FULLBRIDGE_PERIOD * 20)/100  // 20 Percent
#define FULLBRIDGE_MAX_DUTY             (FULLBRIDGE_PERIOD * 90)/100  // 90 Percent
#define FULLBRIDGE_DUTY_MIN_LIMIT         10
#define FULLBRIDGE_DUTY_MAX_LIMIT       3000

// ----------------- 
/* Q15 Format */
// DC InputCurrent
#define BATTERY_OVERCURRENT_1A           412        //  1.00 A
#define BATTERY_OVERCURRENT_2A           824        //  2.00 A
#define BATTERY_OVERCURRENT_5A          2060        //  5.00 A
#define BATTERY_OVERCURRENT_10A         4120        // 10.00 A
#define BATTERY_OVERCURRENT_20A         8241        // 20.00 A

#define BATTERY_OVERCURRENT_25A        10300        // 25.00 A
#define BATTERY_OVERCURRENT_30A        12360        // 30.00 A
#define BATTERY_OVERCURRENT_35A        14420        // 35.00 A
#define BATTERY_OVERCURRENT_40A        16480        // 40.00 A
#define BATTERY_OVERCURRENT_45A        18540        // 45.00 A
#define BATTERY_OVERCURRENT_50A        20600        // 50.00 A
#define BATTERY_OVERCURRENT_55A        22660        // 55.00 A

// DC InputVoltage
// 7.5k / (120k + 7.5k) * 27 = 1.588 , (1.588 * 1024)/3.3 = 492 * 32 = 15770
#define BATTERY_OVERVOLTAGE_LIMIT       15770       // 27.00 V
#define BATTERY_OVERVOLTAGE_HYST        14602       // 25.00 V

#define BATTERY_UNDERVOLTAGE_HYST       12850       // 22.00 V
#define BATTERY_UNDERVOLTAGE_LIMIT      11682       // 20.00 V

// AC OutputCurrent
#define OUTPUT_OVERCURRENT_0A5            328        //  0.50 A
#define OUTPUT_OVERCURRENT_1A             655        //  1.00 A
#define OUTPUT_OVERCURRENT_2A            1310        //  2.00 A
#define OUTPUT_OVERCURRENT_3A            1966        //  3.00 A
#define OUTPUT_OVERCURRENT_4A            2610        //  4.00 A
#define OUTPUT_OVERCURRENT_5A            3276        //  5.00 A
#define OUTPUT_OVERCURRENT_5A5           3604        //  5.50 A
#define OUTPUT_OVERCURRENT_6A            3932        //  6.00 A
#define OUTPUT_OVERCURRENT_6A5           4259        //  6.50 A
#define OUTPUT_OVERCURRENT_7A            4587        //  7.00 A
#define OUTPUT_OVERCURRENT_7A5           4915        //  7.50 A
#define OUTPUT_OVERCURRENT_8A            5242        //  8.00 A
#define OUTPUT_OVERCURRENT_8A5           5570        //  8.50 A
#define OUTPUT_OVERCURRENT_9A            5898        //  9.00 A

#define OUTPUT_CURRENT_0A5              16712    //  0.50 A
#define OUTPUT_CURRENT_1A               17040    //  1.00 A
#define OUTPUT_CURRENT_2A               17695    //  2.00 A
#define OUTPUT_CURRENT_3A               18350    //  3.00 A
#define OUTPUT_CURRENT_4A               19000    //  4.00 A
#define OUTPUT_CURRENT_4A5              19333    //  4.50 A
#define OUTPUT_CURRENT_5A               19660    //  5.00 A
#define OUTPUT_CURRENT_5A5              19988    //  5.50 A
#define OUTPUT_CURRENT_6A               20316    //  6.00 A
#define OUTPUT_CURRENT_7A               20970    //  7.00 A


// AC OutputVoltage +/- 10%
#define VAC_MORMAL                      16696      // 220.00 V
#define VAC_OVER                        18366      // 242.00 V
#define VAC_UNDER                       15027      // 198.00 V

// Temperature
#define TEMP_45_C                        9433      // 45 Degree
#define TEMP_50_C                        9929      // 50 Degree
#define TEMP_60_C                       10922      // 60 Degree
#define TEMP_70_C                       11915      // 70 Degree
#define TEMP_85_C                       13405      // 85 Degree

#define TEMPERATURE_HYS                   992      // 10 Degree

//***********************
#define THERMOSTAT_OFF                      0      // 
#define THERMOSTAT_ON                       1      // Transformer Overtemperature

// Relay
#define DRV_ALL_OFF                          0
#define DRV_NORMAL                           1
#define DRV_ERROR                            2
#define DRV_BYPSS                            3

#define RY_INRUSH_ON                        RY_SS_SetHigh()     
#define RY_INRUSH_OFF                       RY_SS_SetLow()

#define RY_BYPSS_ON                         RY_OUTPUT_SetHigh()
#define RY_BYPSS_OFF                        RY_OUTPUT_SetLow()

#define FAN_ON                              FAN_SetHigh()
#define FAN_OFF                             FAN_SetLow()
// LED Indicator
#define LD_RUN_ON                           LED3_SetLow()
#define LD_RUN_OFF                          LED3_SetHigh()
#define LD_RUN_TOGGLE                       LED3_Toggle()

#define LD_FAULT_ON                         LED2_SetLow()
#define LD_FAULT_OFF                        LED2_SetHigh()
#define LD_FAULT_TOGGLE                     LED2_Toggle()

#define LD_BYPSS_ON                         LED4_SetLow()
#define LD_BYPSS_OFF                        LED4_SetHigh()
#define LD_BYPSS_TOGGLE                     LED4_Toggle()

// displayState
#define DISP_OFF_ALL                        0
#define DISP_STARTUP                        1
#define DISP_NORMAL                         2
#define DISP_ERROR                          3
#define DISP_BYPASS                         4
#define DISP_RESTART                        5

#define NUMSAMPLES                        400

#define LOGIC_L                             0
#define LOGIC_H                             1

#define TRUE                                1
#define FALSE                               0

#define ON                                  1
#define OFF                                 0

// Input Switch State
#define SWITCHOFF                           0
#define SWITCHON                            1

// Fault Act knowledge
#define SD_CLEAR                            0 
#define SD_DETECTED                         1

#define FLT1_CLEAR                          0
#define FLT1_DETECTED                       1

// System State 
#define SYSTEM_ERROR                        0
#define SYSTEM_STARTUP                      1
#define SYSTEM_RUN                          2

#define STATE_STARTUP                       0
#define STATE_NORMAL                        1
#define STATE_ERROR                         2   // default state

//------- Faults
#define FAULT_CLEAR                         0 //

#define FAULT_OVER_VOLTAGE                  1 //
#define FAULT_UNDER_VOLTAGE                 2 //
#define FAULT_OVER_VOLTAGE_OP               3 //

#define FAULT_OVER_CURRENT_IP               4 //
#define FAULT_OVER_CURRENT_OP               5 //
#define FAULT_OVER_LOAD                     6
#define FAULT_OVER_TEMP                     7 //
#define FAULT_OVER_TEMP_TRFMR               8 //

#define FAULT_HW_FLT1                       9 
#define FAULT_HW_VOLTAGE                   10
#define FAULT_HW_CURRENT                   11

#define TOTAL_FAULT                        11

//------- Full Bridge Drive 
#define FULLBRIDGE_AH_BL_ACTIVE             0
#define FULLBRIDGE_2ND_INACTIVE             1
#define FULLBRIDGE_AL_BH_ACTIVE             2
#define FULLBRIDGE_4TH_INACTIVE             3//


// Cnt for Timer 2 (10 KHz) = 100 uS
#define COUNTRESTART                        10000  // 1Sec
#define CRITICALFAULTCOUNT                  20000  // 2Sec

#define CNT_RESET                           0

#define CNT_1MS                             10
#define CNT_2MS                             20
#define CNT_3MS                             30
#define CNT_4MS                             40
#define CNT_5MS                             50

#define CNT_10MS                            100
#define CNT_20MS                            200
#define CNT_30MS                            300
#define CNT_40MS                            400
#define CNT_50MS                            500

#define CNT_100MS                           1000
#define CNT_150MS                           1500
#define CNT_200MS                           2000
#define CNT_300MS                           3000
#define CNT_400MS                           4000
#define CNT_500MS                           5000

#define CNT_1SEC                            10000
#define CNT_2SEC                            20000
#define CNT_3SEC                            30000
#define CNT_4SEC                            40000
#define CNT_5SEC                            50000

// Structure
// TMR3  ISR = 50  uS > ADC Trigger > ADC ISR
// TMR2  ISR = 100 uS > StateMachine, Fault Management, Indicator
// FLT1  if FLT1 Detected Hardware Faults

// PID
void init_outputVoltageLoop(void);   
void outputVoltageLoop(void);
void OutputSoftStartRoutine(void);

// FullBridge
void FullBridgeDrive(void);

// 
void InitValue(void);
void FaultCheck(void);
void UpdateParameter(void);
void SentParameters(void);

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void Delay_ms(uint16_t d);
/* ~~~~~~~~~~~~~~~~~~~~~~  PID Variable Definitions  ~~~~~~~~~~~~~~~~~~~~~~~ */

/* Variable Declaration required for each PID controller in the application */

tPID pfcVoltagePID;
tPID pfcCurrentPID;

tPID outputVoltagePID;  // kritsana

fractional SFRAC16control;
fractional readTempQ15;

/* These data structures contain a pointer to derived coefficients in X-space and 
   pointer to controler state (history) samples in Y-space. So declare variables 
   for the derived coefficients and the controller history samples */

fractional outputVoltageABC[3] __attribute__ ((section (".xbss, bss, xmemory")));      // Coefficients
fractional outputVoltageHistory[3] __attribute__ ((section (".ybss, bss, ymemory")));  // History

/* AC Voltage PID Information */
//      (int)(32767*(X) + 0.5)) 
#define PID_OUTPUTVOLTAGE_KP   0.2//0.38
#define PID_OUTPUTVOLTAGE_KI   0.06
#define PID_OUTPUTVOLTAGE_KD   0

// Coefficients
// A = Kp + Ki + Kd
#define PID_OUTPUTVOLTAGE_A Q15(PID_OUTPUTVOLTAGE_KP + PID_OUTPUTVOLTAGE_KI + PID_OUTPUTVOLTAGE_KD)
// B = (-Kp + 2*Kd)
#define PID_OUTPUTVOLTAGE_B Q15(-1 *(PID_OUTPUTVOLTAGE_KP + 2 * PID_OUTPUTVOLTAGE_KD))
// C = Kd
#define PID_OUTPUTVOLTAGE_C Q15(PID_OUTPUTVOLTAGE_KD)

      
#define PID_OUTPUTVOLTAGE_REFERENCE  6300			 
#define PID_OUTPUTVOLTAGE_MIN 	  0			  
#define VOLTAGE_SOFTSTART_INCREMENT	 ((PID_OUTPUTVOLTAGE_REFERENCE - PID_OUTPUTVOLTAGE_MIN) / 500 ) 
#define OUTPUTSOFTSTART_INCREMENT  1


// State
                                    //     0,        1,   2
uint8_t systemState = SYSTEM_ERROR; // Error, Start-Up, Run
uint8_t faultState = 0;
uint8_t faultData = 0;
uint8_t hardwareFault = 0;
uint8_t driveState = DRV_ALL_OFF;
uint8_t switchState = SWITCHOFF;
uint8_t thermoState = THERMOSTAT_OFF;
uint8_t displayState = DISP_OFF_ALL;
uint8_t fullBridgeState = FULLBRIDGE_AH_BL_ACTIVE;


uint8_t vbattOverVoltageFlag = 0;  
uint8_t vbattUnderVoltageFlag = 0;
uint8_t outputOverVoltageFlag = 0;

uint8_t inputOverCurrentFlag = 0;
uint8_t outputOverCurrentFlag = 0;

uint8_t outputOverloadFlag = 0;
uint8_t pcbTemperatureOverFlag = 0;
uint8_t extTemperatureOverFlag = 0;
uint8_t HardwareFaultFlag = 0;


// Input/Output Variable
bool SW1Value, SW2Value, PWRONValue, SD_Voltage, SD_Current;  // Low speed
bool output_fan, output_softstart, output_ac;

// Flag
uint8_t  startFullBridgeFlag = 0; 
uint8_t  Flag_180Degree = 0;
uint8_t  Flag_Ref_Update =0;
uint8_t  Flag_UpdatePercenMod =0;
uint8_t  Flag_Capture_currentOffset =0;

uint8_t  criticalFaultRestartFlag =0;
uint8_t  criticalFaultFlag =0;
uint16_t acCurrentOffsetFlag =0;

//------ Counter Refer Timer2 Interrupt 100 uS
uint16_t  Cnt_ms;
uint16_t  Count_1mS = 0;
uint16_t  Count_20mS = 0;
uint16_t  Count_200mS = 0;

uint16_t  cntLEDTick=0;
uint16_t  cntToggle =0;
uint16_t  CntStable =0;
uint16_t  CntTransError =0;

uint16_t  systemRestartCounter =0;

uint16_t  Fault_Count_InputUnderVoltage = 0;
uint16_t  Fault_Count_InputOverVoltage = 0;
uint16_t  Fault_Count_OutputOverVoltage = 0;

uint16_t  Fault_Count_InputOverCurrent = 0;
uint16_t  Fault_Count_OutputOverCurrent = 0;

uint16_t  Fault_Count_PCBOverTemperature = 0;
uint16_t  Fault_Count_extOvertemperature = 0;
uint16_t  Fault_Count_OutputOverload = 0;
uint16_t  Fault_Count_FLT1 = 0;

uint16_t  criticalFaultCounter =0;

//--- Record Fault In system
uint16_t  countOverVoltage =0;
uint16_t  countUnderVoltage =0;
uint16_t  countOverVoltageOutput =0;
uint16_t  countOverCurrentInput =0;
uint16_t  countOverCurrentOutput =0;
uint16_t  countOverload =0;
uint16_t  countPCBOvertemperature =0;
uint16_t  countTransfmrOvertemp = 0;
uint16_t  countFlt1 =0;
uint16_t  countFanOn = 0;
uint16_t  Sampling_Count_SineWave = 0; // Sine Table Look up

uint16_t  PercentModulation = 0; // 0 - 100 %  ... (CurrentDuty * PercentModulation)/100
uint16_t  Buff_Period;
uint32_t  Buff_Duty;
uint16_t  DutyCycle;

//------ ADC
// ADC-CH      AN0,       AN1,     AN2,     AN3,      AN6
uint16_t adc_ibatt, adc_vbatt, adc_iout, adc_vout, adc_temperature;
uint16_t adc_avg_currentInput, adc_avg_voltageInput, adc_avg_voltageOutput, adc_avg_currentOutput, adc_avg_pcbTemp;
uint32_t sum_ch0, sum_ch1, sum_ch2, sum_ch3, sum_ch4;
uint16_t sampl_ch0, sampl_ch1, sampl_ch2, sampl_ch3, sampl_ch4;

uint16_t adc_offset0, adc_offset1, adc_offset2, adc_offset3, adc_offset4;
uint16_t iout_mv_u16;  // avg value - initial value
uint16_t delta_adc_iin;
int16_t  delta_adc_iout;
uint16_t abs_delta_currentOutput;

// acCurrent
int16_t  inverterOutputCurrent =0;
int16_t  acCurrentOffset =0;
int16_t  rectifiedInverterOutputCurrent = 0, peakInverterOutputVoltage = 0;
uint16_t inverterOutputOverCurrent;
uint32_t acCurrentOffsetAverage =0;
uint16_t acCurrentOffsetCounter =0;

// AC Current Variables and Moving Avg Variables/Array
uint16_t averageRectifiedCurrent = 0, maxInverterOutputCurrent = 0; 
uint16_t rectifiedInverterOutputCurrentArray[8] = {0,0,0,0,0,0,0,0}; // 8
uint32_t rectifiedInverterOutputCurrentSum = 0;
uint8_t  currentArrayCnt =0;

float iin_mv, vin_mv, vout_mv, iout_mv, temp_mv;        
float iin_mA, vin, vout, iout_mA, temp_c;
uint16_t vbatt_u16, ibatt_u16, vout_u16, iout_u16, temp_u16; // Display

unsigned int OutputVoltageReference = 0;
unsigned int xxx;
/*
const unsigned int sineTable_10KHz[100] = {  // 10KHz // 6000 u16 ,  Center Align
   0,  188,  377,  565,  752,  939, 1124, 1309, 1492, 1674,
1854, 2032, 2209, 2383, 2555, 2724, 2891, 3054, 3215, 3373,
3527, 3677, 3825, 3968, 4107, 4243, 4374, 4501, 4623, 4741,
4854, 4962, 5066, 5164, 5258, 5346, 5429, 5507, 5579, 5645,
5706, 5762, 5811, 5856, 5894, 5926, 5953, 5973, 5988, 5997,
6000, 5997, 5988, 5973, 5953, 5926, 5894, 5856, 5811, 5762,  
5706, 5645, 5579, 5507, 5429, 5346, 5258, 5164, 5066, 4962, 
4854, 4741, 4623, 4501, 4374, 4243, 4107, 3968, 3825, 3677,   
3527, 3373, 3215, 3054, 2891, 2724, 2555, 2383, 2209, 2032,   
1854, 1674, 1492, 1309, 1124,  939,  752,  565,  377,  188
};
*/

const unsigned int sineTable_20KHz[200] = {  // 20KHz // 3000 u16 ,  Center Align
       //47
   0,   0,   0,  141,  188,  235,  282,  329,  375,  422,
 469,  515,  562,  608,  654,  700,  746,  791,  836,  882,
 927,  971, 1016, 1060, 1104, 1148, 1191, 1234, 1277, 1319,
1361, 1403, 1445, 1486, 1527, 1567, 1607, 1647, 1686, 1725,
1763, 1801, 1838, 1875, 1912, 1948, 1983, 2019, 2053, 2087,
2121, 2154, 2186, 2218, 2250, 2281, 2311, 2341, 2370, 2399,
2427, 2454, 2481, 2507, 2532, 2557, 2582, 2605, 2628, 2651,
2673, 2694, 2714, 2734, 2753, 2771, 2789, 2806, 2822, 2838,
2853, 2867, 2880, 2893, 2905, 2917, 2927, 2937, 2946, 2955,
2963, 2970, 2976, 2981, 2986, 2990, 2994, 2996, 2998, 2999,
3000, 2999, 2998, 2996, 2994, 2990, 2986, 2981, 2976, 2970,
2963, 2955, 2946, 2937, 2927, 2917, 2905, 2893, 2880, 2867,
2853, 2838, 2822, 2806, 2789, 2771, 2753, 2734, 2714, 2694,
2673, 2651, 2628, 2605, 2582, 2557, 2532, 2507, 2481, 2454,
2427, 2399, 2370, 2341, 2311, 2281, 2250, 2218, 2186, 2154,
2121, 2087, 2053, 2019, 1983, 1948, 1912, 1875, 1838, 1801,
1763, 1725, 1686, 1647, 1607, 1567, 1527, 1486, 1445, 1403,
1361, 1319, 1277, 1234, 1191, 1148, 1104, 1060, 1016,  971,
 927,  882,  836,  791,  746,  700,  654,  608,  562,  515,
 469,  422,  375,  329,  282,  235,  188,  141,    0,   0

};

//-------- ISR ----------

// Interrupt Timer 3 
// Highest Priority
void PriorityHigh()  // TMR3 = 50uS = 20KHz
{   
    ClrWdt();
    
    Sampling_Count_SineWave++;  
    
    if(Sampling_Count_SineWave > 199)  // 20KHz // 200 * 0.005mS = 10mS = 180 Degree
    { 
      
      Sampling_Count_SineWave =0;
      Flag_180Degree = ON;
      Flag_Ref_Update = ON;
      Flag_Capture_currentOffset = ON;
      outputVoltageLoop();
           
    }
    
    UpdateParameter();
    
    if(startFullBridgeFlag == 1)
    {
        FullBridgeDrive();
    }
    else // 0
    {
        PTCONbits.PTEN = false;   // Disable PWM Module        
    }
       
    Count_1mS++;
    if(Count_1mS > 20) // 1 mS
    {   Count_1mS = 0;
               
        if(Cnt_ms > 0) Cnt_ms--;
                
    }
    
    
}

// Interrupt Timer 2
// High Priority
void PriorityMedium()  // TMR2 = 100uS = 10KHz
{   
       
    FaultCheck();  // return fault state 
      
    if(faultState != FAULT_CLEAR) // if any fault detected systems = Error State
    {
       systemState = STATE_ERROR;
    }

    //--------------------------------------------------------
    
    SW1Value   = SW1_GetValue();  // RA10  
    SW2Value   = SW2_GetValue();  // RA7   
    PWRONValue = PWR_GetValue();  // RA4  
    
    SD_Voltage = OUVP_GetValue(); // RB9
    SD_Current = OCP_GetValue();  // RC6
    
    if(PWRONValue == 1) // High Level
    {
        switchState = SWITCHON;
    }
    else // Low level
    {
        switchState = SWITCHOFF;
        systemState = STATE_ERROR;
    }
    
    if(SW1Value == 1) // External Thermostat Close // NO = 0, NC = 1
    {
        thermoState = THERMOSTAT_ON;    // High Level
    }
    else // Low level
    {
        thermoState = THERMOSTAT_OFF;
    }
    /* 
    //  Reserved
    if(SW2Value == FALSE)
        {   

        }
    else 
        {    

        }    
    
    if(SD_Voltage == SD_DETECTED)
        {   

        }
    else // SD_CLEAR
        {    

        }  
     
    if(SD_Current == SD_DETECTED)
        {   

        }
    else // SD_CLEAR
        {    

        }    
    */
    
    //---- systemState ----
    switch(systemState)
    {
        case STATE_STARTUP: // 0
        {   
            
            // Read AC Current offset during startup mode and verify data
            // Needs to be completed before the full-bridge is enabled during system startup
            if(acCurrentOffsetFlag == 0)
            {
                //acCurrentOffsetAverage = acCurrentOffsetAverage + inverterOutputCurrent;
                //acCurrentOffsetAverage = acCurrentOffsetAverage + inverterOutputCurrent;
                acCurrentOffset = adc_avg_currentOutput;
                
                if(Flag_Capture_currentOffset == ON) // Zero degree
                {   
                    Flag_Capture_currentOffset = 0;
                    //acCurrentOffset = (acCurrentOffsetAverage >> 8);
                    //acCurrentOffset = adc_avg_currentOutput;       // 16383 - 16428
                    inverterOutputOverCurrent = OUTPUT_OVERCURRENT_6A + ((int16_t)(16383 - acCurrentOffset));
                    acCurrentOffsetFlag = 1;
                    
                    //acCurrentOffsetAverage = 0;
                    
                }
            }
            
            startFullBridgeFlag = 1;
            
            PTCONbits.PTEN = true;      // Enable PWM Module
            displayState = DISP_STARTUP;
            OutputSoftStartRoutine();   // until voltage output = Setpoint
                       
            systemState = STATE_NORMAL;
        }
        break;
        
        case STATE_NORMAL: // 1
        {   
            displayState = DISP_NORMAL;
            driveState = DRV_NORMAL;
        }
        break;
        
        case STATE_ERROR : // 2 , default
        {   
            ClrWdt();  // clear watchdog timer every 31 mS
            
            SFRAC16control = 0;
            acCurrentOffsetFlag = 0;
            startFullBridgeFlag = 0;  // clear Full bridge flag
            MDC = 0;                  // Master Duty Cycle = 0
            PTCONbits.PTEN = false;   // Disable PWM Module
            driveState = DRV_ERROR;
            
            RY_INRUSH_OFF;
            // restart
            if((switchState == SWITCHON)&&(faultState == FAULT_CLEAR))
            {
                systemRestartCounter++;
                displayState = DISP_RESTART;
                
                if(systemRestartCounter >= COUNTRESTART)
                {   
                    init_outputVoltageLoop();  // clear PID Parameter 
                                   
                    RY_BYPSS_OFF;
                    systemState = STATE_STARTUP;
                    systemRestartCounter = 0;
                }               
            }
            
            // Fault Recording 
            else if((switchState == SWITCHON)&&(faultState != FAULT_CLEAR))
            {   
                systemRestartCounter =0;
                            
                if(faultState == FAULT_OVER_VOLTAGE) countOverVoltage++;
                else if(faultState == FAULT_UNDER_VOLTAGE) countUnderVoltage++;
                else if(faultState == FAULT_OVER_VOLTAGE_OP) countOverVoltageOutput++;
                else if(faultState == FAULT_OVER_CURRENT_IP) countOverCurrentInput++;
                else if(faultState == FAULT_OVER_CURRENT_OP) countOverCurrentOutput++;
                else if(faultState == FAULT_OVER_LOAD) countOverload++;
                else if(faultState == FAULT_OVER_TEMP) countPCBOvertemperature++;
                else if(faultState == FAULT_OVER_TEMP_TRFMR) countTransfmrOvertemp++;
                else if(faultState == FAULT_HW_FLT1) countFlt1++;
                else faultState = FAULT_CLEAR;
                
                // Critical Faults: AC Current, Flyback Over Voltage, and Flyback Over Current
                // Handle faults differently: Allow system to try to restart only once, if fault
                // is still present then disable PWM module.
                if((criticalFaultFlag == 1) && (criticalFaultRestartFlag == 0))
                {
                    criticalFaultCounter++;

                    // After 2s remove the critical fault and allow system to try to restart
                    if(criticalFaultCounter > CRITICALFAULTCOUNT)
                    {
                        criticalFaultRestartFlag = 1;
                        faultState = FAULT_CLEAR;
                        criticalFaultCounter = 0;
                    }
                }                
            }
            else if(switchState == SWITCHOFF)
            {
                displayState = DISP_OFF_ALL;
                driveState = DRV_ALL_OFF;
            }
        }
        break;
        
    }
    //--------------------------------------------------------
    // 100 uS
    // Relay, FAN
    switch(driveState)
    {
        case DRV_ALL_OFF : // 0 , default
        {
            RY_INRUSH_OFF;
            RY_BYPSS_OFF;
            FAN_OFF;
        }
        break;
        
        case DRV_NORMAL : // 1
        {
            RY_INRUSH_ON;
            RY_BYPSS_OFF;
        }
        break;
        
        case DRV_ERROR :  // 2
        {
                RY_INRUSH_OFF;
                
                if(faultState == FAULT_UNDER_VOLTAGE) 
                {   
                    RY_BYPSS_ON;
                    displayState = DISP_BYPASS;
                }
                else
                {   
                    RY_BYPSS_OFF;
                    displayState = DISP_ERROR;
                }
            
        }
        break;
    }
    
    // 200 mS
    // Display 
    faultData = faultState;
    Count_200mS++; 
    if(Count_200mS > CNT_200MS) // 2000 * 100uS = 200mS
    {   Count_200mS = 0; 
        SentParameters();
        
        //---- Display State ------
        switch(displayState)
        {
            case DISP_OFF_ALL : // 0 Default, Switch off
            {
                LD_RUN_OFF;
                LD_FAULT_OFF;
                LD_BYPSS_OFF;
            }
            break;
            
            case DISP_STARTUP : // 1
            {   
                LD_BYPSS_OFF;
                LD_FAULT_OFF;
                LD_RUN_TOGGLE;                
            }
            break;
            
            case DISP_NORMAL : // 2
            {   
                LD_FAULT_OFF;
                LD_BYPSS_OFF;
                LD_RUN_ON;
            }
            break;
            
            case DISP_ERROR : // 3
            {                
                LD_RUN_OFF;
                
                cntLEDTick++; // every 200 mS
                if(cntLEDTick >= 2) // 200mS * 2 = 400mS              
                {
                    cntLEDTick = 0;
                    
                    cntToggle++;
                    if(cntToggle > TOTAL_FAULT) cntToggle = 0;
                  
                }
                
                if(cntToggle < faultData) 
                {
                    LD_FAULT_TOGGLE;
                }
                else 
                {
                    LD_FAULT_OFF;
                }
            }
            break;
            
            case DISP_BYPASS : // 4
            {
                LD_RUN_OFF;
                LD_FAULT_OFF;
                LD_BYPSS_ON;
            }
            break;
            
            case DISP_RESTART :
            {
                LD_BYPSS_OFF;
                LD_FAULT_OFF;
                LD_RUN_TOGGLE;
            }
            
        }
    }
    
    Count_20mS++;
    if(Count_20mS > 200)
    {   Count_20mS = 0;
                
    } 
    
    // FAN Control
    if((adc_temperature > TEMP_50_C)&&(switchState == SWITCHON))
    {
       countFanOn++; 
       if(countFanOn > CNT_1SEC)
       {   
           FAN_ON;
       }
    }
    else
    {   
        FAN_OFF;
        countFanOn =0;
    }
    
}

void Delay_ms(uint16_t d)
{   
    Cnt_ms = d;
    while(Cnt_ms >0);
}

// Report by FLT1 PIN (Hardware Fault Detection
void FLT1_Detected(void) 
{
    hardwareFault = FLT1_DETECTED;   
}
// ADC Conversion Complete  7KHz
void ADC_ISR()  
{   
    
    adc_ibatt = (ADC1BUF0 << 5);       
    adc_vbatt = (ADC1BUF1 << 5);       
    adc_vout  = (ADC1BUF2 << 5);      
    adc_iout  = (ADC1BUF3 << 5);  
    adc_temperature = (ADC1BUF4 << 5); 
 
    inverterOutputCurrent = adc_iout - acCurrentOffset;
    
    /* Rectify AC current and check for over current condition on the ouput */
    if(inverterOutputCurrent >= 0)
    {
        rectifiedInverterOutputCurrent = inverterOutputCurrent;
    }
    else
    {
        rectifiedInverterOutputCurrent = (-inverterOutputCurrent);
    }

    if(systemState != STATE_ERROR)
    {
    // Find Peak Inverter Output Current
        if(rectifiedInverterOutputCurrent > maxInverterOutputCurrent)
        {
            maxInverterOutputCurrent = rectifiedInverterOutputCurrent;
        }        
    }
    else
    {
        maxInverterOutputCurrent =0;
    }

    
    // Moving Average of AC Current for AC Current Fault
    rectifiedInverterOutputCurrentSum = rectifiedInverterOutputCurrentSum + rectifiedInverterOutputCurrent - rectifiedInverterOutputCurrentArray[currentArrayCnt];
    averageRectifiedCurrent = rectifiedInverterOutputCurrentSum >> 3;

    rectifiedInverterOutputCurrentArray[currentArrayCnt++] = rectifiedInverterOutputCurrent;

    if(currentArrayCnt >= 8) // 8
    {
        currentArrayCnt = 0;
    }

    // Inverter Over Current Fault Check
    // inverterOutputOverCurrent takes into account the delta in the acCurrentOffset
    if((averageRectifiedCurrent > inverterOutputOverCurrent) && (systemState == STATE_NORMAL))
    {
        if((criticalFaultFlag == 1) && (criticalFaultRestartFlag == 1))
        {
            PTCONbits.PTEN = 0;     // Disable PWM
            RCONbits.SWDTEN = 0;	// Need to disable WDT
        }

        if(faultState == FAULT_CLEAR)
        {
            criticalFaultFlag = 1;
            faultState = FAULT_OVER_CURRENT_OP;
        }
        
    }
    
    sampl_ch0 = adc_ibatt;
    sum_ch0 += sampl_ch0;
    sum_ch0 -= adc_avg_currentInput;   
    adc_avg_currentInput = (uint32_t)(sum_ch0)/NUMSAMPLES;   
    
    delta_adc_iin = adc_avg_currentInput - adc_offset0;
    //-------------------------------------------------
    sampl_ch1 = adc_vbatt;
    sum_ch1 += sampl_ch1;
    sum_ch1 -= adc_avg_voltageInput;
    adc_avg_voltageInput = (uint32_t)(sum_ch1)/NUMSAMPLES;  

    //-------------------------------------------------
    sampl_ch2 = adc_vout;
    sum_ch2 += sampl_ch2;
    sum_ch2 -= adc_avg_voltageOutput;
    adc_avg_voltageOutput = (uint32_t)(sum_ch2)/NUMSAMPLES;    
    
    //-------------------------------------------------
    sampl_ch3 = adc_iout;
    sum_ch3 += sampl_ch3;
    sum_ch3 -= adc_avg_currentOutput;
    adc_avg_currentOutput = (uint32_t)(sum_ch3)/NUMSAMPLES;  

    //-------------------------------------------------
    sampl_ch4 = adc_temperature;
    sum_ch4 += sampl_ch4;
    sum_ch4 -= adc_avg_pcbTemp;
    adc_avg_pcbTemp = (uint32_t)(sum_ch4)/NUMSAMPLES; 
        
    //-------------------------------------------------    
    /* In Q15 1Lsb = 0.1007080078 mV*/
    // Current Input
    iin_mv = (float)(delta_adc_iin * 0.002427321214);  // 12 bit
    ibatt_u16 = (uint16_t)(iin_mv*1000); //mV/mR    // 1
   
    // Voltage Input
    vin_mv = (float)(adc_avg_voltageInput * 1.728110599); // = (3300/32768)*Gain, (3300/32768)*17
    vbatt_u16 = (uint16_t)vin_mv;
    
    // Voltage Output
    vout_mv = (float)((adc_avg_voltageOutput * 1.016235352)*1.414);
    vout_u16 = (uint16_t)vout_mv;
    
    // Current Output
//    iout_mv = (float)(delta_adc_iout * (3.3/1024.0))/0.066;  
    iout_mv = (float)(delta_adc_iout * 0.001525878906); 
    iout_u16 = (uint16_t)(iout_mv * 1000);      
            
    // Temperature    
    temp_mv = (float)(adc_avg_pcbTemp * 0.100780078);  // mV
    temp_c = (float)(temp_mv - 500)/10.00;
    temp_u16 = temp_c * 100;
        
}


//-------------- End of Interrupt Service Routine -------------

void FullBridgeDrive(void)
{   
    switch(fullBridgeState)
    {
        case FULLBRIDGE_AH_BL_ACTIVE : // 0
        {   
            
            IOCON1bits.POLL = 0;   // Not Invert
            IOCON1bits.POLH = 0;   // Not Invert 
            
            //------- Boostrap Drive            
            PWM_OverrideHighEnable(PWM_A);      // AH Away Low 
            PWM_OverrideLowEnable(PWM_A);       // AL Away High

            PWM_OverrideHighDisable(PWM_B);     // BH Send PWM Complementary H 
            PWM_OverrideLowDisable(PWM_B);      // BL Send PWM Complementary L
            
            if(Flag_180Degree == ON)
            {    
                Flag_180Degree = OFF;
                fullBridgeState = FULLBRIDGE_2ND_INACTIVE;
            }  
        }
        break;
 
        case FULLBRIDGE_2ND_INACTIVE : // 1
        {                             
            fullBridgeState = FULLBRIDGE_AL_BH_ACTIVE;        
        }
        break;
        
        case FULLBRIDGE_AL_BH_ACTIVE : // 2
        {   
            
            IOCON1bits.POLL = 1;   // Invert
            IOCON1bits.POLH = 1;   // Invert     
            
            //------- Boostrap Drive            
            PWM_OverrideHighEnable(PWM_B);      // BH Away Low 
            PWM_OverrideLowEnable(PWM_B);       // BL Away High

            PWM_OverrideHighDisable(PWM_A);     // AH Send PWM Complementary H 
            PWM_OverrideLowDisable(PWM_A);      // AL Send PWM Complementary L
            
            if(Flag_180Degree == ON)
            {       

                 
                 Flag_180Degree = OFF;
                 fullBridgeState = FULLBRIDGE_4TH_INACTIVE;
            }            
        }
        break;
        
        case FULLBRIDGE_4TH_INACTIVE : // 3
        {                
            fullBridgeState = FULLBRIDGE_AH_BL_ACTIVE;  // 1           
        }
        break;
        
    }
    
    
}


void InitValue(void)  // Stamp Initial ADC Value
{   
    adc_offset0 = adc_avg_currentInput;     // i batt
    adc_offset1 = adc_avg_voltageInput;     // v batt
    adc_offset2 = adc_avg_voltageOutput;    // v out
    adc_offset3 = 16384;                    // i out 
    adc_offset4 = adc_avg_pcbTemp;          // temperature
}

void FaultCheck(void) // 100 uS
{   
    hardwareFault = FLT1_CLEAR;
    
// Check Input OverCurrent, Pass
    if((adc_avg_currentInput > BATTERY_OVERCURRENT_40A)&&(inputOverCurrentFlag == 0))
    {
        Fault_Count_InputOverCurrent++;
        if(Fault_Count_InputOverCurrent > CNT_10MS)
        {
            if(faultState == FAULT_CLEAR)
            {   
                faultState = FAULT_OVER_CURRENT_IP;
                inputOverCurrentFlag = 1;
            }
        }
    }
    else if((adc_avg_currentInput < BATTERY_OVERCURRENT_1A)&&(inputOverCurrentFlag == 1))
    {
        Fault_Count_InputOverCurrent++;
        if(Fault_Count_InputOverCurrent > CNT_2SEC)
        {
            inputOverCurrentFlag = 0;
            if(faultState == FAULT_OVER_CURRENT_IP)
            {
                faultState = FAULT_CLEAR;
                
            }
            
        }
    }
    else
    {
        Fault_Count_InputOverCurrent = 0;
    }
    
// Check Input Over Voltage Condition
    if((adc_avg_voltageInput > BATTERY_OVERVOLTAGE_LIMIT)&&(vbattOverVoltageFlag == 0))
    {
        Fault_Count_InputOverVoltage++;
        if(Fault_Count_InputOverVoltage > CNT_1SEC) // Cut out
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_OVER_VOLTAGE;
                vbattOverVoltageFlag = 1;
            }
        }
    }
    else if((adc_avg_voltageInput < BATTERY_OVERVOLTAGE_HYST)&&(vbattOverVoltageFlag == 1))
    {
        Fault_Count_InputOverVoltage++;
        if(Fault_Count_InputOverVoltage > CNT_2SEC) // Back to work
        {   
            vbattOverVoltageFlag = 0;  // Clear Flag
            if(faultState == FAULT_OVER_VOLTAGE)
            {
                faultState = FAULT_CLEAR;     
            }
        }
    }
    else
    {
        Fault_Count_InputOverVoltage = 0;
    }
    
// Check Input Under Voltage Condition
    if((adc_avg_voltageInput < BATTERY_UNDERVOLTAGE_LIMIT)&&(vbattUnderVoltageFlag == 0))
    {
        Fault_Count_InputUnderVoltage++;
        if(Fault_Count_InputUnderVoltage > CNT_1SEC)
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_UNDER_VOLTAGE;
                vbattUnderVoltageFlag = 1;
            }
        }
    }
    else if((adc_avg_voltageInput > BATTERY_UNDERVOLTAGE_HYST)&&(vbattUnderVoltageFlag == 1))
    {
        Fault_Count_InputUnderVoltage++;
        if(Fault_Count_InputUnderVoltage > CNT_2SEC)
        {
            vbattUnderVoltageFlag = 0;
            if(faultState == FAULT_UNDER_VOLTAGE)
            {
               faultState = FAULT_CLEAR; 
            }
        }
    }
    else
    {
        Fault_Count_InputUnderVoltage = 0; 
    }

            
// Check Output Over Voltage Condition
    if((adc_avg_voltageOutput > VAC_OVER)&&(outputOverVoltageFlag == 0))
    {
        Fault_Count_OutputOverVoltage++;
        if(Fault_Count_OutputOverVoltage > CNT_10MS) // Cut out
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_OVER_VOLTAGE_OP;
                outputOverVoltageFlag = 1;
            }
        }
    }
    else if((adc_avg_voltageOutput < VAC_OVER)&&(outputOverVoltageFlag == 1))
    {
        Fault_Count_OutputOverVoltage++;
        if(Fault_Count_OutputOverVoltage > CNT_2SEC) // Back to work
        {   
            outputOverVoltageFlag = 0;  // Clear Flag
            if(faultState == FAULT_OVER_VOLTAGE_OP)
            {
                faultState = FAULT_CLEAR;     
            }
        }
    }
    else
    {
        Fault_Count_OutputOverVoltage = 0;
    }
    
// Check PCB OverTemperature Condition
    if((adc_avg_pcbTemp > TEMP_50_C)&&(pcbTemperatureOverFlag == 0))
    {
        Fault_Count_PCBOverTemperature++;
        if(Fault_Count_PCBOverTemperature > CNT_2SEC) // Cut out
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_OVER_TEMP;
                pcbTemperatureOverFlag = 1;
            }
        }
    }
    else if((adc_avg_pcbTemp < (TEMP_50_C - TEMPERATURE_HYS))&&(pcbTemperatureOverFlag == 1))
    {
        Fault_Count_PCBOverTemperature++;
        if(Fault_Count_PCBOverTemperature > CNT_2SEC) // Back to work
        {   
            pcbTemperatureOverFlag = 0;  // Clear Flag
            if(faultState == FAULT_OVER_TEMP)
            {
                faultState = FAULT_CLEAR;     
            }
        }
    }
    else
    {
        Fault_Count_PCBOverTemperature = 0;
    }

    // Check Transformer OverTemperature Condition
    if((thermoState == THERMOSTAT_ON)&&(extTemperatureOverFlag == 0))
    {
        Fault_Count_extOvertemperature++;
        if(Fault_Count_extOvertemperature > CNT_2SEC) // Cut out
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_OVER_TEMP_TRFMR;
                extTemperatureOverFlag = 1;
            }
        }
    }
    else if((thermoState == THERMOSTAT_OFF)&&(extTemperatureOverFlag == 1))
    {
        Fault_Count_extOvertemperature++;
        if(Fault_Count_extOvertemperature > CNT_2SEC) // Back to work
        {   
            extTemperatureOverFlag = 0;  // Clear Flag
            if(faultState == FAULT_OVER_TEMP_TRFMR)
            {
                faultState = FAULT_CLEAR;     
            }
        }
    }
    else
    {
        Fault_Count_extOvertemperature = 0;
    }
    
 
// Check Hardware Fault
    if((hardwareFault == FLT1_DETECTED)&&(HardwareFaultFlag == 0))
    {
        Fault_Count_FLT1++;
        if(Fault_Count_FLT1 > CNT_200MS) // Cut out
        {
            if(faultState == FAULT_CLEAR)
            {
                faultState = FAULT_HW_FLT1;
                HardwareFaultFlag = 1;
            }
        }
    }
    else if((hardwareFault == FLT1_CLEAR)&&(HardwareFaultFlag == 1))
    {
        Fault_Count_FLT1++;
        if(Fault_Count_FLT1 > CNT_200MS) // Back to work
        {   
            HardwareFaultFlag = 0;  // Clear Flag
            if(faultState == FAULT_HW_FLT1)
            {
                faultState = FAULT_CLEAR;     
            }
        }
    }
    else
    {
        Fault_Count_FLT1 = 0;
    }
    
}

void UpdateParameter(void)
{
    if(PercentModulation < 0) PercentModulation = 0;
    if(PercentModulation > 100) PercentModulation = 100;
    
    if(SFRAC16control < 0) SFRAC16control = 0;
    if(SFRAC16control > 32767) SFRAC16control = 32767;
        
    Buff_Period = sineTable_20KHz[Sampling_Count_SineWave];    // 20KHz

    Buff_Duty = (uint32_t) SFRAC16control * Buff_Period;  // Max 65535 * 100 = 6553500
    DutyCycle = Buff_Duty /32767;
    
    if(DutyCycle > FULLBRIDGE_PERIOD) DutyCycle = FULLBRIDGE_PERIOD;
    if(DutyCycle < 0) DutyCycle = 0;
    
    MDC =  DutyCycle;  // MasterDutyControl
       
}

void SentParameters(void)
{   
//      [0X03],[Byte-L][Byte-H],[Byte-L][Byte-H],......[0XFC]]
     
        UART1_Write(0x03);  // Start
        
        // Voltage Output Target
        UART1_Write(PID_OUTPUTVOLTAGE_REFERENCE & 0x00FF);    //L
        UART1_Write(PID_OUTPUTVOLTAGE_REFERENCE >> 8);        //H
        
        // Input Current
        UART1_Write(adc_avg_currentInput & 0x00FF);    //L
        UART1_Write(adc_avg_currentInput >> 8);        //H
        
        // Input Voltage
        UART1_Write(adc_avg_voltageInput & 0x00FF);    
        UART1_Write(adc_avg_voltageInput >> 8);        

        // Output Voltage   
        UART1_Write(adc_avg_voltageOutput & 0x00FF); 
        UART1_Write(adc_avg_voltageOutput >> 8); 

        // Output Current   
        UART1_Write(adc_avg_currentOutput & 0x00FF); 
        UART1_Write(adc_avg_currentOutput >> 8); 

        // Temperature
        UART1_Write(adc_avg_pcbTemp & 0x00FF); 
        UART1_Write(adc_avg_pcbTemp >> 8);
        
        // Variable 1
        UART1_Write(inverterOutputCurrent & 0x00FF); 
        UART1_Write(inverterOutputCurrent >> 8);

        // Variable 2
        UART1_Write(acCurrentOffset & 0x00FF); 
        UART1_Write(acCurrentOffset >> 8);

        // Variable 3
        UART1_Write(maxInverterOutputCurrent & 0x00FF); 
        UART1_Write(maxInverterOutputCurrent >> 8);

        // Variable 4
        UART1_Write(averageRectifiedCurrent & 0x00FF); 
        UART1_Write(averageRectifiedCurrent >> 8);
 
        // Variable 5
        UART1_Write(inverterOutputOverCurrent & 0x00FF); 
        UART1_Write(inverterOutputOverCurrent >> 8);
        
        // 8 bit
        UART1_Write(systemState);               
        UART1_Write(faultState);                
        UART1_Write(criticalFaultFlag);         
        UART1_Write(criticalFaultRestartFlag);  
        UART1_Write(acCurrentOffsetFlag);       
        UART1_Write(thermoState);               

        UART1_Write(thermoState); 
        UART1_Write(thermoState); 
        UART1_Write(thermoState); 
        
        UART1_Write(0xFC);  // End
            
}

void init_outputVoltageLoop(void)   // PID
{
    outputVoltagePID.abcCoefficients = outputVoltageABC;      /* Set up pointer to derived coefficients */
    outputVoltagePID.controlHistory = outputVoltageHistory;   /* Set up pointer to controller history samples */
    
    PIDInit(&outputVoltagePID);                                    /* Clear the controler history and the controller output */
    
	if ((PID_OUTPUTVOLTAGE_A == 0x7FFF || PID_OUTPUTVOLTAGE_A == 0x8000) || 
		(PID_OUTPUTVOLTAGE_B == 0x7FFF || PID_OUTPUTVOLTAGE_B == 0x8000) ||
		(PID_OUTPUTVOLTAGE_C == 0x7FFF || PID_OUTPUTVOLTAGE_C == 0x8000))
	{
		while(1);		// If this point is reached then coefficients are invalid *
	}

	outputVoltagePID.abcCoefficients[0] = PID_OUTPUTVOLTAGE_A;   /* Load calculated coefficients */	
	outputVoltagePID.abcCoefficients[1] = PID_OUTPUTVOLTAGE_B;
	outputVoltagePID.abcCoefficients[2] = PID_OUTPUTVOLTAGE_C;
    
    //outputVoltagePID.controlReference = OutputVoltageReference << 5;  /* assign initial control reference for PID to be what ever DC */
    outputVoltagePID.controlReference = adc_vout << 5;  /* assign initial control reference for PID to be what ever DC */
	outputVoltagePID.measuredOutput = 0;              	       

}

void outputVoltageLoop(void)   // PID Voltage Control
{       
    outputVoltagePID.abcCoefficients = outputVoltageABC;      /* Set up pointer to derived coefficients */
    outputVoltagePID.controlHistory  = outputVoltageHistory;   /* Set up pointer to controller history samples */
    
    PID(&outputVoltagePID);                                    /* Clear the controler history and the controller output */    
    
	if ((PID_OUTPUTVOLTAGE_A == 0x7FFF || PID_OUTPUTVOLTAGE_A == 0x8000) || 
		(PID_OUTPUTVOLTAGE_B == 0x7FFF || PID_OUTPUTVOLTAGE_B == 0x8000) ||
		(PID_OUTPUTVOLTAGE_C == 0x7FFF || PID_OUTPUTVOLTAGE_C == 0x8000))
	{
		while(1);		// If this point is reached then coefficients are invalid 
	}    
    
    SFRAC16control = outputVoltagePID.controlOutput;    
    outputVoltagePID.controlReference = PID_OUTPUTVOLTAGE_REFERENCE;  /* assign initial control reference for PID to be what ever DC */    
	outputVoltagePID.measuredOutput = adc_vout;  
    
    /* Load calculated coefficients */	
	outputVoltagePID.abcCoefficients[0] = PID_OUTPUTVOLTAGE_A;   
	outputVoltagePID.abcCoefficients[1] = PID_OUTPUTVOLTAGE_B;
	outputVoltagePID.abcCoefficients[2] = PID_OUTPUTVOLTAGE_C;
    
    /* Load calculated history */	
    outputVoltagePID.controlHistory[2] = outputVoltageHistory[1];
    outputVoltagePID.controlHistory[1] = outputVoltageHistory[0];
    outputVoltagePID.controlHistory[0] = PID_OUTPUTVOLTAGE_REFERENCE - adc_vout;     
    
            
}
   
void OutputSoftStartRoutine(void)
{   
//    (if V Measure < VoltageReference) ++ Reference Value
//    while (outputVoltagePID.controlReference <= PID_OUTPUTVOLTAGE_REFERENCE) // 21472 
    
    while (outputVoltagePID.controlReference <= PID_OUTPUTVOLTAGE_REFERENCE)  
	{
		Delay_ms(20);  // Interval time
		outputVoltagePID.controlReference += OUTPUTSOFTSTART_INCREMENT;  // 1
	}
    
    outputVoltagePID.controlReference = PID_OUTPUTVOLTAGE_REFERENCE;   
}


int main(void)
{
    // initialize the device
    SYSTEM_Initialize();
     
    //TMR1_SetInterruptHandler(Indication);      // 200mS
    
    TMR2_SetInterruptHandler(PriorityMedium);  // 10KHz, 100uS
    TMR2_Start();
    
    TMR3_SetInterruptHandler(PriorityHigh);   //  20KHz,  50uS 
    TMR3_Start();
    
    PWM_SetGenerator3InterruptHandler(FLT1_Detected);
    
    ADC1_SetInterruptHandler(ADC_ISR);  
    
    //AD1CON1bits.ADON = 1;  //ADC1_Enable
    
    init_outputVoltageLoop();               /* Initialize  AC Voltage PID */   
    //OutputSoftStartRoutine();             /* SoftStartRoutine */
    LD_BYPSS_OFF;
    LD_FAULT_OFF;
    LD_RUN_OFF;
    
    Delay_ms(1000); // Waiting ADC Settle
    InitValue();   // Stamp OffSet Value 
    
    RCONbits.SWDTEN = 1; // Enable Watchdog
    
    while (1)
    {   
              
    }
    
    return 1; 
}
//--------------- End of main ----------------


/**
 End of File
*/


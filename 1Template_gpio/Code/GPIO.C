/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2015 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

//***********************************************************************************************************
//  Nuvoton Technoledge Corp. 
//  Website: http://www.nuvoton.com
//  E-Mail : MicroC-8bit@nuvoton.com
//  Date   : Apr/21/2015
//***********************************************************************************************************

//***********************************************************************************************************
//  File Function: N76E885 GPIO demo code
//***********************************************************************************************************

#include <stdio.h>
#include "N76E885.h"
#include "Version.h"
#include "Typedef.h"
#include "Define.h"
#include "SFR_Macro.h"
#include "Common.h"
#include "Delay.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
//
//<e0> System Clock Source Configuration
// <o1> System Clock Source Selection
//      <0=> 2~25MHz    XTAL
//      <1=> 32.768KHz  XTAL
//      <2=> 22.1184MHz Internal
//      <3=> 10KHz      Internal
//      <4=> OSC-In     External
//</e>
//
//<e2> Clock Divider Configuration
//     <o3.0..7>  System Clock Source Devider  <1-255:1>
//                     <i> Fsys = (System Clock Source) / (2 * Devider)
//</e>
//
// <o4> Port0 Mode Selection (P0[7:0])
//      <0=> Quasi-Bidirectional
//      <1=> Push-Pull
//      <2=> Input-Only (high-impedance)
//      <3=> Open-Drain
//
// <o5> Port1 Mode Selection (P1[1:0])
//      <0=> Quasi-Bidirectional
//      <1=> Push-Pull
//      <2=> Input-Only (high-impedance)
//      <3=> Open-Drain
//
// <o6> Port2 Mode Selection (P2[6:0])
//      <0=> Quasi-Bidirectional
//      <1=> Push-Pull
//      <2=> Input-Only (high-impedance)
//      <3=> Open-Drain
//
// <o7> Port3 Mode Selection (P3[7:0])
//      <0=> Quasi-Bidirectional
//      <1=> Push-Pull
//      <2=> Input-Only (high-impedance)
//      <3=> Open-Drain
//-------- <<< end of configuration section >>> ------------------------------
*/


#include <absacc.h>  

#define SYS_CLK_EN      0
#define SYS_SEL         2
#define SYS_DIV_EN      0                   //0: Fsys=Fosc, 1: Fsys = Fosc/(2*CKDIV)
#define SYS_DIV         1

#define PORT0_MODE      0
#define PORT1_MODE      0
#define PORT2_MODE      0
#define PORT3_MODE      0

bit BIT_TMP;

/*------------------------------------------------
The main C function.  Program execution starts
here after stack initialization.
------------------------------------------------*/
void main (void) 
{
    /* Note
       MCU power on system clock is HIRC (22.1184MHz), so Fsys = 22.1184MHz
    */
    
    Set_All_GPIO_Quasi_Mode();                   //in Common.c
    InitialUART0_Timer1_Type1(9600);             /* 9600 Baud Rate*/

    Show_FW_Version_Number_To_PC();
    
    printf ("\n*===================================================================");
    printf ("\n*  Name: N76E885 GPIO Toggling Demo Code.");
    printf ("\n*===================================================================\n");

    /* Change system closk source */
    #if SYS_CLK_EN == 1
        #if   SYS_SEL == 0
            System_Clock_Select(E_HXTEN);   //Fosc = 2~25MHz XTAL
        #elif SYS_SEL == 1
            System_Clock_Select(E_LXTEN);   //Fosc = 32.768KHz XTAL
        #elif SYS_SEL == 2
            System_Clock_Select(E_HIRCEN);  //Fosc = 22.1184MHz Internal RC
        #elif SYS_SEL == 3
            System_Clock_Select(E_LIRCEN);  //Fosc = 10KHz Internal RC
        #elif SYS_SEL == 4
            System_Clock_Select(E_OSCEN);   //Fosc = OSC-In External OSC
        #endif
    #endif
    
    #if SYS_DIV_EN == 1
        CKDIV = SYS_DIV;                    //Fsys = Fosc / (2* CLKDIV) = Fcpu
    #endif
  
  #if 1
    Set_All_GPIO_Quasi_Mode();
  #else
    #if   PORT0_MODE == 0                   //Quasi-Bidirectional
        P0M1 = 0x00;
        P0M2 = 0x00;
    #elif PORT0_MODE == 1                   //Push-Pull
        P0M1 = 0x00;
        P0M2 = 0xFF;
    #elif PORT0_MODE == 2                   //Input-Only
        P0M1 = 0xFF;
        P0M2 = 0x00;
    #elif PORT0_MODE == 3                   //Open-Drain
        P0M1 = 0xFF;
        P0M2 = 0xFF;
    #endif

    #if   PORT1_MODE == 0                   //Quasi-Bidirectional
        P1M1 = 0x00;
        P1M2 = 0x00;
    #elif PORT1_MODE == 1                   //Push-Pull
        P1M1 = 0x00;
        P1M2 = 0x03;
    #elif PORT1_MODE == 2                   //Input-Only
        P1M1 = 0x03;
        P1M2 = 0x00;
    #elif PORT1_MODE == 3                   //Open-Drain
        P1M1 = 0x03;
        P1M2 = 0x03;
    #endif

    #if   PORT2_MODE == 0                   //Quasi-Bidirectional
        P2M1 = 0x00;
        P2M2 = 0x00;
    #elif PORT2_MODE == 1                   //Push-Pull
        P2M1 = 0x00;
        P2M2 = 0xFF;
    #elif PORT2_MODE == 2                   //Input-Only
        P2M1 = 0x7F;
        P2M2 = 0x00;
    #elif PORT2_MODE == 3                   //Open-Drain
        P2M1 = 0x7F;
        P2M2 = 0x7F;
    #endif

    #if   PORT3_MODE == 0                   //Quasi-Bidirectional
        P3M1 = 0x00;
        P3M2 = 0x00;
    #elif PORT3_MODE == 1                   //Push-Pull
        P3M1 = 0x00;
        P3M2 = 0xFF;
    #elif PORT3_MODE == 2                   //Input-Only
        P3M1 = 0xFF;
        P3M2 = 0x00;
    #elif PORT3_MODE == 3                   //Open-Drain
        P3M1 = 0xFF;
        P3M2 = 0xFF;
    #endif
  #endif
  
  #define N 30
  
  while(1)
  {
        P02 = 0;
        Timer3_Delay1ms(N*4);
        P03 = 0;
        
        Timer0_Delay1ms(N*1);
        Timer2_Delay1ms(N*2);
        Timer3_Delay1ms(N*4);
        WakeUp_Timer_Delay25ms(1);          //Clock source is always 10KHz
        
        P02 = 1;
        Timer3_Delay1ms(N*4);
        P03 = 1;
        
        Timer0_Delay1ms(N*1);
        Timer2_Delay1ms(N*2);
        Timer3_Delay1ms(N*4);
        WakeUp_Timer_Delay25ms(1);          //Clock source is always 10KHz
    }
}




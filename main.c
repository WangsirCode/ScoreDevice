/*
 * File:   main.c
 * Author: wangyuhao
 *
 * Created on March 16, 2017, 9:19 PM
 */

// CONFIG1
#pragma config FOSC = ECH       // Oscillator Selection (ECH, External Clock, High Power Mode (4-32 MHz): device clock supplied to CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (Vcap functionality is disabled on RA6.)
#pragma config PLLEN = ON       // PLL Enable (4x PLL enabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low Power Brown-Out Reset Enable Bit (Low power brown-out is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

int maxScore = 3;
#define MODE_3 3
#define MODE_10 10
#include <xc.h>
#include "display.h"
void initiliazition();
void main(void) {
    initiliazition();
    while(1)
    {
        
    }
    return;
}


void initiliazition()
{
    //设置ScreenOne的io引脚
    PORTA = 0;
    ANSELA = 0;
    TRISA = 0;
    LATA = 0;
    
    //设置ScreenTwo的io引脚
    PORTC = 0;
    TRISC = 0;
    LATC = 0;
    
    //初始化portb
    ANSELB = 0;
    TRISB = 0;
    LATB = 0;
    
    //中断使能
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.IOCIE = 1;
    
    //设置开关的电平中断
    TRISBbits.TRISB4 = 1;
    IOCBPbits.IOCBP4 = 1;
    IOCBNbits.IOCBN4 = 1;
    
    //设置复位按键的电平中断
    TRISBbits.TRISB3 = 1;
    IOCBPbits.IOCBP3 = 1;
    IOCBNbits.IOCBN3 = 1;
    
    //设置选择模式的io引脚和电平中断
    TRISBbits.TRISB2 = 1;
    IOCBPbits.IOCBP2 = 1;
    IOCBNbits.IOCBN2 = 1;
    
    //设置红外接收管的io引脚和电平中断
    TRISBbits.TRISB0 = 1;
    IOCBPbits.IOCBP0 = 1;
    IOCBNbits.IOCBN0 = 1;
    
    TRISBbits.TRISB1 = 1;
    IOCBPbits.IOCBP1 = 1;
    IOCBNbits.IOCBN1 = 1;
    
    //设置两个screen的初始值为0
    displayScreenSet(SCREEN_ONE,0);
    displayScreenSet(SCREEN_TWO,0);
    
    //设置模式
    if(PORTBbits.RB2 == 1)
    {
        maxScore = MODE_3;
    }
    
    else
    {
        maxScore = MODE_10;
    }
}
void endGame()
{
    displayScreenSet(SCREEN_ONE,0);
    displayScreenSet(SCREEN_TWO,0);
}

void  interrupt  ISR(void) 
{
    //显示屏1
    if(IOCBFbits.IOCBF0 == 1)
    {
        IOCBFbits.IOCBF0 = 0;
        if(PORTBbits.RB0 == 1)
        {
            int value = displayScreenGet(SCREEN_ONE);
            displayScreenSet(SCREEN_ONE,++value);
            if (value == maxScore)
            {
                endGame(); 
            }
        }
    }
    
    //显示屏2
    if(IOCBFbits.IOCBF1 == 1)
    {
        IOCBFbits.IOCBF1 = 0;
        if(PORTBbits.RB1 == 1)
        {
            int value = displayScreenGet(SCREEN_TWO);
            displayScreenSet(SCREEN_TWO,++value);
            if (value == maxScore)
            {
                endGame(); 
            }
        }
    }
    
    //选择模式
    if(IOCBFbits.IOCBF2 == 1)
    {
        IOCBFbits.IOCBF2 = 0;
        //设置模式
        if(PORTBbits.RB2 == 1)
        {
            maxScore = MODE_3;
        }

        else
        {
            maxScore = MODE_10;
        }

        //如果当前比分已经超过了最大比分，停止游戏
        if(maxScore <= displayScreenGet(SCREEN_ONE) || maxScore <= displayScreenGet(SCREEN_ONE) )
        {
            endGame();
        }
    }
    
    //复位
    if(IOCBFbits.IOCBF3 == 1)
    {
        IOCBFbits.IOCBF3 = 0;
        displayScreenSet(SCREEN_ONE,0);
        displayScreenSet(SCREEN_TWO,0);
    }
    
}
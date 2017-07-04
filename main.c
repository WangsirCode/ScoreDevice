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
#define END_TIMES 8
#define MODE_3 3
#define MODE_10 10
#include <xc.h>
#include <stdint.h>
#include "display.h"
#define INSTR_CYCLE_DELAY 100000
void initiliazition();
void main(void) {
    initiliazition();
    while(1)
    {
        
    }
}


void initiliazition()
{
    //����ScreenOne��io����
    PORTA = 0;
    ANSELA = 0;
    TRISA = 0;
    LATA = 0;
    
    //����ScreenTwo��io����
    PORTC = 0;
    TRISC = 0;
    LATC = 0;
    
    //��ʼ��portb
    ANSELB = 0;
    TRISB = 0;
    LATB = 0;
    
    //�ж�ʹ��
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.IOCIE = 1;
    
    //���ø�λ�����ĵ�ƽ�ж�
    TRISBbits.TRISB3 = 1;
    IOCBPbits.IOCBP3 = 1;
    IOCBNbits.IOCBN3 = 1;
    
    //����ѡ��ģʽ��io���ź͵�ƽ�ж�
    TRISBbits.TRISB2 = 1;
    IOCBPbits.IOCBP2 = 1;
    IOCBNbits.IOCBN2 = 1;
    
    //���ú�����չܵ�io���ź͵�ƽ�ж�
    TRISBbits.TRISB0 = 1;
    IOCBPbits.IOCBP0 = 0;
    IOCBNbits.IOCBN0 = 1;
    
    TRISBbits.TRISB1 = 1;
    IOCBPbits.IOCBP1 = 0;
    IOCBNbits.IOCBN1 = 1;
    
    //��������screen�ĳ�ʼֵΪ0
    displayScreenSet(SCREEN_ONE,0);
    displayScreenSet(SCREEN_TWO,0);
    
    //����ģʽ
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
    int i = 0;
    for(; i < END_TIMES; i++)
    {
        displayScreenSet(SCREEN_ONE,10);
        displayScreenSet(SCREEN_TWO,10);
        _delay(INSTR_CYCLE_DELAY / 5);
        displayScreenSet(SCREEN_ONE,0);
        displayScreenSet(SCREEN_TWO,0);
        _delay(INSTR_CYCLE_DELAY / 5);
    }
    
    
}

void  interrupt  ISR(void) 
{
    //��ʾ��1
    if(IOCBFbits.IOCBF0 == 1)
    {
        IOCBFbits.IOCBF0 = 0;
        _delay(INSTR_CYCLE_DELAY / 100);
        if(PORTBbits.RB0 == 0)
        {
            int value = displayScreenGet(SCREEN_ONE);
            displayScreenSet(SCREEN_ONE,++value);

            if (value == maxScore)
            {
                endGame(); 
            }
            _delay(INSTR_CYCLE_DELAY);
        }
    }
    
    //��ʾ��2
    if(IOCBFbits.IOCBF1 == 1)
    {
        IOCBFbits.IOCBF1 = 0;
        INTCONbits.IOCIE = 0;
        _delay(INSTR_CYCLE_DELAY / 100);
        if(PORTBbits.RB1 == 0)
        {
            int value = displayScreenGet(SCREEN_TWO);
            displayScreenSet(SCREEN_TWO,++value);
            if (value == maxScore)
            {
                endGame(); 
            }
            _delay(INSTR_CYCLE_DELAY * 3);
        }
        INTCONbits.IOCIE = 1;
    }
    
    //ѡ��ģʽ
    if(IOCBFbits.IOCBF2 == 1)
    {
        IOCBFbits.IOCBF2 = 0;
        _delay(INSTR_CYCLE_DELAY / 100);
        //����ģʽ
        if(PORTBbits.RB2 == 1)
        {
            maxScore = MODE_3;
        }

        else
        {
            maxScore = MODE_10;
        }

        //�����ǰ�ȷ��Ѿ����������ȷ֣�ֹͣ��Ϸ
        if(maxScore <= displayScreenGet(SCREEN_ONE) || maxScore <= displayScreenGet(SCREEN_TWO) )
        {
            endGame();
        }
    }
    
    //��λ
    if(IOCBFbits.IOCBF3 == 1)
    {
        IOCBFbits.IOCBF3 = 0;
        INTCONbits.IOCIE = 0;
        _delay(INSTR_CYCLE_DELAY / 100);
        displayScreenSet(SCREEN_ONE,0);
        displayScreenSet(SCREEN_TWO,0);
        INTCONbits.IOCIE = 1;
    }
    
}
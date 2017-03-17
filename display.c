/*
 * File:   display.c
 * Author: wangyuhao
 *
 * Created on March 16, 2017, 9:40 PM
 */

#include "display.h"
#include <xc.h>
void displayScreenSet(int num,int value)
{
    switch(num)
    {
        case SCREEN_ONE:
            PORTA = ScreenDecoder[value];
            score1 = value;
            break;
        case SCREEN_TWO:
            PORTC = ScreenDecoder[value];
            score2 = value;
            break;
        default:
            break;
    }
}


int displayScreenGet(int num)
{
    int value;
    switch(num)
    {
        case SCREEN_ONE:
            value = score1;
            break;
        case SCREEN_TWO:
            value = score2;
            break;
        default:
            value = ERROR;
            break;
    }
    return value;
}
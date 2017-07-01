/*
 * File:   display.c
 * Author: wangyuhao
 *
 * Created on March 16, 2017, 9:40 PM
 */

#include "display.h"
#include <xc.h>
void screenOneSet(int value)
{

}

void screenTwoSet(int value)
{

}

void displayScreenSet(int num,int value)
{
    switch(num)
    {
        case SCREEN_ONE:
            screenOneSet(value);
            score1 = value;
            break;
        case SCREEN_TWO:
            screenTwoSet(value);
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
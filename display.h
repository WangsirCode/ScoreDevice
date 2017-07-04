/* 
 * File:   display.h
 * Author: wangyuhao
 *
 * Created on March 16, 2017, 9:42 PM
 */

#ifndef DISPLAY_H
#define	DISPLAY_H

#ifdef	__cplusplus
extern "C" {
#endif

#define SCREEN_ONE 0
#define SCREEN_TWO 1
#define ERROR -1

static int score1; //???1???????
static int score2; //???2???????

 const unsigned int ScreenDecoder[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000
 ,0b10010000,0b11111111};   
    
/*
 * ????????value
 */
void displayScreenSet(int num,int value);

/*
 * ????????value
 */
int displayScreenGet(int num);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */


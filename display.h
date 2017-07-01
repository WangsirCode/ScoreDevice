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

#define SCREEN_ONE 1
#define SCREEN_TWO 2
#define ERROR -1

static int score1; //显示屏1当前显示的得分
static int score2; //显示屏2当前显示的得分

 const unsigned int ScreenDecoder[] = {0b11000000,0b11111001,0b10100100,0b10110000,0b10011001,0b10010010,0b10000010,0b11111000,0b10000000
 ,0b10010000,0b11111111};   
    
/*
 * 设置指定显示屏的value
 */
void displayScreenSet(int num,int value);

/*
 * 获取指定显示屏的value
 */
int displayScreenGet(int num);

#ifdef	__cplusplus
}
#endif

#endif	/* DISPLAY_H */


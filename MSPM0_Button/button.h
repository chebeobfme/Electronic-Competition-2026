#ifndef __BUTTON_H
#define __BUTTON_H

//按键宏定义
#define START_PORT      GPIO_BUTTON_BUTTON_START_PORT           //开始
#define FUNTION1_PORT   GPIO_BUTTON_BUTTON_FUNTION1_PORT        //功能1
#define FUNTION2_PORT   GPIO_BUTTON_BUTTON_FUNTION2_PORT        //功能2

#define START_PIN       GPIO_BUTTON_BUTTON_START_PIN
#define FUNTION1_PIN    GPIO_BUTTON_BUTTON_FUNTION1_PIN
#define FUNTION2_PIN    GPIO_BUTTON_BUTTON_FUNTION2_PIN


void START_BUTTON(void);
void FUNTION1_BUTTON(void);
void FUNTION2_BUTTON(void);
void button_scanf(void);

#endif

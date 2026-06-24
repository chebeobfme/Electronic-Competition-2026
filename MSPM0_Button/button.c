#include "main.h"

uint8_t count = 0;
void START_BUTTON(void)
{
    //开始按键
    if(DL_GPIO_readPins(START_PORT , START_PIN) == 0)
    {
        while(DL_GPIO_readPins(START_PORT , START_PIN) == 0);
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN_LED_PIN);
        count++;
    } 
}


void FUNTION1_BUTTON(void)
{
    //开始按键
    if(DL_GPIO_readPins(FUNTION1_PORT , FUNTION1_PIN) == 0)
    {
        while(DL_GPIO_readPins(FUNTION1_PORT , FUNTION1_PIN) == 0);
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN_LED_PIN);
        count++;
    } 
}


void FUNTION2_BUTTON(void)
{
    
    //开始按键
    if(DL_GPIO_readPins(FUNTION2_PORT , FUNTION2_PIN) == 0)
    {
        while(DL_GPIO_readPins(FUNTION2_PORT , FUNTION2_PIN) == 0);
        DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_PIN_LED_PIN);
    } 
}

void button_scanf(void)
{
    START_BUTTON();
    // FUNTION1_BUTTON();
    // FUNTION2_BUTTON();
    
}

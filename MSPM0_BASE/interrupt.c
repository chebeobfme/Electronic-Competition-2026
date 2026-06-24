#include "main.h"

uint8_t enable_group1_irq = 0;

//中断初始化
void Interrupt_Init(void)
{
    //开启总中断
    if(enable_group1_irq)
    {
        NVIC_EnableIRQ(1);
    }
}

//滴答定时器中断
void SysTick_Handler(void)
{
    tick_ms++;
}


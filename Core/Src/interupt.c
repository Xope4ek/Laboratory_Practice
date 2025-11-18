#include "interupt.h"

void EXTI15_10_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
    btnCount++;
    flag = !flag;
}

void SysTick_Handler(void)
{
    global_systick_tim_count++;
    global_delay_tim_count++;
}
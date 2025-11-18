#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "main.h"

extern volatile uint8_t flag, btnCount;
extern volatile uint32_t global_systick_tim_count;
extern volatile uint16_t global_delay_tim_count;
// void EXTI15_10_IRQHandler(void);

void delay(uint32_t);

#endif
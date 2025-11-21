#ifndef INTERRUPT_H
#define INTERRUPT_H
#include "main.h"
extern volatile uint32_t system_time_ms;
extern volatile uint8_t button1_pressed_flag; 
extern volatile uint8_t button2_press_event_flag;
extern volatile uint8_t button3_press_event_flag;

void SysTick_Handler(void);
void EXTI0_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif
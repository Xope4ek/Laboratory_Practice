#ifndef INIT_H
#define INIT_H

#include <stdint.h>
#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F429ZI/stm32f429xx.h"
#include "stm32f4xx.h"
#include <stdbool.h>

//LB2
void GPIO_init_CMSIS(void);
void RCC_INIT(void);
void ITR_INIT(void);
void SysTick_Init(void);

void LED_AllOff(void);
void LED_On_Index(uint8_t index);
void LED_Off_Index(uint8_t index);
void LED_SetActive(uint8_t index);

extern volatile uint8_t led1_state;
extern volatile uint8_t led2_state;
extern volatile uint8_t led3_state;
extern volatile uint8_t led4_state;
extern volatile uint8_t led5_state;
extern volatile uint8_t led6_state;

#define BIT_SET(REG, BIT)   ((REG) |= (BIT))
#define BIT_READ(REG, BIT)  ((REG) & (BIT))
#endif




#include "main.h"

void GPIO_init__Memory(void){};

// Здесь должно быть включение через регистры (хардкод) синий светодиот
void GPIO_init_With_Myself_Macros (void)
{
    RCC_AHB1ENR |= RCC_GPIOA_EN | RCC_GPIOB_EN | RCC_GPIOC_EN;
    BIT_SET(GPIOB_MODER, GPIO_PIN_OUT_7);
    BIT_SET(GPIOB_OTYPER, GPIO_OFF);
    BIT_SET(GPIOB_OSPEEDR, GPIO_PIN_MED_7);
    BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_7);
}

// Включение через макроссы красный светодиот
void GPIO_init_With_Myself_Macros2 (void)
{
    RCC_AHB1ENR |= RCC_GPIOA_EN | RCC_GPIOB_EN | RCC_GPIOC_EN;
    BIT_SET(GPIOB_MODER, GPIO_PIN_OUT_14);
    BIT_SET(GPIOB_OTYPER, GPIO_OFF);
    BIT_SET(GPIOB_OSPEEDR, GPIO_PIN_MED_14);
    BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);
}

// Подключение портов PA3, РС0 и РС3
void GPIO_init_With_Myself_Macros3 (void)
{
    RCC_AHB1ENR |= RCC_GPIOA_EN | RCC_GPIOB_EN | RCC_GPIOC_EN;
    // PA3
    BIT_SET(GPIOA_MODER, GPIO_PIN_IN_3);
    BIT_SET(GPIOA_OTYPER, GPIO_OFF);
    BIT_SET(GPIOA_OSPEEDR, GPIO_PIN_MED_3);
    BIT_SET(GPIOA_BSRR, GPIO_PIN_RESET_3);

    //PC0 A1
/*     BIT_SET(GPIOC_MODER, GPIO_PIN_IN_0);
    BIT_SET(GPIOC_OTYPER, GPIO_OFF);
    BIT_SET(GPIOC_OSPEEDR, GPIO_PIN_MED_0);
    BIT_SET(GPIOC_BSRR, GPIO_PIN_RESET_0); */

    //PC3
    BIT_SET(GPIOC_MODER, GPIO_PIN_IN_3);
    BIT_SET(GPIOC_OSPEEDR, GPIO_PIN_MED_3);
    BIT_SET(GPIOC_BSRR, GPIO_PIN_RESET_3);
}

// Включение через библиотеку зеленый светодиот
void GPIO_init_CMSIS(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOBEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOFEN);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODER0_0);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0_0);
   

    //PA5
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODER5_0);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED5_0);
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR5);
    //PF3
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER3_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED3_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR3);
    //PF5 (D7)
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER5_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED5_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR5);
    //PF10 (D8)
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER10_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED10_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR10);
    //PF15 (D2)
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER15_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED15_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR15);
}

void delay(volatile uint32_t count)
{
    for(; count > 0; count--)
    {
        // void
    }
}

uint32_t CheckTimeButtonPress()
{
    uint32_t long_press_time = 50000;
    if (READ_BIT(GPIOF->IDR, GPIO_IDR_ID3)) // button 3 A3 (PF3)
    {
        uint32_t press_time = 0;
        while(READ_BIT(GPIOF->IDR, GPIO_IDR_ID3))
        {
            delay(100);
            press_time += 100;
            if (press_time >= long_press_time)
            {
                while(READ_BIT(GPIOF->IDR, GPIO_IDR_ID3))
                {
                    delay(100);
                }
                return 2;
            }
        }
        return 1;
    }
    return 0;
}

void TimeMerz(volatile uint32_t mode)
{
    if (mode == 0)
    {
        delay(30000*6);
    }
    if (mode == 1)
    {
        delay(15000*6);
    }
    if (mode == 2)
    {
        delay(7500*6);
    }
}

 



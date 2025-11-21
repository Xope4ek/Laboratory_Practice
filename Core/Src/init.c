
#include "main.h"


void GPIO_init_CMSIS(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIOFEN);

    SET_BIT(GPIOB->MODER, GPIO_MODER_MODER0_0);
    SET_BIT(GPIOB->OSPEEDR, GPIO_OSPEEDR_OSPEED0_0);
    //Инициализация кнопок на PC0, PF5, PF13 (A1, A4, D7 соответственно)
    //PC0
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER0_0);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED0_0);
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR0);
    //PF5
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER5_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED5_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR5);
    //PF13
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER13_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED13_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR13);
    // Инициализация шести диодов PA3, PC3, PF3, PF10, PF12, PF15 (A0, A2, A3, A5, D8, D2 соответственно)
    //PA3
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODER3_0);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED3_0);
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR3);
    //PC3
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER3_0);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED3_0);
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);
    //PF3
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER3_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED3_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR3);
    //PF10
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER10_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED10_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR10);
    //PF12
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER12_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED12_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR12);
    //PF15
    SET_BIT(GPIOF->MODER, GPIO_MODER_MODER15_0);
    SET_BIT(GPIOF->OSPEEDR, GPIO_OSPEEDR_OSPEED15_0);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR15);
}

void RCC_INIT(void){
    // Настройка порта РС9 в качестве МСО2
    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER9_1);                  //Настраиваем пин на альтернативный режим
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDR_OSPEED9_Msk);           //Настраиваем пин на максимальную скорость работы
    MODIFY_REG(GPIOC->AFR[1], GPIO_AFRH_AFSEL9_Msk, 0x0);        //Выбираем тип альтернативной функции – Выход MCO2
    // Настройка порта РA8 в качестве МСО1
    SET_BIT(GPIOA->MODER, GPIO_MODER_MODE8_1);
    SET_BIT(GPIOA->OSPEEDR, GPIO_OSPEEDR_OSPEED8);
    CLEAR_BIT(GPIOA->AFR[1], GPIO_AFRH_AFSEL8);

    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL);
    CLEAR_REG(RCC->CFGR);
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);

    CLEAR_BIT(RCC->CR, RCC_CR_HSION);
    SET_BIT(RCC->CR, RCC_CR_HSEON);                             //Включение внешнего источника тактирования высокой частоты
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);
    SET_BIT(RCC->CR, RCC_CR_CSSON);                             // Включение Clock Security

    // PLL configurator
    CLEAR_REG(RCC->PLLCFGR);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);              // Источник тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_2);                  // Деление источника тактирования 
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_3 | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_8); // число 360 в  bin //2457 для 180
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                  // при 0 Деление частоты после умножения на 4 (PLLP) // при 1 деление частоты на 6 
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_3); // Деление частоты на 15 v bin итого 48МГц

    // tact configurator
    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                         // В качестве системного тактирования выбран PLL 
    SET_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                      //Предделитель шины AHB1 настроен на 1(без деления)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV4);                     //Предделитель шины APB1 настроен на 4
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV2);                     //Предделитель шины APB2 настроен на 2
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO1);                           //настройка вывода частоты на MCO1
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                         //настройка вывода частоты на MCO2
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO1PRE_2 | RCC_CFGR_MCO1PRE_1); //Предделитель 4 для вывода частоты на MCO1
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1); //Предделитель 4 для вывода частоты на MCO2

    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_5WS);                  // Установка 5 циклов ожидания для флэш памями

    SET_BIT(RCC->CR, RCC_CR_PLLON);                              // Включение блока PLL
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);           //    
// Все закончили
}

void ITR_INIT(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);
    //PF13
    SET_BIT(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_PF);
    SET_BIT(EXTI->IMR, EXTI_IMR_IM13);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR13);
    //PC0
    SET_BIT(SYSCFG->EXTICR[0], SYSCFG_EXTICR1_EXTI0_PC);
    SET_BIT(EXTI->IMR, EXTI_IMR_IM0);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR0);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR0);
    //PF5
    SET_BIT(SYSCFG->EXTICR[1], SYSCFG_EXTICR2_EXTI5_PF);
    SET_BIT(EXTI->IMR, EXTI_IMR_IM5);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR5);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR5);

    NVIC_SetPriority(EXTI15_10_IRQn,2);
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    NVIC_SetPriority(EXTI0_IRQn, 3);
    NVIC_EnableIRQ(EXTI0_IRQn);

    NVIC_SetPriority(EXTI9_5_IRQn, 4);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

void SysTick_Init(void){
    CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //На всякий случай, предварительно, выключим счётчик
    SET_BIT(SysTick->CTRL, SysTick_CTRL_TICKINT_Msk); //Разрешаем прерывание по системному таймеру
    SET_BIT(SysTick->CTRL, SysTick_CTRL_CLKSOURCE_Msk); //Источник тактирования будет идти из AHB без деления
    MODIFY_REG(SysTick->LOAD, SysTick_LOAD_RELOAD_Msk, (180000-1) << SysTick_LOAD_RELOAD_Pos); //Значение с которого начинается счёт, эквивалентное 1 кГц, т.к. 180000000/180000 = 1000 раз в секнду или 1 кГц 
    MODIFY_REG(SysTick->VAL, SysTick_VAL_CURRENT_Msk, (180000-1) << SysTick_VAL_CURRENT_Pos); //Очистка поля
    SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk); //Включим счётчик
} 

void LED_AllOff(void)
{
    SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR3);
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR3);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR10);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR12);
    SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR15);

    led1_state = 0;
    led2_state = 0;
    led3_state = 0;
    led4_state = 0;
    led5_state = 0;
    led6_state = 0;
}

void LED_On_Index(uint8_t index)
{
    switch (index)
    {
    case 0: SET_BIT(GPIOA->BSRR, GPIO_BSRR_BS3); led1_state = 1; break;
    case 1: SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS3); led2_state = 1; break;
    case 2: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS3); led3_state = 1; break;
    case 3: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS10); led4_state = 1; break;
    case 4: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS12); led5_state = 1; break;
    case 5: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS15); led6_state = 1; break;
    }
}

void LED_Off_Index(uint8_t index)
{
    switch (index)
    {
    case 0: SET_BIT(GPIOA->BSRR, GPIO_BSRR_BR3); led1_state = 0; break;
    case 1: SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR3); led2_state = 0; break;
    case 2: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR3); led3_state = 0; break;
    case 3: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR10); led4_state = 0; break;
    case 4: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR12); led5_state = 0; break;
    case 5: SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR15); led6_state = 0; break;
    }
}

void LED_SetActive(uint8_t index)
{
    LED_AllOff();
    LED_On_Index(index);
}
#include "main.h"
/* #include "interupt.h" */

int main(void)
{
    uint32_t button = 0;   
    uint32_t button_Set = 0;
    uint32_t pressed = 0;

    uint32_t light1 = 0;
    uint32_t light2 = 0;
    uint32_t light3 = 0;
    uint32_t light4 = 0;
    uint32_t light5 = 0;
    uint32_t light6 = 0;

    GPIO_init_With_Myself_Macros ();
    GPIO_init_With_Myself_Macros2 ();
    GPIO_init_With_Myself_Macros3 ();
    GPIO_init_CMSIS ();
    while (1)
    {
        //Основное задание вариант 4
        // non control button 1
        if (BIT_READ(GPIOA_IDR, GPIO_PIN_IDR_3)) // Если поступила единица на РА3(А0)
        {
            GPIOC->MODER &= ~0x55555555;
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_14); // Включает красный светодиот comp
        }
        else
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14);
        }
        // non control button 2 A3 (PF3)
        if (READ_BIT(GPIOF->IDR, GPIO_IDR_ID3))
        {
            GPIOC->MODER = 0x55555555;
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_7); // Включает Синий
            BIT_SET(GPIOC_BSRR, GPIO_PIN_SET_3);
        }
        else
        {
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_7); // Выключает Синий
        }
        // control button 3 A2
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_IDR_3)) // Если нажата 3я кнопка A2 и "на вход", то True
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0); //Желтый
        }
        else
        {
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0); //Желтый
        }
        BIT_SET(GPIOC_BSRR, GPIO_PIN_SET_3); // Включает "свой" светодиот
                  
        

// Дополнительное задание
/*
        // Реализация выполнения задания для первой кнопки по короткому нажатию
        if (BIT_READ(GPIOA_IDR, GPIO_PIN_IDR_3)) // Если поступила единица на РА3(А0)
        {
            button++;
            delay(50000);
        }
        switch (button)
        {
        case 1:
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_14); // включает красный
            TimeMerz(light1);
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_14); // выключает красный
            TimeMerz(light1);
            break;
        case 2:
            BIT_SET(GPIOB_BSRR, GPIO_PIN_SET_7); // Включает Синий
            TimeMerz(light2);
            BIT_SET(GPIOB_BSRR, GPIO_PIN_RESET_7); // Выключает Синий
            TimeMerz(light2);
            break;
        case 3:
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS0); // вкл Желтый
            TimeMerz(light3);
            SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR0); // выкл Желтый
            TimeMerz(light3);
            break;
        case 4:
            BIT_SET(GPIOA->BSRR, GPIO_BSRR_BS5); // вкл свой D4
            TimeMerz(light4);
            BIT_SET(GPIOA->BSRR, GPIO_BSRR_BR5); // выкл свой D4
            TimeMerz(light4);
            break;
        case 5:
            SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS5); // вкл D7
            TimeMerz(light5);
            SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR5); // выкл D7
            TimeMerz(light5);
            break;
        case 6:
            SET_BIT(GPIOF->BSRR, GPIO_BSRR_BS15); // вкл D2
            TimeMerz(light6);
            SET_BIT(GPIOF->BSRR, GPIO_BSRR_BR15); // выкл D2
            TimeMerz(light6);
            break;
        default:
            button = 0;
            break;
        }

    // Реализация выполнения задания для 3ей кнопки по короткому и длинному нажатию        
        pressed = CheckTimeButtonPress();      
        if (pressed == 1)
        {
            button--;
            pressed = 0;
        }
        if (pressed == 2)
        {
            button_Set++;
            pressed = 0;
        }
    // Реализация выполнения задания для 2ой кнопки по короткому нажатию
        if (BIT_READ(GPIOC_IDR, GPIO_PIN_IDR_3)) // Если нажата 2я кнопка PIN A2
        {
            switch (button_Set)
            {
            case 1:
                if (light1 < 2) {light1++;}
                else {light1 = 0;}
                break;
            case 2:
                if (light2 < 2) {light2++;}
                else {light2 = 0;}
                break;
            case 3:
                if (light3 < 2) {light3++;}
                else {light3 = 0;}
                break;
            case 4:
                if (light4 < 2) {light4++;}
                else {light4 = 0;}
                break; 
            case 5:
                if (light5 < 2) {light5++;}
                else {light5 = 0;}
                break; 
            case 6:
                if (light6 < 2) {light6++;}
                else {light6 = 0;}
                break;  
            default:
                button_Set = 0;
                break;
            }
            delay(50000);
        }
        */
    }
}        


        

 



#include "key.h"
#include "led.h"
#include <stdio.h>

void KEY_IRQ_NVIC_init()
{
    NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0X01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0X02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void KEY_IRQ_init()
{
    EXTI_InitTypeDef exit_def;
    EXTI_StructInit(&exit_def);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ENABLE CLOCK
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA,EXTI_PinSource0);

    exit_def.EXTI_Line = EXTI_Line0;
    exit_def.EXTI_Mode = EXTI_Mode_Interrupt;
    exit_def.EXTI_Trigger = EXTI_Trigger_Falling;
    exit_def.EXTI_LineCmd = ENABLE;
    EXTI_Init(&exit_def);
    KEY_IRQ_NVIC_init();
}

void KEY_Init(){
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    GPIO_InitStructure.GPIO_Pin = KEY1_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    KEY_IRQ_init();
}

void EXTI0_IRQHandler()
{
    EXTI_ClearITPendingBit(EXTI_Line0);
    EXTI_ClearFlag(EXTI_Line0);
    LED1_ON();
    printf("you press key\n");
}
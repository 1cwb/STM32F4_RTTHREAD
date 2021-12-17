#ifndef _LED_H
#define _LED_H
#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "sys.h"

#define LED1_PORT GPIOC
#define LED1_PIN  GPIO_Pin_13

void LED_init();

// #define LED1_ON()  {GPIO_ResetBits(LED1_PORT,LED1_PIN);}
// #define LED1_OFF() {GPIO_SetBits(LED1_PORT,LED1_PIN);}

#define LED1_ON() (PCout(13) = 0)
#define LED1_OFF() (PCout(13) = 1)
#endif
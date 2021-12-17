#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"

#ifndef _KEY_H
#define _KEY_H

#define KEY1_PORT GPIOA
#define KEY1_PIN GPIO_Pin_0

void KEY_Init();

#define READ_KEY1() GPIO_ReadInputDataBit(KEY1_PORT,KEY1_PIN)
#define IS_KEY1_ON() (READ_KEY1() == 0x00)

#endif
#include "stm32f4xx.h"
#include "delay.h"
#include "bsp_usart.h"
#include "led.h"
#include "key.h"
#include "stm32f4xx.h"

extern int thread_test();
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}


int main(void)
{
  USART1_Config(115200);
  LED_init();
  RCC_ClocksTypeDef rcc;
  RCC_GetClocksFreq(&rcc);
  while(1)
  {
		LED1_ON();

    Delay(0xfffff);
		LED1_OFF();
    Delay(0xfffff);
    printf("test----\n");
  }
}


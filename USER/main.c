#include "stm32f4xx.h"
#include "delay.h"
#include "bsp_usart.h"
#include "led.h"
#include "key.h"
#include "stm32f4xx.h"
  
void Delay(__IO uint32_t nCount);

void Delay(__IO uint32_t nCount)
{
  while(nCount--){}
}

int main(void)
{

  USART1_Config(115200);
  KEY_Init();
  LED_init();
  RCC_ClocksTypeDef rcc;
  RCC_GetClocksFreq(&rcc);
  delay_init(rcc.HCLK_Frequency/1000000);
  while(1){
    printf("sys clock is %lu\n",rcc.SYSCLK_Frequency);
		LED1_ON();
		delay_ms(1000);
		LED1_OFF();
		delay_ms(1000);
	}
}


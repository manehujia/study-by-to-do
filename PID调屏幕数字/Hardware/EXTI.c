#include "EXTI.h"         
#include "stm32f10x.h" 
void Encoder_Init(void)
{

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);		//??GPIOB???
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);		//??AFIO???,????????AFIO???
	

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);						//?PB0?PB1??????????
	
	/*AFIO??????*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);//??????0?????GPIOB,???PB0???????
	
	/*EXTI???*/
	EXTI_InitTypeDef EXTI_InitStructure;						//???????
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;					//?????????
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;			//????????????
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;		//?????????????
	EXTI_Init(&EXTI_InitStructure);								//????????EXTI_Init,??EXTI??
	
	/*NVIC????*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//??NVIC???2
	
	/*NVIC??*/
	NVIC_InitTypeDef NVIC_InitStructure;						//???????
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//????NVIC?EXTI0?
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				//??NVIC????
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;	//??NVIC?????????1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			//??NVIC?????????1
	NVIC_Init(&NVIC_InitStructure);								//????????NVIC_Init,??NVIC??

}

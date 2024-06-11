#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);

#endif


/**
  * 函    数：定时中断初始化
  * 参    数：无
  * 返 回 值：无
	    注意点：TIM_Period的值
			注意点：TIM_Prescaler的值
			cnt计数频率：时钟频率/PSC是TIM的
			触发中断：cnt=ARR(TIM_Period的值)
			即中断频率 = 时钟频率/(PSC * ARR)
			中断函数在末尾
  */
	
	
	/* 定时器中断函数，可以复制到使用它的地方
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/


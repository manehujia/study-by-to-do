#ifndef __TIMER_H
#define __TIMER_H

void Timer_Init(void);

#endif


/**
  * ��    ������ʱ�жϳ�ʼ��
  * ��    ������
  * �� �� ֵ����
	    ע��㣺TIM_Period��ֵ
			ע��㣺TIM_Prescaler��ֵ
			cnt����Ƶ�ʣ�ʱ��Ƶ��/PSC��TIM��
			�����жϣ�cnt=ARR(TIM_Period��ֵ)
			���ж�Ƶ�� = ʱ��Ƶ��/(PSC * ARR)
			�жϺ�����ĩβ
  */
	
	
	/* ��ʱ���жϺ��������Ը��Ƶ�ʹ�����ĵط�
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/


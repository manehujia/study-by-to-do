#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Key.h"
#include "timer.h"
#include "Delay.h"
#include "usert.h"
#include "EXTI.h" 
/*资源使用情况
中断    TIM4定时中断   串口1接收中断
外设
GPIOA.B    OLED：PB8.9    按键：PB1.11

串口1 PA9.10
	
*/

//全局变量定义开始================================================
int num;
int x,y;
uint16_t g;
double kp,ki,kd,err,t,sum,errlast,diff;
extern int high_byte;
extern int low_byte;
//全局变量定义结束================================================
//函数声明开始====================================================
void PID(void);
//函数声明结束====================================================

//主函数开始======================================================
int main(void)
{
	/*模块初始化*/
	OLED_Init();		
//	Key_Init();
  Timer_Init();
	Serial_Init();
	Encoder_Init();
	
	
  OLED_ShowChar(2,1 ,'g');
//	OLED_ShowChar(3,1 ,'t');
//	OLED_ShowChar(4,1 ,'e');
	
	
	t=150;
	
	
	while (1)
	{	
//		num=Key_GetNum();
//		 {
//		    if(num==1)
//				{
//					g+=100;
//			  	num=0;
//				}
//		 } 
	//	OLED_ShowSignedNum(2, 2, g, 5);	
		OLED_ShowBinNum(2, 1, g, 16);
      g=high_byte<<8|low_byte;
//		OLED_ShowSignedNum(3, 2, t, 5);	
//		OLED_ShowSignedNum(4, 2, err, 5);
		
		OLED_ShowBinNum(3, 2, high_byte, 16);
		OLED_ShowBinNum(4, 2, low_byte, 16);
  // PID();
	}
}
//主函数结束===============================================

//中断函数开始=============================================
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
	{
	  PID();
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);			//清除TIM2更新事件的中断标志位														
	}
}
//中断函数结束=============================================
//自定义函数区开始=========================================
void PID()
{
	kp=1.5;
	ki=0.2;
	kd=-0.2;
	
	err=g-t;
	sum=errlast+err;
	diff=err-errlast;
	
	t=kp*err+ki*sum+ki*diff+t;
	errlast=err;
	if(sum>1000||sum<-1000)
	{
			sum=100;
	}
}
//自定义函数区结束=========================================

void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) == SET)		//判断是否是外部中断0号线触发的中断
	{
		/*如果出现数据乱跳的现象，可再次判断引脚电平，以避免抖动*/
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1)
		{
					g=g+100;		
		}
		EXTI_ClearITPendingBit(EXTI_Line0);			//清除外部中断0号线的中断标志位
													//中断标志位必须清除
													//否则中断将连续不断地触发，导致主程序卡死
	}
}



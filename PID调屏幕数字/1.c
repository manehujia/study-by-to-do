//#include "stm32f10x.h"                  // Device header
//#include "OLED.h"
//#include "Key.h"
//#include "timer.h"
//#include "Delay.h"
//#include "usert.h"
///*资源使用情况
//中断    TIM4定时中断   串口1接收中断
//外设
//GPIOA.B    OLED：PB8.9    按键：PB1.11

//串口1 PA9.10
//	
//*/

////全局变量定义开始================================================
//int num;
//int x,y;

//double kp,ki,kd,err,g,t,sum,errlast,diff;
////全局变量定义结束==============================================================

////函数声明开始====================================================
//void PID(void);
////函数声明结束==============================================================

////主函数开始=======================================================
//int main(void)
//{
//	/*模块初始化*/
//	OLED_Init();		
//	Key_Init();
//  Timer_Init();
//	Serial_Init();

//	OLED_ShowChar(3,1 ,'t');
//	OLED_ShowChar(2,1 ,'g');
//	OLED_ShowChar(4,1 ,'e');
//	t=150;
//	g=500;
//	
//	while (1)
//	{	
//		num=Key_GetNum();
//		 {
//		    if(num==1)
//					g=200;
//		 } 
//		OLED_ShowSignedNum(2, 2, g, 5);	
//		OLED_ShowSignedNum(3, 2, t, 5);	
//		OLED_ShowSignedNum(4, 2, err, 5);
//    PID();
//	}
//}
////主函数结束=======================================================

////中断函数开始==============================================
//void TIM4_IRQHandler(void)
//{
//	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
//	{
//	  PID();
//		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);			//清除TIM2更新事件的中断标志位														
//	}
//}
////中断函数结束======================================================

////自定义函数区开始=========================================
//void PID()
//{
//	kp=0.3;
//	ki=0.2;
//	kd=0.2;
//	
//	err=g-t;
//	sum=errlast+err;
//	diff=errlast-err;
//	
//	t=kp*err+ki*sum+ki*diff+t;
//	errlast=err;
//	if(sum>1000||sum<-1000)
//	{
//			sum=100;
//	}
//}
////自定义函数区结束=====================================================



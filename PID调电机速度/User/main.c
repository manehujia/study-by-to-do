#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "Encoder.h"
#include "Motor.h"
#include "Serial.h"
void PID(void);
double Speed;			//定义速度变量
uint8_t KeyNum;
double PWM;
int num;
int x,y;
double kp,ki,kd,err,g,t,sum,errlast,diff;
int main(void)
{
	/*模块初始化*/
		Serial_Init();
		Motor_Init();
	OLED_Init();		//OLED初始化
	Timer_Init();		//定时器初始化
	Encoder_Init();		//编码器初始化
	PWM=50;
	/*显示静态字符串*/
	OLED_ShowString(1, 1, "Speed:");//实际速度
	OLED_ShowString(2, 1, "PWM:");//PWM
	OLED_ShowString(3, 1, "err:");//PWM	

	OLED_ShowString(4, 1, "g:");//PWM	
	while (1)
	{
	
		
		Motor_SetSpeed(PWM);
		
		OLED_ShowSignedNum(1, 7, Speed, 6);	//不断刷新显示编码器测得的最新速度
		OLED_ShowSignedNum(2, 7, PWM, 6);
		OLED_ShowSignedNum(3, 7, err,6);
		
		OLED_ShowSignedNum(4, 7, g,6);
	}
}

/**
  * 函    数：TIM4中断函数
  * 参    数：无
  * 返 回 值：无
  * 注意事项：此函数为中断函数，无需调用，中断触发后自动执行
  *           函数名为预留的指定名称，可以从启动文件复制
  *           请确保函数名正确，不能有任何差异，否则中断函数将不能进入
  */
void TIM4_IRQHandler(void)//每秒一次
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) == SET)		//判断是否是TIM2的更新事件触发的中断
	{
		Speed = Encoder_Get();								//每隔固定时间段读取一次编码器计数增量值，即为速度值
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);			//清除TIM2更新事件的中断标志位
		PID();			  		//中断标志位必须清除
									  	//否则中断将连续不断地触发，导致主程序卡死
	}
}
void PID()
{
	
	kp=0.1;
	ki=0.02;
	//kd=-0.2;
	//g=Speed;//g作为目标值,刚测的
	//t=PWM;//t作为当前值，也就是给电机的pwm
	err=g-Speed;
	sum=sum+err;
	//diff=err-errlast;
	
	PWM=kp*err+PWM;//+ki*diff+t;//这里调的一定是PWM   ki*sum+
	errlast=err;
	if(PWM>1000)
  {
			PWM=1000;
	}
		if(PWM<-1000)
  {
			PWM=-1000;
	}
		if(sum>1000)
  {
			sum=1000;
	}
			if(sum<-1000)
  {
			sum=-1000;
	}
	
}

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "sys.h" // 包含系统相关的头文件
#include "mpu6050.h" // 包含MPU6050传感器的头文件
#include "inv_mpu.h" // 包含MPU6050传感器的库
#include "inv_mpu_dmp_motion_driver.h" // 包含MPU6050传感器的DMP库
#include "Timer.h"
#include "Encoder.h"
#include "Motor.h"
#include "pid.h"
float Kp=-420,Ki=0,Kd=-2000;  //调完速度环后精调
float VKp=+190,VKi=0.95;          

int Speed;
//double PWM;
//int num;
//int x,y;
//double kp,ki,kd,err,g,t,sum,errlast,diff;
float pitch,roll,yaw; 		
void PID(void);

void PWM_Xianfu(int max,int *PWM)
{
	if(*PWM>max)  *PWM = max;
	if(*PWM<-max) *PWM =-max;
}

int main(void)
{
	int t,m,g;
	t=MPU_Init();				
	m=mpu_dmp_init();
	OLED_Init();		//OLED初始化
	Timer_Init();
	Encoder_Init();
	Motor_Init();
	while (1)
	{
		 
	 while(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){};			
		OLED_ShowSignedNum(1,1,pitch,3);
		OLED_ShowSignedNum(2,1,roll,3);
		OLED_ShowSignedNum(3,1,yaw,3);
		OLED_ShowSignedNum(1,7,t,2);
		OLED_ShowSignedNum(2,7,m,2);
		OLED_ShowSignedNum(3,7,g,2);	
		 
		 
  }
}


float pitch,roll,yaw;  //欧拉角
float measure,calcu;   //测量值和理论值                   
int velocity;          //速度测量值（编码器脉冲数，非真实速度）
int PWM;               //PWM值

	
	
	

void TIM1_UP_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0)
		{ 	
			measure = roll;                                     //roll测量值                                 //roll理论值
			velocity = ( Encoder_Get3()+ Encoder_Get4() )/2; //速度测量值      

		  //PID计算：直立环+速度环（完整版本还要加转向环，转向环怎么写怎么调，请看群公告）
			PWM = vertical_PID_value(measure, 0) + velocity_PID_value(velocity); 
			PWM_Xianfu(7000,&PWM);      //PWM限幅
		
			if(1){ Motor_SetSpeed2(PWM);Motor_SetSpeed1(PWM);} //给电机PWM
			else           {Motor_SetSpeed2(0); Motor_SetSpeed1(0);}  //关闭电机		
		}	
	}
}

//void PID()
//{
//	
//	kp=0.1;
//	ki=0.08;
//	//kd=-0.2;
//	//g=Speed;//g作为目标值,刚测的
//	//t=PWM;//t作为当前值，也就是给电机的pwm
//	g=200;
//	err=g-Speed;
//	sum=sum+err;
//	diff=err-errlast;
//	
//	PWM=kp*err+ki*diff+PWM;//+ki*diff+t;//这里调的一定是PWM   ki*sum+
//	errlast=err;
//	
//	if(PWM>1000){PWM=1000;}
//	if(PWM<-1000){PWM=-1000;}
//	if(sum>1000){sum=1000;}
//	if(sum<-1000){sum=-1000;}
//}

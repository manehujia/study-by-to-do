#ifndef __PID_H
#define __PID_H

int vertical_PID_value(float measure,float calcu); //ֱ����
int velocity_PID_value(int velocity);              //�ٶȻ�
void xianfu(int max);                            //pwm�޷�

#endif

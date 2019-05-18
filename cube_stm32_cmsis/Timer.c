#include "timer.h"



//ͨ�ö�ʱ���жϳ�ʼ��
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
void Timer4_Init(uint16_t psc,uint16_t arr)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);                //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr;                             //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =(psc - 1);              		//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ   
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;                        //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;         //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);                     //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(                                       				//ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM4,                                           				//TIM4
		TIM_IT_Update  |                                				//TIM �ж�Դ
		TIM_IT_Trigger,                                 				//TIM �����ж�Դ 
		ENABLE                                          				//ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;                 	//TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;       	//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;              	//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                 	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);                                 	//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);                                          	//ʹ��TIMx����
}















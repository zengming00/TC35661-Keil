/***********************************************************
��ѧ֮�� http://simcom.taobao.com/
��ϵ��ʽ��15296811438 �ֹ�
*************************************************************/

#include "sys.h"
   
		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_13; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOC, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8| GPIO_Pin_9; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);				//��ʼ��������

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
    GPIO_Init(GPIOA, &GPIO_InitStructure);

}
 
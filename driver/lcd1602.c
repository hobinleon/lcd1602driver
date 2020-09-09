/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:33
 * @LastEditTime: 2020-09-09 09:15:28
 * @LastEditors: LJB
 * @Description: lcd1602������Դ����
 * @FilePath: \lcd1602driver\driver\lcd1602.c
 * @
 */
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "lcd1602.h"
#include "common.h"

#define RS_HIGH() digit_high(RS_PORT, RS_PIN) //��������,RS=0��ѡ��ָ��Ĵ�����RS=1��ѡ�����ݼĴ���
#define RS_LOW() digit_low(RS_PORT, RS_PIN) 

#define RW_HIGH() digit_high(RW_PORT, RW_PIN) //��д����,R/W=0   д������R/W=1  ������
#define RW_LOW() digit_low(RW_PORT, RW_PIN) 

#define E_HIGH() digit_high(E_PORT, E_PIN) //д����ʱ���ź��½�����Ч��������ʱ���ߵ�ƽ��Ч
#define E_LOW() digit_low(E_PORT, E_PIN) 

void lcd_init(lcd_info_type lcd_info)
{
   DATA_PORT->CR1 |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //����(��),����(д)    
   DATA_PORT->DDR |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //����Ϊ���ģʽ
    RS_PORT->DDR |= RS_PIN ;
    RW_PORT->DDR |= RW_PIN ;
    E_PORT->DDR  |= E_PIN ;

    lcd_write(COMMAND_REGISTER, 0X28 );
}

/**
 * @description: д�뵽����Ĵ����������ݼĴ���
 * @param areg ָ�������������, adata Ҫд������� 
 * @return {��} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata)
{
    RW_LOW();   //д����
    if(areg == COMMAND_REGISTER)
    {
        RS_LOW();   //����Ĵ���
    }
    else if (areg == DATA_REGISTER)
    {
        /* ���ݼĴ��� */
        RS_HIGH();
    }
    E_HIGH();
    DATA_PORT->ODR &=0X0F ;
    DATA_PORT->ODR |=(uint8_t)((adata)&(0xF0)) ;
    E_LOW();     

    E_HIGH();
    DATA_PORT->ODR &=0X0F ;
    DATA_PORT->ODR |=(uint8_t)(((adata & 0x0F))<<4) ;
    E_LOW();   

}
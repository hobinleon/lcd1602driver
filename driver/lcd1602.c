/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:33
 * @LastEditTime: 2020-09-10 20:21:50
 * @LastEditors: LJB
 * @Description: lcd1602������Դ����
 * @FilePath: \lcd1602driver\driver\lcd1602.c
 * @�����ֲ,Ӧ���޸�;lcd_driver.h�����Ӳ�����弰���Ӳ���ĺ��������RS_HIGH(),����lcd_write(),busy_flag()
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

#define SET_PORT_INPUT() DATA_PORT->DDR &=0X0F  
#define SET_PORT_OUTPUT() DATA_PORT->DDR |=0XF0 

#define DELAY_COUNT 50000
void lcd_init(lcd_info_type lcd_info)
{
   DATA_PORT->CR1 |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //����(��),����(д)    
   DATA_PORT->DDR |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //����Ϊ���ģʽ
    RS_PORT->DDR |= RS_PIN ;
    RW_PORT->DDR |= RW_PIN ;
    E_PORT->DDR  |= E_PIN ;
    
    Delay(4998);    //2Mhzϵͳʱ����,�ӳ�15ms����Ҫ��������
    lcd_write(COMMAND_REGISTER, 0X28 );
    Delay(1664);     //�ӳ�5ms 
    lcd_write(COMMAND_REGISTER, 0X28 );
    wait_for_busy(); 
    lcd_write(COMMAND_REGISTER, 0X28 );
    Delay(DELAY_COUNT);
    lcd_clear();
    wait_for_busy(); // Delay(DELAY_COUNT);
    lcd_write(COMMAND_REGISTER, 0X06);  //�������
    wait_for_busy();
    lcd_write(COMMAND_REGISTER, 0x0c );
}

/**
 * @description: д�뵽����Ĵ����������ݼĴ���
 * @param areg ָ�������������, adata Ҫд������� 
 * @return {��} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata)
{
    SET_PORT_OUTPUT();
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

/**
 * @description: ��lcdæ�ı�־.
 * @param {type} 
 * @return {type} ����ֵΪ���ʱ��,��ʾæ.Ӧ�õȴ�.��֮���Խ��в���
 */
bool busy_flag(void)
{
    RS_LOW();
    RW_HIGH();
    E_HIGH();
    SET_PORT_INPUT();
    return (bool)(DATA_PORT->IDR &= DATA_BIT7 );
}

/**
 * @description: �ȴ�ֱ��æ��־�����
 * @param {type} 
 * @return {type} 
 */
void wait_for_busy(void)
{
    while (busy_flag()) ;
}

/**
 * @description: ��ʾһ���ַ�
 * @param a Ҫ��ʾ���ַ� 
 * @return  
 */
void lcd_putc(char a)
{
    wait_for_busy();
    lcd_write(DATA_REGISTER, a) ;
}


/**
 * @description: ��ʾһ���ַ���
 * @param s �ַ���,������/0��β
 * @return
 */
void lcd_puts(char *s) 
{
    uint8_t i;
    for(i = 0;i <0xff; i++)
    {
        if ( *s != '\0')
        {
            lcd_putc(*s) ;
            s++ ;
        }
        else
          break ;
    }
}
/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:33
 * @LastEditTime: 2020-09-09 09:15:28
 * @LastEditors: LJB
 * @Description: lcd1602的驱动源代码
 * @FilePath: \lcd1602driver\driver\lcd1602.c
 * @
 */
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "lcd1602.h"
#include "common.h"

#define RS_HIGH() digit_high(RS_PORT, RS_PIN) //命令引脚,RS=0，选择指令寄存器；RS=1，选择数据寄存器
#define RS_LOW() digit_low(RS_PORT, RS_PIN) 

#define RW_HIGH() digit_high(RW_PORT, RW_PIN) //读写引脚,R/W=0   写操作；R/W=1  读操作
#define RW_LOW() digit_low(RW_PORT, RW_PIN) 

#define E_HIGH() digit_high(E_PORT, E_PIN) //写操作时，信号下降沿有效；读操作时，高电平有效
#define E_LOW() digit_low(E_PORT, E_PIN) 

void lcd_init(lcd_info_type lcd_info)
{
   DATA_PORT->CR1 |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //上拉(读),推挽(写)    
   DATA_PORT->DDR |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //配置为输出模式
    RS_PORT->DDR |= RS_PIN ;
    RW_PORT->DDR |= RW_PIN ;
    E_PORT->DDR  |= E_PIN ;

    lcd_write(COMMAND_REGISTER, 0X28 );
}

/**
 * @description: 写入到命令寄存器或者数据寄存器
 * @param areg 指定是命令还是数据, adata 要写入的数据 
 * @return {无} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata)
{
    RW_LOW();   //写操作
    if(areg == COMMAND_REGISTER)
    {
        RS_LOW();   //命令寄存器
    }
    else if (areg == DATA_REGISTER)
    {
        /* 数据寄存器 */
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
/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:33
 * @LastEditTime: 2020-09-10 20:21:50
 * @LastEditors: LJB
 * @Description: lcd1602的驱动源代码
 * @FilePath: \lcd1602driver\driver\lcd1602.c
 * @如果移植,应该修改;lcd_driver.h的相关硬件定义及相关硬件的宏操作比如RS_HIGH(),还有lcd_write(),busy_flag()
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

#define SET_PORT_INPUT() DATA_PORT->DDR &=0X0F  
#define SET_PORT_OUTPUT() DATA_PORT->DDR |=0XF0 

#define DELAY_COUNT 50000
void lcd_init(lcd_info_type lcd_info)
{
   DATA_PORT->CR1 |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //上拉(读),推挽(写)    
   DATA_PORT->DDR |= ( DATA_BIT4|DATA_BIT5|DATA_BIT6|DATA_BIT7 ) ;   //配置为输出模式
    RS_PORT->DDR |= RS_PIN ;
    RW_PORT->DDR |= RW_PIN ;
    E_PORT->DDR  |= E_PIN ;
    
    Delay(4998);    //2Mhz系统时钟下,延迟15ms所需要的周期数
    lcd_write(COMMAND_REGISTER, 0X28 );
    Delay(1664);     //延迟5ms 
    lcd_write(COMMAND_REGISTER, 0X28 );
    wait_for_busy(); 
    lcd_write(COMMAND_REGISTER, 0X28 );
    Delay(DELAY_COUNT);
    lcd_clear();
    wait_for_busy(); // Delay(DELAY_COUNT);
    lcd_write(COMMAND_REGISTER, 0X06);  //光标设置
    wait_for_busy();
    lcd_write(COMMAND_REGISTER, 0x0c );
}

/**
 * @description: 写入到命令寄存器或者数据寄存器
 * @param areg 指定是命令还是数据, adata 要写入的数据 
 * @return {无} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata)
{
    SET_PORT_OUTPUT();
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

/**
 * @description: 读lcd忙的标志.
 * @param {type} 
 * @return {type} 返回值为真的时候,表示忙.应该等待.反之可以进行操作
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
 * @description: 等待直到忙标志被清除
 * @param {type} 
 * @return {type} 
 */
void wait_for_busy(void)
{
    while (busy_flag()) ;
}

/**
 * @description: 显示一个字符
 * @param a 要显示的字符 
 * @return  
 */
void lcd_putc(char a)
{
    wait_for_busy();
    lcd_write(DATA_REGISTER, a) ;
}


/**
 * @description: 显示一个字符串
 * @param s 字符串,必须以/0结尾
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
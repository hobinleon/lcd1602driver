/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:09
 * @LastEditTime: 2020-09-09 21:26:38
 * @LastEditors: LJB
 * @Description: LCD1602的驱动引脚定义
 * @FilePath: \lcd1602driver\driver\lcd1602.h
 * @
 */

#define DATA_PORT GPIOC     //数据脚的高四位,这里准备用4位总线方式
#define DATA_BIT7 GPIO_PIN_7
#define DATA_BIT6 GPIO_PIN_6
#define DATA_BIT5 GPIO_PIN_5
#define DATA_BIT4 GPIO_PIN_4

#define RS_PORT GPIOC   //命令引脚,RS=0，选择指令寄存器；RS=1，选择数据寄存器
#define RS_PIN GPIO_PIN_3

#define RW_PORT GPIOB   //读写引脚,R/W=0   写操作；R/W=1  读操作
#define RW_PIN GPIO_PIN_4

#define E_PORT GPIOB    //写操作时，信号下降沿有效；读操作时，高电平有效
#define E_PIN GPIO_PIN_5

#define lcd_clear()  lcd_write(COMMAND_REGISTER, 0X01)  //清除屏幕
#define lcd_return_home() lcd_write(COMMAND_REGISTER, 0X20) //AC指针归位,光标归位

typedef enum
{
    CURSOR_LEFT = ((uint8_t)0X02) ,
    CURSOR_RIGHT = ((uint8_t)0X01) 
}cursor_direction_type ;

typedef struct
{
    cursor_direction_type cursor_direction ;
}lcd_info_type ;

typedef enum
{
    COMMAND_REGISTER = ((uint8_t)(0X00)) ,
    DATA_REGISTER = ((uint8_t)(0X01)) 
}lcd_register_type ;


void lcd_init(lcd_info_type lcd_info);

/**
 * @description: 写入到命令寄存器或者数据寄存器
 * @param areg 指定是命令还是数据, adata 要写入的数据 
 * @return {无} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata) ;

/**
 * @description: 读lcd忙的标志.
 * @param {type} 
 * @return {type} 返回值为真的时候,表示忙.应该等待.反之可以进行操作
 */
bool busy_flag(void) ;

/**
 * @description: 等待直到忙标志被清除
 * @param {type} 
 * @return {type} 
 */
void wait_for_busy(void);

/**
 * @description: 显示一个字符
 * @param a 要显示的字符 
 * @return  
 */
void lcd_putc(char a) ;


/**
 * @description: 显示一个字符串
 * @param s 字符串,必须以/0结尾
 * @return
 */
void lcd_puts(char *s) ;


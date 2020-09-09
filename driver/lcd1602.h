/*
 * @Author: LJB
 * @Date: 2020-09-08 20:06:09
 * @LastEditTime: 2020-09-09 21:26:38
 * @LastEditors: LJB
 * @Description: LCD1602���������Ŷ���
 * @FilePath: \lcd1602driver\driver\lcd1602.h
 * @
 */

#define DATA_PORT GPIOC     //���ݽŵĸ���λ,����׼����4λ���߷�ʽ
#define DATA_BIT7 GPIO_PIN_7
#define DATA_BIT6 GPIO_PIN_6
#define DATA_BIT5 GPIO_PIN_5
#define DATA_BIT4 GPIO_PIN_4

#define RS_PORT GPIOC   //��������,RS=0��ѡ��ָ��Ĵ�����RS=1��ѡ�����ݼĴ���
#define RS_PIN GPIO_PIN_3

#define RW_PORT GPIOB   //��д����,R/W=0   д������R/W=1  ������
#define RW_PIN GPIO_PIN_4

#define E_PORT GPIOB    //д����ʱ���ź��½�����Ч��������ʱ���ߵ�ƽ��Ч
#define E_PIN GPIO_PIN_5

#define lcd_clear()  lcd_write(COMMAND_REGISTER, 0X01)  //�����Ļ
#define lcd_return_home() lcd_write(COMMAND_REGISTER, 0X20) //ACָ���λ,����λ

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
 * @description: д�뵽����Ĵ����������ݼĴ���
 * @param areg ָ�������������, adata Ҫд������� 
 * @return {��} 
 */
void lcd_write(lcd_register_type areg, uint8_t adata) ;

/**
 * @description: ��lcdæ�ı�־.
 * @param {type} 
 * @return {type} ����ֵΪ���ʱ��,��ʾæ.Ӧ�õȴ�.��֮���Խ��в���
 */
bool busy_flag(void) ;

/**
 * @description: �ȴ�ֱ��æ��־�����
 * @param {type} 
 * @return {type} 
 */
void wait_for_busy(void);

/**
 * @description: ��ʾһ���ַ�
 * @param a Ҫ��ʾ���ַ� 
 * @return  
 */
void lcd_putc(char a) ;


/**
 * @description: ��ʾһ���ַ���
 * @param s �ַ���,������/0��β
 * @return
 */
void lcd_puts(char *s) ;


/*
 * @Author: LJB
 * @Date: 2020-09-11 10:48:27
 * @LastEditTime: 2020-09-14 22:32:53
 * @LastEditors: LJB
 * @Description: 这里存储了一些默认设定,如果要改设定,就应该改这里的define相关内容
 * @注意事项:用到了中断,所以应该在主函数里面打开中断
 * @FilePath: \lcd1602driver\uart\uart.h
 * @
 */

#include "stm8s.h"

#define UART_STOP_BIT UART1_STOPBITS_1 
#define UART_PARITY UART1_PARITY_NO
#define UART_SYCNMODE UART1_SYNCMODE_CLOCK_DISABLE
#define UART_WAKEUP_MODE UART1_WAKEUP_IDLELINE 
#define UART_BUFFER_SIZE 127

typedef struct 
{
    /* 缓冲区数据结构 */
    uint8_t size ;  //未发送或者接收到的数据的数量
    char buffer[UART_BUFFER_SIZE];
    char *cur(uint8_t)(buffer.current_pos - buffer.buffer);rent_pos ; //当前操作的位置
}data_buffer_type;



/**
 * @description: 初始化串口
 * @param baud:波特率 
 * mode:UART1_MODE_RX_ENABLE  
 *      UART1_MODE_TX_ENABLE  
 *      UART1_MODE_TX_DISABLE 
 *      UART1_MODE_RX_DISABLE
 *      UART1_MODE_TXRX_ENABLE
 * @注意:上面的参数是引用自 stm8s_uart1.h,所以使用这个函数的文件必须引用这个头文件  
 * @return 
 */
void init_uart(uint16_t band, UART1_Mode_TypeDef mode);

/**
 * @description: 读了n个字节到缓冲区里面
 * @param buf:缓冲区指针 n 指定接收的字符数量
 * @return  返回读到的字符数量
 */
uint8_t uart_read(char *buf, uint8_t n);

/**
 * @description: 发送一个字符串
 * @param buf 字符串指针 n 要写入的数据数量
 * @return 写入缓冲区发送的字节数
 * 注意:本函数在缓冲区满的时候会导致等待,一直到所有数据存入buffer为止
 */
uint8_t uart_write(char *buf, uint8_t n);

/**
 * @description: 如果忙,返回真
 * @param {type} 
 * @return {type} 
 */
bool uart_busy();


/**
 * @description: 被接收中断调用
 * @param {type} 
 * @return {type} 
 */
void uart_send_handle();

/**
 * @description: 被发送中断调用
 * @param {type} 
 * @return {type} 
 */
void uart_receive_handle();

/**
 * @description:取得接收到的字符数量 
 * @param 
 * @return 返回接收缓冲区内接收到的数据的数量
 */
uint8_t get_received_datas_count();
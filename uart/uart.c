/*
 * @Author: LJB
 * @Date: 2020-09-11 10:48:02
 * @LastEditTime: 2020-09-15 22:33:18
 * @LastEditors: LJB
 * @Description: 串口的函数库
 * @FilePath: \lcd1602driver\uart\uart.c
 * @
 */
#include "stm8s.h"
#include "uart.h"
#include "stm8s_clk.h"
#include "stm8s_uart1.h"

static data_buffer_type received_buf,trans_buf ;


/**
 * @description: 整理缓冲区
 * @param buf 缓冲区地址 current_pos 当前处理的数据的位置 
 * @return {type} 
 */
void align_buffer(data_buffer_type *buffer);

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
void init_uart(uint16_t band, UART1_Mode_TypeDef mode)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1 , ENABLE) ; 
    UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, \
        UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_Cmd(ENABLE) ;

    //初始化缓冲区
    received_buf.size = 0 ;
    received_buf.current_pos = received_buf.buffer;
    trans_buf.size = 0;
    trans_buf.current_pos = trans_buf.buffer;
}

/**
 * @description: 整理缓冲区
 * @param buf 缓冲区地址 current_pos 当前处理的数据的位置 
 * @return {type} 
 */
void align_buffer(data_buffer_type *buffer)
{
    char *pos ;
    uint8_t i ;
    pos = (*buffer).buffer;
    i = (*buffer).current_pos - pos;    //计算已经处理了多少个数据
    i = (*buffer).size - i;// 计算还有多少个没有被处理
    while(i)
    {
        *pos = *(*buffer).current_pos ;
        pos++ ;
        (*buffer).current_pos++ ;
        i--;
    }
    (*buffer).current_pos = (*buffer).buffer ;
}

/**
 * @description: 读了n个字节到缓冲区里面
 * @param buf:缓冲区指针 n 指定接收的字符数量
 * @return  返回读到的字符数量
 */
uint8_t uart_read(char *buf, uint8_t n)
{
  return 0;
}

/**
 * @description: 发送一个字符串
 * @param buf 字符串指针 n 要写入的数据数量
 * @return 写入缓冲区发送的字节数
 * 注意:本函数在缓冲区满的时候会导致等待,一直到所有数据存入buffer为止
 */
uint8_t uart_write(char *buf, uint8_t n)
{
    char writed_count = 0;
    align_buffer(&trans_buf);
    while (n)
    {
        /* 判断缓冲区是否满 */
        //因为数组下标是从0开始的,所以必须减1
        if ((trans_buf.current_pos - trans_buf.buffer + trans_buf.size) <= UART_BUFFER_SIZE-1)
        {
            /* 写入缓冲区 */
            trans_buf.buffer[trans_buf.size] = *buf ;
            trans_buf.size ++ ;
            buf++ ;
            writed_count++ ;
            n--;
        }
        else
          break ;
    }
    return writed_count ;
}

/**
 * @description: 如果忙,返回真
 * @param {type} 
 * @return {type} 
 */
bool uart_busy()
{
  return FALSE ;
}

/**
 * @description: 被接收中断调用
 * @param {type} 
 * @return {type} 
 */
void uart_send_handle()
{
   if(trans_buf.size)
   { 
       UART1->DR = *trans_buf.current_pos;
       trans_buf.current_pos++;
       trans_buf.size--; 
   }
}

/**
 * @description:被发送中断调用
 * @param {type} 
 * @return {type} 
 */
void uart_receive_handle()
{
    
}

/**
 * @description:取得接收到的字符数量
 * @param 
 * @return 返回接收缓冲区内接收到的数据的数量
 */
uint8_t get_received_datas_count()
{
    return 0;
}
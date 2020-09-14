/*
 * @Author: LJB
 * @Date: 2020-09-13 22:06:40
 * @LastEditTime: 2020-09-14 22:34:00
 * @LastEditors: LJB
 * @Description: 测试用的文件
 * @FilePath: \lcd1602driver\test.c
 * @
 */
#include "uart\uart.h"
#include "stm8s.h"
#include "test.h"
#include "stm8s_uart1.h"

#define NUMBER_STRING "1234567890"
#define LOW_CHARACTER_STRING "abcdefghijklmnopqrstuvwxyz"
#define HIGH_CHARACTER_STRING "ABCDEFGHIJKLMNOPQRSTUVWXYZ"

void test_align()
{

}

void test_trans_handle()
{
  uart_send_handle();
}

void test_write_uart()
{
    uart_write(NUMBER_STRING,sizeof(NUMBER_STRING)-1);
    uart_write(LOW_CHARACTER_STRING,sizeof(LOW_CHARACTER_STRING)-1); 
    uart_write(HIGH_CHARACTER_STRING,sizeof(HIGH_CHARACTER_STRING)-1);
}

void test_uart_codes()
{
  init_uart(9600, UART1_MODE_TXRX_ENABLE);
  uint8_t t;
  for ( t = 0; t < 3; t++)
    test_write_uart();
  for ( t = 0; t < 10; t++)
  {
    test_trans_handle();
  }
  test_write_uart();
  
  test_trans_handle(); 
}
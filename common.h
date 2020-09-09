/*
 * @Author: LJB
 * @Date: 2020-08-24 19:25:45
 * @LastEditTime: 2020-09-09 00:41:54
 * @LastEditors: LJB
 * @Description: 一些通用的定义，函数等
 * @FilePath: \lcd1602driver\common.h
 */
#define digit_high(port, pin) port->ODR |= pin
#define digit_low(port, pin) port->ODR &= (~pin)

void Delay(uint16_t nCount);

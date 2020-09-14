/*
 * @Author: LJB
 * @Date: 2020-09-09 00:09:51
 * @LastEditTime: 2020-09-10 10:16:42
 * @LastEditors: LJB
 * @Description: 
 * @FilePath: \lcd1602driver\common.c
 * @
 */

#include "stm8s.h"
#include "common.h"

/* void delay(uint16_t aCount)
(
    while(aCount != 0)
    {
      aCount-- ;
    }
) */

/**
 * @description: 延时函数
 * @param: nCount 需要延迟的时钟周期数
 * @return 无
 * @ 进入函数需要8个时钟周期,出函数需要7个时钟周期,一个循环需要6个时钟周期
 * @ 所以延迟时间为15+6*nCount个时钟周期
 * @ 如果默认为2Mhz系统时钟,则延迟1ms需要1000/2=500,(500-15)/6=81
 */
void Delay(uint16_t nCount)
{
  //进入函数需要8个时钟周期,出函数需要7个周期
    /* Decrement nCount value */
  //每执行下面一次需要6个时钟周期
     while (nCount != 0)
     {
         nCount--;
//         nop();nop();nop();
//         nop();nop();nop();
//         nop();nop();nop();nop();
     }
}

void delay2(uint16_t nCount)
{
  while(nCount--);
}
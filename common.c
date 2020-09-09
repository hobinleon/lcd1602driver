/*
 * @Author: LJB
 * @Date: 2020-09-09 00:09:51
 * @LastEditTime: 2020-09-09 00:37:58
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

void Delay(uint16_t nCount)
{
    /* Decrement nCount value */
     while (nCount != 0)
     {
         nCount--;
     }
}

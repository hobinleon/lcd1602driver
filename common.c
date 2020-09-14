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
 * @description: ��ʱ����
 * @param: nCount ��Ҫ�ӳٵ�ʱ��������
 * @return ��
 * @ ���뺯����Ҫ8��ʱ������,��������Ҫ7��ʱ������,һ��ѭ����Ҫ6��ʱ������
 * @ �����ӳ�ʱ��Ϊ15+6*nCount��ʱ������
 * @ ���Ĭ��Ϊ2Mhzϵͳʱ��,���ӳ�1ms��Ҫ1000/2=500,(500-15)/6=81
 */
void Delay(uint16_t nCount)
{
  //���뺯����Ҫ8��ʱ������,��������Ҫ7������
    /* Decrement nCount value */
  //ÿִ������һ����Ҫ6��ʱ������
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
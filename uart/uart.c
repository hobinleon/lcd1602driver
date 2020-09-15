/*
 * @Author: LJB
 * @Date: 2020-09-11 10:48:02
 * @LastEditTime: 2020-09-15 22:33:18
 * @LastEditors: LJB
 * @Description: ���ڵĺ�����
 * @FilePath: \lcd1602driver\uart\uart.c
 * @
 */
#include "stm8s.h"
#include "uart.h"
#include "stm8s_clk.h"
#include "stm8s_uart1.h"

static data_buffer_type received_buf,trans_buf ;


/**
 * @description: ��������
 * @param buf ��������ַ current_pos ��ǰ��������ݵ�λ�� 
 * @return {type} 
 */
void align_buffer(data_buffer_type *buffer);

/**
 * @description: ��ʼ������
 * @param baud:������
 * mode:UART1_MODE_RX_ENABLE  
 *      UART1_MODE_TX_ENABLE  
 *      UART1_MODE_TX_DISABLE 
 *      UART1_MODE_RX_DISABLE
 *      UART1_MODE_TXRX_ENABLE 
 * @ע��:����Ĳ����������� stm8s_uart1.h,����ʹ������������ļ������������ͷ�ļ�   
 * @return 
 */
void init_uart(uint16_t band, UART1_Mode_TypeDef mode)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART1 , ENABLE) ; 
    UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO, \
        UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
    UART1_Cmd(ENABLE) ;

    //��ʼ��������
    received_buf.size = 0 ;
    received_buf.current_pos = received_buf.buffer;
    trans_buf.size = 0;
    trans_buf.current_pos = trans_buf.buffer;
}

/**
 * @description: ��������
 * @param buf ��������ַ current_pos ��ǰ��������ݵ�λ�� 
 * @return {type} 
 */
void align_buffer(data_buffer_type *buffer)
{
    char *pos ;
    uint8_t i ;
    pos = (*buffer).buffer;
    i = (*buffer).current_pos - pos;    //�����Ѿ������˶��ٸ�����
    i = (*buffer).size - i;// ���㻹�ж��ٸ�û�б�����
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
 * @description: ����n���ֽڵ�����������
 * @param buf:������ָ�� n ָ�����յ��ַ�����
 * @return  ���ض������ַ�����
 */
uint8_t uart_read(char *buf, uint8_t n)
{
  return 0;
}

/**
 * @description: ����һ���ַ���
 * @param buf �ַ���ָ�� n Ҫд�����������
 * @return д�뻺�������͵��ֽ���
 * ע��:�������ڻ���������ʱ��ᵼ�µȴ�,һֱ���������ݴ���bufferΪֹ
 */
uint8_t uart_write(char *buf, uint8_t n)
{
    char writed_count = 0;
    align_buffer(&trans_buf);
    while (n)
    {
        /* �жϻ������Ƿ��� */
        //��Ϊ�����±��Ǵ�0��ʼ��,���Ա����1
        if ((trans_buf.current_pos - trans_buf.buffer + trans_buf.size) <= UART_BUFFER_SIZE-1)
        {
            /* д�뻺���� */
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
 * @description: ���æ,������
 * @param {type} 
 * @return {type} 
 */
bool uart_busy()
{
  return FALSE ;
}

/**
 * @description: �������жϵ���
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
 * @description:�������жϵ���
 * @param {type} 
 * @return {type} 
 */
void uart_receive_handle()
{
    
}

/**
 * @description:ȡ�ý��յ����ַ�����
 * @param 
 * @return ���ؽ��ջ������ڽ��յ������ݵ�����
 */
uint8_t get_received_datas_count()
{
    return 0;
}
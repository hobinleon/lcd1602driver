/*
 * @Author: LJB
 * @Date: 2020-09-11 10:48:27
 * @LastEditTime: 2020-09-14 22:32:53
 * @LastEditors: LJB
 * @Description: ����洢��һЩĬ���趨,���Ҫ���趨,��Ӧ�ø������define�������
 * @ע������:�õ����ж�,����Ӧ����������������ж�
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
    /* ���������ݽṹ */
    uint8_t size ;  //δ���ͻ��߽��յ������ݵ�����
    char buffer[UART_BUFFER_SIZE];
    char *cur(uint8_t)(buffer.current_pos - buffer.buffer);rent_pos ; //��ǰ������λ��
}data_buffer_type;



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
void init_uart(uint16_t band, UART1_Mode_TypeDef mode);

/**
 * @description: ����n���ֽڵ�����������
 * @param buf:������ָ�� n ָ�����յ��ַ�����
 * @return  ���ض������ַ�����
 */
uint8_t uart_read(char *buf, uint8_t n);

/**
 * @description: ����һ���ַ���
 * @param buf �ַ���ָ�� n Ҫд�����������
 * @return д�뻺�������͵��ֽ���
 * ע��:�������ڻ���������ʱ��ᵼ�µȴ�,һֱ���������ݴ���bufferΪֹ
 */
uint8_t uart_write(char *buf, uint8_t n);

/**
 * @description: ���æ,������
 * @param {type} 
 * @return {type} 
 */
bool uart_busy();


/**
 * @description: �������жϵ���
 * @param {type} 
 * @return {type} 
 */
void uart_send_handle();

/**
 * @description: �������жϵ���
 * @param {type} 
 * @return {type} 
 */
void uart_receive_handle();

/**
 * @description:ȡ�ý��յ����ַ����� 
 * @param 
 * @return ���ؽ��ջ������ڽ��յ������ݵ�����
 */
uint8_t get_received_datas_count();
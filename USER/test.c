#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
#include "key.h"	 	 
#include "exti.h"	 	 
#include "wdg.h" 	 
#include "timer.h"		 	 	 
#include "lcd.h"
#include "usmart.h"	
#include "rtc.h"	 	 
#include "wkup.h"	
#include "dma.h" 	 
#include "24cxx.h" 	 
#include "flash.h" 	 
#include "touch.h" 	 
#include "malloc.h"
#include "string.h"
#include "mmc_sd.h"
#include "ff.h"
#include "exfuns.h"	    
#include "fontupd.h"
#include "text.h"		
#include "usart2.h"
#include "sim900a.h" 
//ALIENTEKս��STM32��������չʵ��5
//ATK-SIM900A GSM/GPRSģ�����ʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾ 

int main(void)
{
	u8 key,fontok=0; 
   	Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);			//��ʱ��ʼ��
	uart_init(72,115200); 	//����1��ʼ�� 
	LCD_Init();				//��ʼ��Һ�� 
	LED_Init();         	//LED��ʼ��	 
	KEY_Init();				//������ʼ��	 
	usmart_dev.init(72);	//usmart��ʼ��	
 	USART2_Init(36,115200);	//��ʼ������2 
	TP_Init();				//��ʼ��������
	mem_init(SRAMIN);		//��ʼ���ڲ��ڴ��	    
 	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
  	f_mount(0,fs[0]); 		//����SD�� 
	key=KEY_Scan(0);  
	if(key==KEY_RIGHT)		//ǿ��У׼
	{
		LCD_Clear(WHITE);	//����
		TP_Adjust();  		//��ĻУ׼ 
		TP_Save_Adjdata();	  
		LCD_Clear(WHITE);	//����
	}
	fontok=font_init();		//����ֿ��Ƿ�OK
	if(fontok||key==KEY_DOWN)//��Ҫ�����ֿ�				 
	{
		LCD_Clear(WHITE);		   	//����
 		POINT_COLOR=RED;			//��������Ϊ��ɫ	   	   	  
		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
		while(SD_Initialize())		//���SD��
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,0);//��SD������
		while(key)//����ʧ��		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//����	       
	}  
	sim900a_test();
}












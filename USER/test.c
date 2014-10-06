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
//ALIENTEK战舰STM32开发板扩展实验5
//ATK-SIM900A GSM/GPRS模块测试实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司 

int main(void)
{
	u8 key,fontok=0; 
   	Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);			//延时初始化
	uart_init(72,115200); 	//串口1初始化 
	LCD_Init();				//初始化液晶 
	LED_Init();         	//LED初始化	 
	KEY_Init();				//按键初始化	 
	usmart_dev.init(72);	//usmart初始化	
 	USART2_Init(36,115200);	//初始化串口2 
	TP_Init();				//初始化触摸屏
	mem_init(SRAMIN);		//初始化内部内存池	    
 	exfuns_init();			//为fatfs相关变量申请内存  
  	f_mount(0,fs[0]); 		//挂载SD卡 
	key=KEY_Scan(0);  
	if(key==KEY_RIGHT)		//强制校准
	{
		LCD_Clear(WHITE);	//清屏
		TP_Adjust();  		//屏幕校准 
		TP_Save_Adjdata();	  
		LCD_Clear(WHITE);	//清屏
	}
	fontok=font_init();		//检查字库是否OK
	if(fontok||key==KEY_DOWN)//需要更新字库				 
	{
		LCD_Clear(WHITE);		   	//清屏
 		POINT_COLOR=RED;			//设置字体为红色	   	   	  
		LCD_ShowString(60,50,200,16,16,"ALIENTEK STM32");
		while(SD_Initialize())		//检测SD卡
		{
			LCD_ShowString(60,70,200,16,16,"SD Card Failed!");
			delay_ms(200);
			LCD_Fill(60,70,200+60,70+16,WHITE);
			delay_ms(200);		    
		}								 						    
		LCD_ShowString(60,70,200,16,16,"SD Card OK");
		LCD_ShowString(60,90,200,16,16,"Font Updating...");
		key=update_font(20,110,16,0);//从SD卡更新
		while(key)//更新失败		
		{			 		  
			LCD_ShowString(60,110,200,16,16,"Font Update Failed!");
			delay_ms(200);
			LCD_Fill(20,110,200+20,110+16,WHITE);
			delay_ms(200);		       
		} 		  
		LCD_ShowString(60,110,200,16,16,"Font Update Success!");
		delay_ms(1500);	
		LCD_Clear(WHITE);//清屏	       
	}  
	sim900a_test();
}












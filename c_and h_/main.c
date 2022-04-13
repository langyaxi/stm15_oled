#include "all.h"



void main()
{
	P0M0=0;//配置为标准IO口
	P0M1=0;
	P1M0=0;//配置为标准IO口
	P1M1=0;
	P2M0=0;//配置为标准IO口
	P2M1=0;
	P3M0=0;//配置为标准IO口
	P3M1=0;
	P4M0=0;//配置为标准IO口 
	P4M1=0;
	P5M0=0;//配置为标准IO口
	P5M1=0;
	EA=1;
	
	IIC_Init();
//	Oled_Init();
	OLED_Init();
	while(1)
	{		
//		Oled_display();
		OLED_Newpic_Show_Ser() ;
	}
}


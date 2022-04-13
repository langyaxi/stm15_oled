#include "all.h"
u8 xdata OLED_Write_pic_Buffer[8][128];//二维数组   8页   每页128个字节

void OLED_Write_Reg(u8 IIC_Command)
{
	IIC_Start();
	IIC_Write_Byte(0x78);// 设备识别码
	IIC_Read_Ack();//检测来自从机的应答
	IIC_Write_Byte(0x00);// 控制字节   下一位数据为命令
	IIC_Read_Ack();//检测来自从机的应答
	IIC_Write_Byte(IIC_Command);// 写命令
	IIC_Read_Ack();//检测来自从机的应答
	IIC_Stop();
}

void OLED_Write_pic_Data(u8 PAGE )  //将数组的1页（182个字节）写入oled
{
	u8 i;
	OLED_Write_Reg(0xb0+PAGE);
	OLED_Write_Reg(0x00);        //列低字节起始地址
	OLED_Write_Reg(0x10);        //列高字节起始地址

	IIC_Start();
	IIC_Write_Byte(0x78);// 设备识别码
	IIC_Read_Ack();//检测来自从机的应答
	IIC_Write_Byte(0x40);// 控制字节   下一位数据为数据
	IIC_Read_Ack();//检测来自从机的应答
	for(i=0;i<128;i++)
	{
		IIC_Write_Byte(OLED_Write_pic_Buffer[PAGE][i]);// 写数据
		IIC_Read_Ack();//检测来自从机的应答
	}		
	IIC_Stop();
}
void OLED_XRAM_Delete()   //单片机的数据缓存清空
{
	u16 i;
	u8 *P;
	P=&OLED_Write_pic_Buffer[0][0];
	for(i=0;i<1024;i++)
	{
		(* P)=0;
		P++;
	}
}
void OLED_Delete()         //OLED清屏
{
	u8 i,k;
	for(i=0;i<8;i++)
	{				
			OLED_Write_Reg(0xb0+i);      //起始页
			OLED_Write_Reg(0x00);        //列低字节起始地址
//			OLED_Write_Reg(0x1b);        //列高字节起始地址

			IIC_Start();
			IIC_Write_Byte(0x78);// 设备识别码
			IIC_Read_Ack();//检测来自从机的应答
			IIC_Write_Byte(0x40);// 控制字节   下一位数据为数据
			IIC_Read_Ack();//检测来自从机的应答
			for(k=0;k<128;k++)
			{
				IIC_Write_Byte(0);// 写数据
				IIC_Read_Ack();//检测来自从机的应答
			}		
			IIC_Stop();
		}
}

void OLED_Newpic_Show_Ser()        //将全部缓存数据发送到oled
{
	static xdata u8 count=0;
	static xdata u8 PAGE=0;       //静态变量会记住改变以后的值
	switch(count)
	{
		case 10:OLED_Write_pic_Data(PAGE);break;
		case 20:OLED_Write_pic_Data(PAGE);break;
		case 30:OLED_Write_pic_Data(PAGE);break;
		case 40:OLED_Write_pic_Data(PAGE);break;
		case 50:OLED_Write_pic_Data(PAGE);break;
		case 60:OLED_Write_pic_Data(PAGE);break;
		case 70:OLED_Write_pic_Data(PAGE);break;
		case 80:
		{
			OLED_Write_pic_Data(PAGE);
			PAGE++;
		 	PAGE=PAGE%8;
			count=0;
		}
		break;
	}
	count++;
}
void OLED_Show_Picture_Ser(u8 PAGE,u8 dat1)//显示图片    将图片数据放入缓存数组中
{
	u8 i;
	for(i=0;i<128;i++)      //
	{
		OLED_Write_pic_Buffer[PAGE][i]=Picture[dat1][i];		
	}

}
void OLED_Init()
{
	
	OLED_XRAM_Delete();//缓存数组清零  跟oled没有直接关系  这些都放在单片机的外部RAM中   

	OLED_Show_Picture_Ser(0,0);
	OLED_Show_Picture_Ser(1,1);
	OLED_Show_Picture_Ser(2,2);
	OLED_Show_Picture_Ser(3,3);
	OLED_Show_Picture_Ser(4,4);
	OLED_Show_Picture_Ser(5,5);
	OLED_Show_Picture_Ser(6,6);
	OLED_Show_Picture_Ser(7,7);
		
	OLED_Write_Reg(0x81);//设置对比度
	OLED_Write_Reg(0xff);//全亮
	
	OLED_Write_Reg(0xa4);//上电自动显示RAM中的图像
	OLED_Write_Reg(0xa6);//黑底白字 
	OLED_Write_Reg(0xaf);//显示开
	OLED_Write_Reg(0x40);//不进行卷屏   起始行
	OLED_Write_Reg(0xa1);//左右镜像
	OLED_Write_Reg(0xc8);//上下镜像 
	
	OLED_Write_Reg(0xa8);//设置重复率  （没看懂） 
	OLED_Write_Reg(0x3f);

	OLED_Write_Reg(0xd3);//不进行滚屏   不偏移
	OLED_Write_Reg(0x00);
	
	OLED_Write_Reg(0xd5);//  下面都与刷新频率有关
	OLED_Write_Reg(0x00); 
	
	OLED_Write_Reg(0xd9);
	OLED_Write_Reg(0x22);
	
	OLED_Write_Reg(0xdb);
	OLED_Write_Reg(0x20);
 	OLED_Write_Reg(0x8d);
	OLED_Write_Reg(0x14);//与刷新频率有关

	OLED_Write_Reg(0x20);//设置显示方式  
	OLED_Write_Reg(0x02);//页寻址
	
	OLED_Delete();     //擦除
	
}
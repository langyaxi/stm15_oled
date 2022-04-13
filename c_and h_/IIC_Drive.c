#include "all.h"
void IIC_Init()
{
	IIC_SCL=1;
	IIC_SDA=1;
}
void IIC_Delay()
{
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}
void IIC_Start()//
{
	IIC_SCL=1;
	IIC_SDA=1;
	IIC_Delay();
	IIC_SDA=0;
//	IIC_SCL=0;
	IIC_Delay();
}
void IIC_Stop()//
{	
	IIC_SDA=0;
	IIC_SCL=1;
	IIC_Delay();
	IIC_SDA=1;
	IIC_Delay();
}
void IIC_Write_Byte(u8 IIC_Byte)  //д�ֽ�
{
	u8 idata i;
	IIC_SCL=0;
	IIC_SDA=1;
	for(i=0;i<8;i++)
	{
		IIC_SDA=(bit)(IIC_Byte&0x80);  //ȡ���λ
		IIC_Byte<<=1;
		IIC_SCL=1;
		IIC_Delay();
		IIC_SCL=0;
		IIC_Delay();
	}
	 IIC_SDA=1;
}
u8 IIC_Read_Byte()   //���ֽ�
{
	u8 idata i,value;
	for(i=0;i<8;i++)
	{
		value<<=1;
		value|=IIC_SDA;
		IIC_SCL=1;
		IIC_Delay();
		IIC_SCL=0;
		IIC_Delay();
	}
//	IIC_SDA=1;
	return value;
}

u8 IIC_Read_Ack()//  ������Դӻ���Ӧ��
{
	u8 idata i,ack=1;
	IIC_SCL=1;
	IIC_Delay();
	while((ack)&&(i<5))
	{
		i++;
		ack=IIC_SDA;
	}
	IIC_SCL=0;
	return ack;
}
void IIC_Write_Ack(bit ack)  //mcu����Ӧ��
{
	IIC_SDA=ack;
	IIC_SCL=1;
	IIC_Delay();
	IIC_SCL=0;
	IIC_SDA=1;
	IIC_Delay();
}
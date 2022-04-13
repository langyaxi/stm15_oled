#include "all.h"
u8 xdata OLED_Write_pic_Buffer[8][128];//��ά����   8ҳ   ÿҳ128���ֽ�

void OLED_Write_Reg(u8 IIC_Command)
{
	IIC_Start();
	IIC_Write_Byte(0x78);// �豸ʶ����
	IIC_Read_Ack();//������Դӻ���Ӧ��
	IIC_Write_Byte(0x00);// �����ֽ�   ��һλ����Ϊ����
	IIC_Read_Ack();//������Դӻ���Ӧ��
	IIC_Write_Byte(IIC_Command);// д����
	IIC_Read_Ack();//������Դӻ���Ӧ��
	IIC_Stop();
}

void OLED_Write_pic_Data(u8 PAGE )  //�������1ҳ��182���ֽڣ�д��oled
{
	u8 i;
	OLED_Write_Reg(0xb0+PAGE);
	OLED_Write_Reg(0x00);        //�е��ֽ���ʼ��ַ
	OLED_Write_Reg(0x10);        //�и��ֽ���ʼ��ַ

	IIC_Start();
	IIC_Write_Byte(0x78);// �豸ʶ����
	IIC_Read_Ack();//������Դӻ���Ӧ��
	IIC_Write_Byte(0x40);// �����ֽ�   ��һλ����Ϊ����
	IIC_Read_Ack();//������Դӻ���Ӧ��
	for(i=0;i<128;i++)
	{
		IIC_Write_Byte(OLED_Write_pic_Buffer[PAGE][i]);// д����
		IIC_Read_Ack();//������Դӻ���Ӧ��
	}		
	IIC_Stop();
}
void OLED_XRAM_Delete()   //��Ƭ�������ݻ������
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
void OLED_Delete()         //OLED����
{
	u8 i,k;
	for(i=0;i<8;i++)
	{				
			OLED_Write_Reg(0xb0+i);      //��ʼҳ
			OLED_Write_Reg(0x00);        //�е��ֽ���ʼ��ַ
//			OLED_Write_Reg(0x1b);        //�и��ֽ���ʼ��ַ

			IIC_Start();
			IIC_Write_Byte(0x78);// �豸ʶ����
			IIC_Read_Ack();//������Դӻ���Ӧ��
			IIC_Write_Byte(0x40);// �����ֽ�   ��һλ����Ϊ����
			IIC_Read_Ack();//������Դӻ���Ӧ��
			for(k=0;k<128;k++)
			{
				IIC_Write_Byte(0);// д����
				IIC_Read_Ack();//������Դӻ���Ӧ��
			}		
			IIC_Stop();
		}
}

void OLED_Newpic_Show_Ser()        //��ȫ���������ݷ��͵�oled
{
	static xdata u8 count=0;
	static xdata u8 PAGE=0;       //��̬�������ס�ı��Ժ��ֵ
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
void OLED_Show_Picture_Ser(u8 PAGE,u8 dat1)//��ʾͼƬ    ��ͼƬ���ݷ��뻺��������
{
	u8 i;
	for(i=0;i<128;i++)      //
	{
		OLED_Write_pic_Buffer[PAGE][i]=Picture[dat1][i];		
	}

}
void OLED_Init()
{
	
	OLED_XRAM_Delete();//������������  ��oledû��ֱ�ӹ�ϵ  ��Щ�����ڵ�Ƭ�����ⲿRAM��   

	OLED_Show_Picture_Ser(0,0);
	OLED_Show_Picture_Ser(1,1);
	OLED_Show_Picture_Ser(2,2);
	OLED_Show_Picture_Ser(3,3);
	OLED_Show_Picture_Ser(4,4);
	OLED_Show_Picture_Ser(5,5);
	OLED_Show_Picture_Ser(6,6);
	OLED_Show_Picture_Ser(7,7);
		
	OLED_Write_Reg(0x81);//���öԱȶ�
	OLED_Write_Reg(0xff);//ȫ��
	
	OLED_Write_Reg(0xa4);//�ϵ��Զ���ʾRAM�е�ͼ��
	OLED_Write_Reg(0xa6);//�ڵװ��� 
	OLED_Write_Reg(0xaf);//��ʾ��
	OLED_Write_Reg(0x40);//�����о���   ��ʼ��
	OLED_Write_Reg(0xa1);//���Ҿ���
	OLED_Write_Reg(0xc8);//���¾��� 
	
	OLED_Write_Reg(0xa8);//�����ظ���  ��û������ 
	OLED_Write_Reg(0x3f);

	OLED_Write_Reg(0xd3);//�����й���   ��ƫ��
	OLED_Write_Reg(0x00);
	
	OLED_Write_Reg(0xd5);//  ���涼��ˢ��Ƶ���й�
	OLED_Write_Reg(0x00); 
	
	OLED_Write_Reg(0xd9);
	OLED_Write_Reg(0x22);
	
	OLED_Write_Reg(0xdb);
	OLED_Write_Reg(0x20);
 	OLED_Write_Reg(0x8d);
	OLED_Write_Reg(0x14);//��ˢ��Ƶ���й�

	OLED_Write_Reg(0x20);//������ʾ��ʽ  
	OLED_Write_Reg(0x02);//ҳѰַ
	
	OLED_Delete();     //����
	
}
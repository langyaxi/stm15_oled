#ifndef IIC_Drive
#define IIC_Drive

sbit IIC_SDA=P2^6;
sbit IIC_SCL=P2^7;
void IIC_Init();
void IIC_Start();
void IIC_Stop();
void IIC_Write_Byte(unsigned char IIC_Byte);
unsigned char IIC_Read_Byte();
unsigned char IIC_Read_Ack();
void IIC_Write_Ack(bit ack);
#endif 

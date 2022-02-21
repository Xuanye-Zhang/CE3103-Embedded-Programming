#include "mpu9250.h"
#include "sys.h"
#include "delay.h"  

int Deviation_Count;
short gyro[3], accel[3],magnet[3], sensors;
short Deviation_gyro[3],Original_gyro[3];    
 int Flag_Mpu6050;  
  
void Read_DMP(void)
{
	           
}


void MPU9250_task(void *pvParameters)
{
  u32 lastWakeTime = getSysTickCnt();
    while(1)
    {	
			vTaskDelayUntil(&lastWakeTime, F2T(RATE_100_HZ));	

		  	Deviation_Count++;
			memcpy(Deviation_gyro,gyro,sizeof(gyro));
	
			MPU_Get_Accelerometer(accel);	
			MPU_Get_Gyroscope(gyro);	
			MPU_Get_Magnetometer(magnet);		  
    }
}  


u8 MPU9250_Init(void)
{
    u8 res=0;
    IIC_Init();     
  MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X80);
  delay_ms(100);  
  MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X00);
	
  MPU_Set_Gyro_Fsr(1);					        	
	MPU_Set_Accel_Fsr(0);					       	 	
  MPU_Set_Rate(50);						       	 	

  MPU_Write_Byte(MPU9250_ADDR,MPU_INT_EN_REG,0X00);   
	MPU_Write_Byte(MPU9250_ADDR,MPU_USER_CTRL_REG,0X00);
	MPU_Write_Byte(MPU9250_ADDR,MPU_FIFO_EN_REG,0X00);	
	MPU_Write_Byte(MPU9250_ADDR,MPU_INTBP_CFG_REG,0X82);
    res=MPU_Read_Byte(MPU9250_ADDR,MPU_DEVICE_ID_REG);  
    if(res==MPU6500_ID) 
    {
       MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT1_REG,0X01);  	
       MPU_Write_Byte(MPU9250_ADDR,MPU_PWR_MGMT2_REG,0X00);  	
		MPU_Set_Rate(50);						       	
    }
	else return 1;
 
    res=MPU_Read_Byte(AK8963_ADDR,MAG_WIA);    			   
    if(res==AK8963_ID)
    {
        MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11);		
    }
	else return 1;

    return 0;
}


u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_GYRO_CFG_REG,fsr<<3); 
}


u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU9250_ADDR,MPU_ACCEL_CFG_REG,fsr<<3); 
}

u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU9250_ADDR,MPU_CFG_REG,data);
}

u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU9250_ADDR,MPU_SAMPLE_RATE_REG,data);	
 	return MPU_Set_LPF(rate/2);	
}


short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU9250_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=21+((double)raw)/333.87;  
    return temp*100;;
}

u8 MPU_Get_Gyroscope(short *gyro)
{
    u8 buf[6],res; 
	res=MPU_Read_Len(MPU9250_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		
		Original_gyro[0] =(((u16)buf[0]<<8)|buf[1]);  
		Original_gyro[1] =(((u16)buf[2]<<8)|buf[3]);  
		Original_gyro[2]= (((u16)buf[4]<<8)|buf[5]);			
			
	} 	
    return res;;
}

u8 MPU_Get_Accelerometer(short *accel)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU9250_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
{
		accel[0] =((u16)buf[0]<<8)|buf[1];  
		accel[1] =((u16)buf[2]<<8)|buf[3];  
		accel[2] =((u16)buf[4]<<8)|buf[5];
	} 	
    return res;
}

u8 MPU_Get_Magnetometer(short *magnet)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(AK8963_ADDR,MAG_XOUT_L,6,buf);
	if(res==0)
	{
		magnet[0]=((u16)buf[1]<<8)|buf[0];  
		magnet[1]=((u16)buf[3]<<8)|buf[2];  
		magnet[2]=((u16)buf[5]<<8)|buf[4];
	} 	
    MPU_Write_Byte(AK8963_ADDR,MAG_CNTL1,0X11); 
    return res;;
}

u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
    u8 i;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         
    IIC_Wait_Ack();             
    for(i=0;i<len;i++)
    {
        IIC_Send_Byte(buf[i]);  
        if(IIC_Wait_Ack())      
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_Stop();
    return 0;
} 

u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         
    IIC_Wait_Ack();             
	IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); 
    IIC_Wait_Ack();             
    while(len)
    {
        if(len==1)*buf=IIC_Read_Byte(0); 
		else *buf=IIC_Read_Byte(1);		 
		len--;
		buf++;  
    }
    IIC_Stop();                 
    return 0;       
}


u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data)
{
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Send_Byte(reg);         
    IIC_Wait_Ack();             
    IIC_Send_Byte(data);        
    if(IIC_Wait_Ack())          
    {
        IIC_Stop();
        return 1;
    }
    IIC_Stop();
    return 0;
}


u8 MPU_Read_Byte(u8 addr,u8 reg)
{
    u8 res;
    IIC_Start();
    IIC_Send_Byte((addr<<1)|0); 
    IIC_Wait_Ack();             
    IIC_Send_Byte(reg);         
    IIC_Wait_Ack();             
	  IIC_Start();                
    IIC_Send_Byte((addr<<1)|1); 
    IIC_Wait_Ack();             
    res=IIC_Read_Byte(0);		 
    IIC_Stop();                 
    return res;  
}


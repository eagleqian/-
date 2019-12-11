//=====================================================================
//�ļ����ƣ�i2c.c
//���ܸ�Ҫ��i2c�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2013-05-4   V2.1
//        2015-01-21   V3.0
//=====================================================================
#include  "i2c.h"

static const uint_8 data[]={300,0x14,150,0x54,100,0x1f,75,0x25,50,0x5f};
static void send_signal(uint_8 Signal,uint_8 I2C_No);
static uint_8 wait(uint_8 x,uint_8 I2C_No);
static I2C_MemMapPtr i2c_get_base_address(uint_8 I2C_No);

//=====================================================================
//�������ƣ�send_signal
//���ܸ�Ҫ��������Ҫ������ʼ��ֹͣ�ź�
//����˵���� I2C_No:ģ��ţ���ȡֵΪ0��1
//       Signal: 'S'(Start),������ʼ�ź�      'O'(Over),  ����ֹͣ�ź�
//�������أ���
//=====================================================================
void send_signal(uint_8 Signal,uint_8 I2C_No)
{
    //��ȡi2cģ���ַ
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    if(num==I2C0)
    {
        if (Signal  == 'S')
        {
              //i2c0_c����ģʽѡ��λMST��0��Ϊ1,���Բ�����ʼ�ź�
              BSET(I2C_C1_MST_SHIFT,I2C0_C1);
         }
         else if (Signal == 'O')
        {
              //����ģʽѡ��λMST��1��Ϊ0,���Բ���ֹͣ�ź�
        	 BCLR(I2C_C1_MST_SHIFT,I2C0_C1);
        }
    }
    else if(num==I2C1)
    {
         if (Signal == 'S')
         {
              //i2c0_c����ģʽѡ��λMST��0��Ϊ1,���Բ�����ʼ�ź�
        	 BSET(I2C_C1_MST_SHIFT,I2C1_C1);
          }
          else if (Signal == 'O')
         {
              //����ģʽѡ��λMST��1��Ϊ0,���Բ���ֹͣ�ź�
        	  BCLR(I2C_C1_MST_SHIFT,I2C1_C1);
          }
    }
}
//=====================================================================
//�������ƣ� wait
//���ܸ�Ҫ�� ��ʱ����,ѭ��������Ӧ���־λ,������ɱ�־λ,�ж�MCU
//          �Ƿ���յ�Ӧ���źŻ�һ���ֽ��Ƿ����������ϴ������
//����˵���� I2C_No:ģ���  ����ȡֵΪ0��1
//          x:x = 'A'(Ack),�ȴ�Ӧ��;x = 'T'(Transmission),�ȴ�һ���ֽ����ݴ������
//�������أ�  0:�յ�Ӧ���źŻ�һ���ֽڴ������;
//        1:δ�յ�Ӧ���źŻ�һ�� �ֽ�û������
//=====================================================================
uint_8 wait(uint_8 x,uint_8 I2C_No)
{
    uint_16 ErrTime, i;
    //��ȡi2cģ�����ַ
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    ErrTime = 255*10;            //�����ѯ��ʱʱ��
    for (i = 0;i < ErrTime;i++)
    {
         if (x == 'A')           //�ȴ�Ӧ���ź�
         {
              if(( I2C_S_REG(num)  & I2C_S_RXAK_MASK)==0)
                   return 0;      //������һ���ֽں�,�յ��˴ӻ���Ӧ���ź�
          }
         else if (x == 'T')      //�ȴ��������һ���ֽ��ź�
         {
             if ((I2C_S_REG(num) & I2C_S_IICIF_MASK) != 0)
             {
                  (I2C_S_REG(num) |=(0 | I2C_S_IICIF_MASK));  //��IICIF��־λ
                       return 0;       //�ɹ�������һ���ֽ�
              }
          }
     }
    if (i >= ErrTime)
         return 1;               //��ʱ,û���յ�Ӧ���źŻ�����һ���ֽ�
}

//=====================================================================
//�������ƣ�i2c_init                                                        
//���ܸ�Ҫ����ʼ��IICXģ�顣                                     
//����˵����I2C_No:ģ���,��ȡֵΪ0,1
//       Mode ģʽ  1������     0���ӻ�
//       address ��ģ���ʼ����ַ    ��Χ(1~255)
//       BaudRateΪ�����ʣ��䵥λΪKb/s����ȡֵΪ50,75,100,150,300
//�������أ���                                                                  
//=====================================================================
void i2c_init(uint_8 I2C_No,uint_8 Mode,uint_8 address,uint_8 BaudRate)
{
    //��ȡI2Cģ��Ļ�ַ
	uint_8 index;
    I2C_MemMapPtr num = i2c_get_base_address(I2C_No);
    if(I2C_No<0||I2C_No>1)//���ģ��Ŵ�����ǿ����Ϊ0
    {
    	I2C_No=0;
    }
    if(num==I2C0)
    {
        //I2C0 Clock Gate Control --enable
    	BSET(SIM_SCGC4_I2C0_SHIFT,SIM_SCGC4);
        I2C0_C1=0X00;
        BSET(I2C_S_IICIF_SHIFT,I2C0_S);

        //IIC_0��1=PTE24~25�ţ�2=PTB0~1�ţ�3=PTB2~3�ţ�4=PTC8~9��
		//���Ÿ���ΪIIC0����
        #if (IIC_0_GROUP == 1)
		PORTE_PCR24 = PORT_PCR_MUX(0x5);      //ʹ��IIC0_SCL
		PORTE_PCR25 = PORT_PCR_MUX(0x5);      //ʹ��IIC0_SDA
        #endif

		#if (IIC_0_GROUP == 2)
		PORTB_PCR0 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SCL
		PORTB_PCR1 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SDA
		#endif

		#if (IIC_0_GROUP == 3)
		PORTB_PCR2 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SCL
		PORTB_PCR3 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SDA
		#endif

		#if (IIC_0_GROUP == 4)
		PORTC_PCR8 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SCL
		PORTC_PCR9 = PORT_PCR_MUX(0x2);      //ʹ��IIC0_SDA
		#endif

        //���� MULT �� ICR,kL25��MCU����Ƶ��Ϊ24M���������Ϸ�Ƶ��75K������  
        I2C0_A1=address;                    //������Ϊ�ӻ�ʱ��Ĭ�ϵ�ַ
        for(index=0;index<10;index+=2)
        {
        	if(data[index]==BaudRate)
        	{
        		index++;
        		I2C0_F=data[index];        //������Ĳ�������I2C1_F
        		break;
        	}
        }

        if(1 == Mode)   //����ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C0_C1);//��i2c0ģ��ʹ��
            BSET(I2C_C1_TXAK_SHIFT,I2C0_C1); //��λi2c0 TXAK
        }
        else            //�ӻ�ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C0_C1);//ʹ��I2Cģ��
            BSET(I2C_C1_IICIE_SHIFT,I2C0_C1);//��I2C�ж�
            BSET(I2C_C1_MST_SHIFT,I2C0_C1);//���ó�����ģʽ
            BCLR(I2C_C1_TX_SHIFT,I2C0_C1);//TX = 0,MCU����Ϊ����ģʽ
//            i=I2C0_D;                        //����IIC1D,׼����������
            BCLR(I2C_C1_MST_SHIFT,I2C0_C1);//MSTλ��1���0������Ϊ�ӻ�ģʽ
        }

    }
    else
    {
        //I2C1 Clock Gate Control --enable
    	BSET(SIM_SCGC4_I2C1_SHIFT,SIM_SCGC4);
        //SIM_SCGC4 |=SIM_SCGC4_I2C1_MASK;
        I2C1_C1=0X00;
        BSET(I2C_S_IICIF_SHIFT,I2C1_S);

        //IIC_1: 1=PTE1~0�ţ�2=PTA3~4��, 3=PTC1~2��, 4=PTC10~11��
        //SD-FSL-KL25-EVB����ʹ��PTC1~2��
		#if (IIC_1_GROUP == 1)
		PORTE_PCR1 = PORT_PCR_MUX(0x6);      //ʹ��IIC1_SCL
		PORTE_PCR0 = PORT_PCR_MUX(0x6);      //ʹ��IIC1_SDA
		#endif

		#if (IIC_1_GROUP == 2)
		PORTA_PCR3 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SCL
		PORTA_PCR4 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SDA
		#endif

		#if (IIC_1_GROUP == 3)
		PORTC_PCR1 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SCL
		PORTC_PCR2 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SDA
		#endif

		#if (IIC_1_GROUP == 4)
		PORTC_PCR10 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SCL
		PORTC_PCR11 = PORT_PCR_MUX(0x2);      //ʹ��IIC1_SDA
		#endif

        I2C1_A1=address;                    //������Ϊ�ӻ�ʱ��Ĭ�ϵ�ַ
        for(index=0;index<10;index+=2)
        {
            if(data[index]==BaudRate)
            {
               index++;
               I2C1_F=data[index];        //������Ĳ�������I2C1_F
               break;
            }
        }

        if(1 == Mode)   //����ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C1_C1);//��i2c0ģ��ʹ��
            BSET(I2C_C1_TXAK_SHIFT,I2C1_C1); //��λi2c0 TXAK
        }
        else            //�ӻ�ģʽ
        {
            BSET(I2C_C1_IICEN_SHIFT,I2C1_C1);//ʹ��I2Cģ��
            BSET(I2C_C1_IICIE_SHIFT,I2C1_C1);//��I2C�ж�
            BSET(I2C_C1_MST_SHIFT,I2C1_C1);//���ó�����ģʽ
            BCLR(I2C_C1_TX_SHIFT,I2C1_C1);//TX = 0,MCU����Ϊ����ģʽ
//            i=I2C0_D;                        //����IIC1D,׼����������
            BCLR(I2C_C1_MST_SHIFT,I2C1_C1);//MSTλ��1���0������Ϊ�ӻ�ģʽ
        }
    }
}

//=====================================================================
//�������ƣ�i2c_read1                                                        
//���ܸ�Ҫ���Ӵӻ���1���ֽ�����                                            
//����˵����  I2C_No:ģ��ţ���ȡֵΪ0��1
//       DeviceAddr:�豸��ַ    ��Χ(1~255)
//       DataLocation:�����ڴӻ����������е�λ��    ��Χ(0~255)
//       Data:�����յ���һ���ֽ�����  
//�������أ�Ϊ0,�ɹ���һ���ֽ�;Ϊ1,��һ���ֽ�ʧ��  
//����˵��: �ڲ����� send_signal,wait  
//============================================================================
uint_8 i2c_read1(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 *Data)
{      
         //��ȡi2cģ���ַ
     I2C_MemMapPtr num = i2c_get_base_address(I2C_No);            
     BSET(I2C_C1_TX_SHIFT,I2C_C1_REG(num)); //TX = 1,MCU����Ϊ����ģʽ
     send_signal('S',I2C_No);               //���Ϳ�ʼ�ź� 
     I2C_D_REG(num)  = DeviceAddr & 0xfe;   //�����豸��ַ,��֪ͨ�ӻ���������
     if (wait('T',I2C_No))               //�ȴ�һ���ֽ����ݴ������  
     {      
          return 1;                          //û�д��ͳɹ�,��һ���ֽ�ʧ��   
     }
     if (wait('A',I2C_No))               //�ȴ��ӻ�Ӧ���ź� 
     {
          return 1;                          //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ�� 
     }
     I2C_D_REG(num)  = DataLocation;          //���������ڴӻ����������е�λ��
     if (wait('T',I2C_No))               //�ȴ�һ���ֽ����ݴ������ 
     {	 
          return 1;                          //û�д��ͳɹ�,��һ���ֽ�ʧ��
     }
     if (wait('A',I2C_No))               //�ȴ��ӻ�Ӧ���ź�   
     {  
          return 1;                          //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ��  
     }
     // ��MCU������ģ ʽ�£����λд1������һ�����¿�ʼ�ź�  
     BSET(I2C_C1_RSTA_SHIFT,I2C_C1_REG(num));
     I2C_D_REG(num) = DeviceAddr | 0x01;    //֪ͨ�ӻ���Ϊ��������    
     if (wait('T',I2C_No))               //�ȴ�һ���ֽ����ݴ������  
     { 
          return 1;                          //û�д��ͳɹ�,��һ���ֽ�ʧ�� 
     }
     if (wait('A',I2C_No))               //�ȴ��ӻ�Ӧ���ź�  
     {
          return 1;                         //û�еȵ�Ӧ���ź�,��һ���ֽ�ʧ��
     }
     BCLR(I2C_C1_TX_SHIFT,I2C_C1_REG(num));      //TX = 0,MCU����Ϊ����ģʽ (170216�ģ� 

  
     *Data = I2C_D_REG(num);            //����IIC1D,׼����������   
     if (wait('T',I2C_No))           //�ȴ�һ���ֽ����ݴ������  
     {  	 
          return 1;                      //û�д��ͳɹ�,��һ���ֽ�ʧ��  
     }
     send_signal('O',I2C_No);           //����ֹͣ�ź�    
     *Data = I2C_D_REG(num);            //�������յ���һ������    	
           return 0;                          //��ȷ���յ�һ���ֽ�����	
}

//============================================================================
//�������ƣ�i2c_write1                                                        
//���ܸ�Ҫ����ӻ�д1���ֽ�����                                           
//����˵����  I2C_No:ģ���       ����ȡֵΪ0��1
//       DeviceAddr:�豸��ַ    ��Χ(1~255)
//       DataLocation:�����ڴӻ����������е�λ��    ��Χ(0~255)
//       Data:Ҫ�����ӻ���1���ֽ�����  
//�������أ�Ϊ0,�ɹ�дһ���ֽ�;Ϊ1,дһ���ֽ�ʧ�� 
//����˵��: �ڲ����� send_signal,wait  
//============================================================================

uint_8 i2c_write1(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 Data)
{
	 //��ȡi2cģ���ַ
     I2C_MemMapPtr num = i2c_get_base_address(I2C_No);	
     BSET(I2C_C1_TX_SHIFT,I2C_C1_REG(num)); //TX = 1,MCU����Ϊ����ģʽ
     send_signal('S',I2C_No);          //���Ϳ�ʼ�ź�
     I2C_D_REG(num) = DeviceAddr & 0xfe;  //�����豸��ַ,��֪ͨ�ӻ���������
     if (wait('T',I2C_No))             //�ȴ�һ���ֽ����ݴ������
          return 1;                        //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))             //�ȴ��ӻ�Ӧ���ź�
          return 1;                        //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��   
     I2C_D_REG(num) = DataLocation;         //���������ڴӻ����������е�λ��
     if (wait('T',I2C_No))             //�ȴ�һ���ֽ����ݴ������
          return 1;                        //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))             //�ȴ��ӻ�Ӧ���ź�
          return 1;                        //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��   
     I2C_D_REG(num) = Data;               //д����
     if (wait('T',I2C_No))             //�ȴ�һ���ֽ����ݴ������
          return 1;                        //û�д��ͳɹ�,дһ���ֽ�ʧ��
     if (wait('A',I2C_No))             //�ȴ��ӻ�Ӧ���ź�
          return 1;                        //û�еȵ�Ӧ���ź�,дһ���ֽ�ʧ��   
     send_signal('O',I2C_No);          //����ֹͣ�ź�
          return 0;
}
//============================================================================
//�������ƣ� i2c_readn                                                        
//���ܸ�Ҫ�� �Ӵӻ���N���ֽ�����                                             
//����˵����  I2C_No:ģ���       ����ȡֵΪ0��1
//       DeviceAddr:�豸��ַ    ��Χ(1~255)
//       DataLocation:�����ڴӻ����������е�λ��    ��Χ(0~255)
//       Data:�������ݵĻ�����
//       N:�Ӵӻ������ֽڸ��� 
//�������أ� Ϊ0,�ɹ���N���ֽ�;Ϊ1,��N���ֽ�ʧ��  
//����˵��: �ڲ�����i2c_read1  
//============================================================================
uint_8 i2c_readn(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation, uint_8 Data[], uint_8 N)
{
    uint_16 i, j;
    for (i = 0;i < N;i++)
    {
        for(j = 0;j <15*40 ;j++); //��С��ʱ(���͵�ÿ���ֽ�֮��Ҫ��ʱ����)
        if (i2c_read1(I2C_No,DeviceAddr, DataLocation + i, &Data[i]))
             return 1;             //����һ���ֽ�û�н��յ�,����ʧ�ܱ�־:1
    }
    if (i >= N)
        return 0;                 //�ɹ�����N������,���سɹ���־:0
}


//============================================================================
//�������ƣ� i2c_writen                                                        
//���ܸ�Ҫ�� ��ӻ�дN���ֽ�����                                              
//����˵����  I2C_No:ģ���       ����ȡֵΪ0��1
//       DeviceAddr:�豸��ַ    ��Χ(1~255)
//       DataLocation:�����ڴӻ����������е�λ��    ��Χ(0~255)
//       Data:Ҫд������� ���׵�ַ
//       N:�Ӵӻ������ֽڸ��� 
//�������أ� Ϊ0,�ɹ�дN���ֽ�;Ϊ1,дN���ֽ�ʧ��
//����˵��: �ڲ�����i2c_write1   
//============================================================================
uint_8 i2c_writen(uint_8 I2C_No,uint_8 DeviceAddr, uint_8 DataLocation,uint_8 Data[], uint_8 N)
{
    uint_16 i, j;
    for (i = 0;i < N;i++)
    {
        for(j = 0;j < 15*40;j++); //��С��ʱ(���͵�ÿ���ֽ�֮��Ҫ��ʱ����)
        if (i2c_write1(I2C_No,DeviceAddr, DataLocation + i, Data[i]))
            return 1;            //����һ���ֽ�û�з��ͳ�ȥ,����ʧ�ܱ�־:1
    }
    if (i >= N)
        return 0;                //�ɹ�����N������,���سɹ���־:0
}
//==============================================================================
//�������ƣ�i2c_re_enable_int.
//����˵������i2c��IRQ�жϡ�
//����������i2cNO:i2cģ���      ����ȡֵΪ0��1
//�������أ��ޡ�
//==============================================================================
void i2c_enable_re_int(uint_8 I2C_No)
{
	 enable_irq (I2C_No+8);
}

//==============================================================================
//�������ƣ�i2c_re_disable_int.
//����˵�����ر�i2c��IRQ�жϡ�
//����������i2cNO:i2cģ���      ����ȡֵΪ0,1
//�������أ��ޡ�
//==============================================================================
void i2c_disable_re_int(uint_8 I2C_No)
{
	 disable_irq (I2C_No+8);
}

//============================================================================
//�������ƣ�i2c_get_base_address                                                        
//���ܸ�Ҫ����ȡi2cģ��Ļ�ַ                                                
//����˵����i2cNO:i2cģ���      ����ȡֵΪ0��1
//�������أ�i2cģ��Ļ�ֵַ                                                                  
//============================================================================
I2C_MemMapPtr i2c_get_base_address(uint_8 I2C_No)
{
        switch(I2C_No)
        {
            case 0:
                    return I2C0_BASE_PTR;
                      break;
            case 1:
                    return I2C1_BASE_PTR;
                       break;
	}
}





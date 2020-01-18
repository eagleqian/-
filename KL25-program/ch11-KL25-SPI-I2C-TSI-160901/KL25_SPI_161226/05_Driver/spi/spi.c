//=====================================================================
//�ļ����ƣ�SPI.c
//���ܸ�Ҫ��SPI�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧ��˼����Ƕ��ʽ����(sumcu.suda.edu.cn)
//���¼�¼��2016-03-17  V2.2
//        2016-05-11  V3.0
//=====================================================================
#include "spi.h"
//=====================================================================
//�������ƣ�SPI_init��
//����˵����SPI��ʼ��
//����������No��ģ��ţ�KL25оƬȡֵΪ0��1
//       MSTR��SPI���ӻ�ѡ��0ѡ��Ϊ�ӻ�,1ѡ��Ϊ������
//       BaudRate�������ʣ���ȡ12000��6000��4000��3000��1500��1000����λ��bps
//       CPOL��CPOL=0������ЧSPIʱ�ӣ�����Ч����CPOL=1������ЧSPIʱ�ӣ�����Ч��
//       CPHA��CPHA=0��λΪ0�� CPHA=1��λΪ1��
//�������أ���
//=====================================================================
void SPI_init(uint_8 No,uint_8 MSTR,uint_16 BaudRate,\
                                               uint_8 CPOL,uint_8 CPHA)
{
    uint_8 BaudRate_Mode;
    uint_8 BaudRate_High;
    uint_8 BaudRate_Low;
    if(No<0||No>1)   No=0;    //���SPI�Ų���������ǿ��ѡ�� 0��ģ��
    if(No==0)                 //��ʼ��SPI0����
    {
        BSET(SIM_SCGC4_SPI0_SHIFT,SIM_SCGC4);   //��SPI0ģ��ʱ�ӡ�
        //���Ÿ���ΪSPI0����
        #if (SPI_0_GROUP == 1)
        PORTD_PCR0=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD0��SS����
        PORTD_PCR1=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD1��SCK����
        PORTD_PCR2=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD2��MOSI����
        PORTD_PCR3=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD3��MIOS����
        #endif

        #if (SPI_0_GROUP == 2)
        PORTA_PCR14=(0|PORT_PCR_MUX(0x02));        //ѡ��PTA14��SS����
        PORTA_PCR15=(0|PORT_PCR_MUX(0x02));        //ѡ��PTA15��SCK����
        PORTA_PCR16=(0|PORT_PCR_MUX(0x02));        //ѡ��PTA16��MOSI����
        PORTA_PCR17=(0|PORT_PCR_MUX(0x02));        //ѡ��PTA17��MIOS����
        #endif

        #if (SPI_0_GROUP == 3)
        PORTC_PCR4=(0|PORT_PCR_MUX(0x02));        //ѡ��PTC4��SS����
        PORTC_PCR5=(0|PORT_PCR_MUX(0x02));        //ѡ��PTC5��SCK����
        PORTC_PCR6=(0|PORT_PCR_MUX(0x02));        //ѡ��PTC6��MOSI����
        PORTC_PCR7=(0|PORT_PCR_MUX(0x02));        //ѡ��PTC7��MIOS����
        #endif

        SPI0_C1=0x00;                           //SPI���ƼĴ���1����
        BSET(SPI_C1_SPE_SHIFT,SPI0_C1);         //ʹ��SPIģ��

        //MSTR=1Ϊ����ģʽ��
        //MSTR=0Ϊ�ӻ�ģʽ����MSTR��ʼֵΪ0��������ģ�
        (MSTR==1)?BSET(SPI_C1_MSTR_SHIFT,SPI0_C1):\
                       BSET(SPI_C1_SPIE_SHIFT,SPI0_C1);

        //ʱ�Ӽ������ã�CPOL=0��ƽʱʱ��Ϊ�ߵ�ƽ����֮CPOL=1��ƽʱʱ��Ϊ�͵�ƽ
        (0==CPOL)?BCLR(SPI_C1_CPOL_SHIFT,SPI0_C1):\
                        BSET(SPI_C1_CPOL_SHIFT,SPI0_C1);

        //ʱ����λCPHA
        (0 == CPHA)?BCLR(SPI_C1_CPHA_SHIFT,SPI0_C1):\
                              BSET(SPI_C1_CPHA_SHIFT,SPI0_C1);

        ////SSOEΪ1,MODFENΪ1�����ñ�ģ��Ϊ�Զ�SS���
        BSET(SPI_C1_SSOE_SHIFT,SPI0_C1);
        //��SPI0��C1�Ĵ�������Ϊ����ģʽ���ӻ�ѡ���Զ�ģʽ��ʹ��SPI0ģ�顣
        SPI0_C2=0x00;
        if(MSTR == 1 )  //����ģʽ
            BSET(SPI_C2_MODFEN_SHIFT,SPI0_C2);
        BSET(SPI_C1_SPIE_SHIFT,SPI0_C1);
        SPI0_BR = 0x00U;//�����ʼĴ�������
        //�������ò�����
        BaudRate_High=0;
        BaudRate_Low=0;
        BaudRate_Mode=12000/BaudRate;
        while(BaudRate_Mode % 2 == 0)
        {
            BaudRate_Mode=BaudRate_Mode/2;
            BaudRate_Low++;
        }
        BaudRate_High=--BaudRate_Mode;
        SPI0_BR=BaudRate_High<<4;//��ֵ����SPI0_BR��SPPR��D6D5D4λ
        SPI0_BR|=BaudRate_Low;//��ֵ��SPI0_BR��SPR�� D2D1D0λ

    }
     else         //��ʼ��SPI1����
    {
        BSET(SIM_SCGC4_SPI1_SHIFT,SIM_SCGC4);   //��SPI1ģ��ʱ�ӡ�
        //���Ÿ���ΪSPI1����
        #if (SPI_1_GROUP == 1)
        PORTE_PCR1=(0|PORT_PCR_MUX(0x02));        //ѡ��PTE1��MOSI����
        PORTE_PCR2=(0|PORT_PCR_MUX(0x02));        //ѡ��PTE2��SCK����
        PORTE_PCR3=(0|PORT_PCR_MUX(0x02));        //ѡ��PTE3��MIOS����
        PORTE_PCR4=(0|PORT_PCR_MUX(0x02));        //ѡ��PTE4��SS����
        #endif

        #if (SPI_1_GROUP == 2)
        PORTB_PCR10=(0|PORT_PCR_MUX(0x02));        //ѡ��PTB10��SS����
        PORTB_PCR11=(0|PORT_PCR_MUX(0x02));        //ѡ��PTB11��SCK����
        PORTB_PCR16=(0|PORT_PCR_MUX(0x02));        //ѡ��PTB16��MOSI����
        PORTB_PCR17=(0|PORT_PCR_MUX(0x02));        //ѡ��PTB17��MIOS����
        #endif

        #if (SPI_1_GROUP == 3)
        PORTD_PCR4=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD4��SS����
        PORTD_PCR5=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD5��SCK����
        PORTD_PCR6=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD6��MOSI����
        PORTD_PCR7=(0|PORT_PCR_MUX(0x02));        //ѡ��PTD7��MIOS����
        #endif

        SPI1_C1=0x00;                     //SPI���ƼĴ���1����
        BSET(SPI_C1_SPE_SHIFT,SPI1_C1);   //ʹ��SPIģ��
        //MSTR=1Ϊ����ģʽ��
        //MSTR=0Ϊ�ӻ�ģʽ����MSTR��ʼֵΪ0��������ģ�
        (MSTR==1)?BSET(SPI_C1_MSTR_SHIFT,SPI1_C1):\
                                            BSET(SPI_C1_SPIE_SHIFT,SPI1_C1);

        //ʱ�Ӽ������ã�CPOL=0��ƽʱʱ��Ϊ�ߵ�ƽ����֮CPOL=1��ƽʱʱ��Ϊ�͵�ƽ
        (0 == CPOL)?BCLR(SPI_C1_CPOL_SHIFT,SPI1_C1):\
                                            BSET(SPI_C1_CPOL_SHIFT,SPI1_C1);

        //CPHA=0ʱ���źŵĵ�һ�����س�����8�������ݴ���ĵ�һ�����ڵ����룻
        //CPHA=1ʱ���źŵĵ�һ�����س�����8�������ݴ���ĵ�һ�����ڵ���㡣
        (0 == CPHA)?BCLR(SPI_C1_CPHA_SHIFT,SPI1_C1): \
                                            BSET(SPI_C1_CPHA_SHIFT,SPI1_C1);

        BSET(SPI_C1_SSOE_SHIFT,SPI1_C1);//SSOEΪ1,MODFENΪ1�����ñ�ģ��Ϊ�Զ�SS���
        //��SPI0��C1�Ĵ�������Ϊ����ģʽ���ӻ�ѡ���Զ�ģʽ��ʹ��SPI0ģ�顣

//        BSET(SPI_C1_SPIE_SHIFT,SPI1_C1);  //����ģ���SPI�ж�
        SPI1_C2 = 0x00U;
        if(MSTR == 1 )  //����ģʽ
            BSET(SPI_C2_MODFEN_SHIFT,SPI1_C2);
        SPI1_BR = 0x00U;
        //�������ò�����
        BaudRate_High=0;
        BaudRate_Low=0;
        BaudRate_Mode=12000/BaudRate;   //ȡ�������ڼĴ��������ݼ���
        while(BaudRate_Mode % 2 == 0)
        {
            BaudRate_Mode=BaudRate_Mode/2;
            BaudRate_Low++;
        }
        BaudRate_High=--BaudRate_Mode;
        SPI1_BR=BaudRate_High<<4;//��ֵ����SPI0_BR��SPPR��D6D5D4λ
        SPI1_BR|=BaudRate_Low;//��ֵ��SPI0_BR��SPR�� D2D1D0λ
    }      
}

//=====================================================================
//�������ƣ�SPI_send1.
//����˵����SPI����һ�ֽ����ݡ�
//����������No��ģ��š� ��ȡֵΪ0��1
//       data��     ��Ҫ���͵�һ�ֽ����ݡ�
//�������أ�0������ʧ�ܣ�1�����ͳɹ���
//=====================================================================
uint_8 SPI_send1(uint_8 No,uint_8 data)
{
    uint_32 i;
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    while(!(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK));//�ȴ����ͻ���������
        SPI_D_REG(baseadd)=data;//���ݼĴ�����������
    for(i=0;i<0xFFF0;i++)        //��һ��ʱ���ڷ��Ͳ�����ɣ�����Ϊ����ʧ�ܡ�
    {
        if(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK)//�жϷ��ͻ������Ƿ�ӵ�����
        {
            return(1);
        }
     }
    return(0);
}

//=====================================================================
//�������ƣ�SPI_sendN.
//����˵����SPI�������ݡ�
//����������No��ģ��š� ��ȡֵΪ0��1
//       n:     Ҫ���͵��ֽڸ�������ΧΪ(1~255)
//       data[]:����������׵�ַ��
//�������أ��ޡ�
//=====================================================================
void SPI_sendN(uint_8 No,uint_8 n,uint_8 data[])
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    uint_32 k;
    for(k=0;k<n;k++)
    {
        //״̬�Ĵ�����SPTEFλ����
        while(!(SPI_S_REG(baseadd)&SPI_S_SPTEF_MASK));
        SPI_D_REG(baseadd)=data[k];
           SPI_S_REG(baseadd) !=  SPI_S_SPTEF_MASK;    //���SPTEFλ
    }
}

//=====================================================================
//�������ƣ�SPI_receive1.
//����˵����SPI����һ���ֽڵ�����
//����������No��ģ��š� ��ȡֵΪ0��1
//�������أ����յ������ݡ�
//=====================================================================
uint_8 SPI_receive1(uint_8 No)
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    while(!(SPI_S_REG(baseadd)& SPI_S_SPRF_MASK));    //���SPI�Ƿ��յ������ݡ�
        return SPI_D_REG(baseadd);
}

//=====================================================================
//�������ƣ�SPI_receiveN.
//����˵����SPI�������ݡ���n=1ʱ�����ǽ���һ���ֽڵ����ݡ���
//����������No��ģ��š� ��ȡֵΪ0��1
//          n:    Ҫ���͵��ֽڸ�������ΧΪ(1~255),
//       data[]:���յ������ݴ�ŵ��׵�ַ��
//�������أ�1�����ճɹ�,���������ʧ�ܡ�
//=====================================================================
uint_8 SPI_receiveN(uint_8 No,uint_8 n,uint_8 data[])
{
    SPI_MemMapPtr baseadd=SPI_baseadd(No);
    uint_32 m=0;
    while(m<n)
    {
        if(SPI_S_REG(baseadd)&SPI_S_SPRF_MASK)
        {
             data[m]=SPI_D_REG(baseadd);
                 m++;
        }
    }
    return(1);
}

//=====================================================================
//�������ƣ�SPI_read1.
//����˵����SPI��������һ���ֽڵ����ݣ�
//����������No��ģ��š� ��ȡֵΪ0��1
//�������أ����յ������ݡ�
//=====================================================================
uint_8 SPI_read1(uint_8 No)
{
	SPI_MemMapPtr baseadd=SPI_baseadd(No);
	uint_16 flag=0;
	while(!(SPI_S_REG(baseadd)& SPI_S_SPRF_MASK)&&flag<5)
    {
 	   SPI_send1(No,'0');
 	   flag++;
    }
	if(SPI_S_REG(SPI_baseadd(SPI_0))&SPI_S_SPRF_MASK)	//���������ջ��������������յ����ݣ����򷵻�����
		return SPI_D_REG(baseadd);
	else return 0;
}

//=====================================================================
//�������ƣ�SPI_enable_re_int
//����˵������SPI�����жϡ�
//����������No��ģ��š� ��ȡֵΪ0��1��
//�������أ��ޡ�
//=====================================================================
void SPI_enable_re_int(uint_8 No)
{
    enable_irq (No+10);
}

//=====================================================================
//�������ƣ�SPI_disable_re_int
//����˵�����ر�SPI�����жϡ�
//����������No��ģ��š� ��ȡֵΪ0��1��
//�������أ��ޡ�
//=====================================================================
void SPI_disable_re_int(uint_8 No)
{
    disable_irq (No+10);
}


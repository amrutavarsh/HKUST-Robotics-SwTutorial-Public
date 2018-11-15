/*	
 *	Camera library - internal 2017/18
 *	Mode 		: ov7725
 *  Author  : Emmett Yim
 *  Contact : yhyim@ust.hk 
 *						66816823
 *	Lib			: ov7725define.h
 */
 
#ifndef __OV7725DEFINE_H
#define __OV7725DEFINE_H

#include "stm32f10x.h"
#include "pwm.h"

//ov7725 address define
#define OV7725ADR 0x42

//ov7725 product id
#define OV7725ID_PID 0x77
#define OV7725ID_VER 0x21

//SCCB
#define SCCB_TIM TIM6
#define SCCB_PSC 2500
#define SCCB_SCL &PB8
#define SCL_H         (GPIOB->BSRR = GPIO_Pin_8)
#define SCL_L         (GPIOB->BRR = GPIO_Pin_8)
#define SCL_read      (GPIOB->IDR & GPIO_Pin_8)
#define SCCB_SDA &PB9
#define SDA_H         (GPIOB->BSRR = GPIO_Pin_9)
#define SDA_L         (GPIOB->BRR = GPIO_Pin_9)
#define SDA_read      (GPIOB->IDR & GPIO_Pin_9)


//ov7725 fifo
#define FIFO_OE &PC4
#define FIFO_OE_H()     GPIOC->BSRR =GPIO_Pin_12
#define FIFO_OE_L()     GPIOC->BRR  =GPIO_Pin_12

#define FIFO_RRST &PC5
#define FIFO_RRST_H()   GPIOC->BSRR =GPIO_Pin_5
#define FIFO_RRST_L()   GPIOC->BRR  =GPIO_Pin_5

#define FIFO_RCLK &PA11
#define FIFO_RCLK_H()   GPIOA->BSRR =GPIO_Pin_11
#define FIFO_RCLK_L()   GPIOA->BRR  =GPIO_Pin_11

#define FIFO_WRST &PD2
#define FIFO_WRST_H()   GPIOD->BSRR =GPIO_Pin_2
#define FIFO_WRST_L()   GPIOD->BRR  =GPIO_Pin_2

#define FIFO_WEN &PA12
#define FIFO_WEN_H()     GPIOA->BSRR =GPIO_Pin_12
#define FIFO_WEN_L()     GPIOA->BRR  =GPIO_Pin_12
#define FIFO_DPORT GPIOB
#define FIFO_DMASK 0xFF
#define FIFO_VSYNC &PC12
//	VSYNC - PC4
//		EXTI&NVIC
//	Data - Capture data
#define FIFO_READY	                {\
	                                  FIFO_RRST_L();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
	                                  FIFO_RRST_H();\
	                                  FIFO_RCLK_L();\
	                                  FIFO_RCLK_H();\
	                                  FIFO_RCLK_L();\
                                    }

#define _1_LOOP_UNROLLING(X) {X;X;X;X}
#define _2_LOOP_UNROLLING(X) {_1_LOOP_UNROLLING(X);_1_LOOP_UNROLLING(X);_1_LOOP_UNROLLING(X);_1_LOOP_UNROLLING(X)}
#define _25_LOOP_UNROLLING(X) {_2_LOOP_UNROLLING(X);_2_LOOP_UNROLLING(X);}
#define _3_LOOP_UNROLLING(X) {_2_LOOP_UNROLLING(X);_2_LOOP_UNROLLING(X);_2_LOOP_UNROLLING(X);_2_LOOP_UNROLLING(X)}
#define _4_LOOP_UNROLLING(X) {_3_LOOP_UNROLLING(X);_3_LOOP_UNROLLING(X);_3_LOOP_UNROLLING(X)}
#define _5_LOOP_UNROLLING(X) {_4_LOOP_UNROLLING(X);_4_LOOP_UNROLLING(X);_4_LOOP_UNROLLING(X);_4_LOOP_UNROLLING(X);_4_LOOP_UNROLLING(X)}

#define __SKIP_PIXEL { \
											FIFO_RCLK_H();\
											FIFO_RCLK_L();\
											FIFO_RCLK_H();\
											FIFO_RCLK_L();\
};
	

#define __READ_FIFO_COLOUR(RGB565)  {\
										*RGB565 = (((FIFO_DPORT->IDR) & FIFO_DMASK) << 8);\
										FIFO_RCLK_H();\
										FIFO_RCLK_L();\
										*RGB565 |= ((FIFO_DPORT->IDR) & FIFO_DMASK);\
										FIFO_RCLK_H();\
										FIFO_RCLK_L();\
										RGB565++;\
									};

#define READ_FIFO_COLOUR(RGB565) _3_LOOP_UNROLLING(__READ_FIFO_COLOUR(RGB565))

#define __COPY_PX_COLOUR(RGB565, PRINT) {PRINT = rotate(RGB565);};
#define COPY_PX_COLOUR(RGB565, PRINT) _3_LOOP_UNROLLING(__COPY_PX_COLOUR(RGB565, PRINT))

#define __READ_FIFO_GREYSCALE(GREY)		{\
											GREY = ((FIFO_DPORT->IDR & FIFO_DMASK));\
											__SKIP_PIXEL; \
											__SKIP_PIXEL; \
											__SKIP_PIXEL; \
											__SKIP_PIXEL; \
										}

#define READ_FIFO_GREYSCALE(GREY) _4_LOOP_UNROLLING(__READ_FIFO_GREYSCALE(GREY))

#define __COPY_PX_GREYSCALE(GREY, PRINT) {PRINT = grey_to_rgb565_r(GREY);}
#define COPY_PX_GREYSCALE(GREY, PRINT) _25_LOOP_UNROLLING(__COPY_PX_GREYSCALE(GREY, PRINT))


//	ov7725 register address definition
#define GAIN      0x00
	#if 0
	#define BLUE      0x01
	#define RED       0x02
	#define RED       0x02
	#define GREEN     0x03
	#endif
#define BAVG      0x05
#define GAVG      0x06
#define RAVG      0x07
#define AECH      0x08
#define COM2      0x09
#define PID       0x0A
#define VER       0x0B
#define COM3_     0x0C
#define COM4      0x0D
#define COM5      0x0E
#define COM6      0x0F
#define AEC       0x10
#define CLKRC     0x11
#define COM7      0x12
#define COM8      0x13
#define COM9      0x14
#define COM10     0x15
#define REG16     0x16
#define HSTART    0x17
#define HSIZE     0x18
#define VSTRT     0x19
#define VSIZE     0x1A
#define PSHFT     0x1B
#define MIDH      0x1C
#define MIDL      0x1D
#define LAEC      0x1F
#define COM11     0x20
#define BDBase    0x22
#define BDMStep   0x23
#define AEW       0x24
#define AEB       0x25
#define VPT       0x26
#define REG28     0x28
#define HOutSize  0x29
#define EXHCH     0x2A
#define EXHCL     0x2B
#define VOutSize  0x2C
#define ADVFL     0x2D
#define ADVFH     0x2E
#define YAVE      0x2F
#define LumHTh    0x30
#define LumLTh    0x31
#define HREF      0x32
#define DM_LNL    0x33
#define DM_LNH    0x34
#define ADoff_B   0x35
#define ADoff_R   0x36
#define ADoff_Gb  0x37
#define ADoff_Gr  0x38
#define Off_B     0x39
#define Off_R     0x3A
#define Off_Gb    0x3B
#define Off_Gr    0x3C
#define COM12     0x3D
#define COM13     0x3E
#define COM14     0x3F
#define COM16     0x41
#define TGT_B     0x42
#define TGT_R     0x43
#define TGT_Gb    0x44
#define TGT_Gr    0x45
#define LC_CTR    0x46
#define LC_XC     0x47
#define LC_YC     0x48
#define LC_COEF   0x49
#define LC_RADI   0x4A
#define LC_COEFB  0x4B 
#define LC_COEFR  0x4C
#define FixGain   0x4D
#define AREF1     0x4F
#define AREF6     0x54
#define UFix      0x60
#define VFix      0x61
#define AWBb_blk  0x62
#define AWB_Ctrl0 0x63
#define DSP_Ctrl1 0x64
#define DSP_Ctrl2 0x65
#define DSP_Ctrl3 0x66
#define DSP_Ctrl4 0x67
#define AWB_bias  0x68
#define AWBCtrl1  0x69
#define AWBCtrl2  0x6A
#define AWBCtrl3  0x6B
#define AWBCtrl4  0x6C
#define AWBCtrl5  0x6D
#define AWBCtrl6  0x6E
#define AWBCtrl7  0x6F
#define AWBCtrl8  0x70
#define AWBCtrl9  0x71
#define AWBCtrl10 0x72
#define AWBCtrl11 0x73
#define AWBCtrl12 0x74
#define AWBCtrl13 0x75
#define AWBCtrl14 0x76
#define AWBCtrl15 0x77
#define AWBCtrl16 0x78
#define AWBCtrl17 0x79
#define AWBCtrl18 0x7A
#define AWBCtrl19 0x7B
#define AWBCtrl20 0x7C
#define AWBCtrl21 0x7D 
#define GAM1      0x7E
#define GAM2      0x7F
#define GAM3      0x80
#define GAM4      0x81
#define GAM5      0x82
#define GAM6      0x83
#define GAM7      0x84
#define GAM8      0x85
#define GAM9      0x86
#define GAM10     0x87
#define GAM11     0x88
#define GAM12     0x89
#define GAM13     0x8A
#define GAM14     0x8B
#define GAM15     0x8C
#define SLOP      0x8D
#define DNSTh     0x8E
#define EDGE0     0x8F
#define EDGE1     0x90
#define DNSOff    0x91
#define EDGE2     0x92
#define EDGE3     0x93
#define MTX1      0x94
#define MTX2      0x95
#define MTX3      0x96
#define MTX4      0x97
#define MTX5      0x98
#define MTX6      0x99
#define MTX_Ctrl  0x9A
#define BRIGHT    0x9B
#define CNST      0x9C
#define UVADJ0    0x9E
#define UVADJ1    0x9F
#define SCAL0     0xA0
#define SCAL1     0xA1
#define SCAL2     0xA2
#define SDE       0xA6
#define USAT      0xA7
#define VSAT      0xA8
#define HUECOS    0xA9
#define HUESIN    0xAA
#define SIGN      0xAB
#define DSPAuto   0xAC
																			
//	register default value
typedef struct
{
	uint8_t address;
	uint8_t data;
}OV7725REG;

//register default
static OV7725REG cameraConfig[] =
{
	{CLKRC,         0x00},
	{COM7,          0x46},
	//default value for QVGA
	{HSTART,     0x3f},
	{HSIZE,      0x50},
	{VSTRT,      0x03},
	{VSIZE,      0x78},
	{HREF,       0x00},
	{HOutSize,   0x50},
	{VOutSize,   0x78},
	{EXHCH,      0x00},
	//tuned value for 80*60	
	/*{HSTART,        0x20},
	{HSIZE,         ImageWidth>>2},
	{VSTRT,         0x2f},
	{VSIZE,         ImageLength>>1},
	{HREF,         (ImageLength&0x01<<2)|(ImageWidth&0x03)},*/
	//{HOutSize,      ImageWidth>>2},
	//{VOutSize,      ImageLength>>1},
	//{EXHCH,        (ImageLength&0x01<<2)|(ImageWidth&0x03)},
	{TGT_B,         0x7f},
	{FixGain,       0x09},
	{AWB_Ctrl0,     0xe0},
	{DSP_Ctrl1,     0xff},
	{DSP_Ctrl2,     0x20},
	{DSP_Ctrl3,	    0x00},
	{DSP_Ctrl4,     0x00},
	{COM8,		    0xff},
	{COM4,		    0xC1},
	{COM6,		    0xc5},
	{COM9,		    0x21},
	{BDBase,	    0xFF},
	{BDMStep,	    0x01},
	{AEW,		    0x34},
	{AEB,		    0x3c},
	{VPT,		    0xa1},
	{EXHCL,		    0x00},
	{AWBCtrl3,      0xaa},
	{COM8,		    0xff},
	{AWBCtrl1,      0x5d},
	{EDGE1,		    0x0a},
	{DNSOff,	    0x01},
	{EDGE2,		    0x01},
	{EDGE3,		    0x01},
	{MTX1,		    0x5f},
	{MTX2,		    0x53},
	{MTX3,		    0x11},
	{MTX4,		    0x1a},
	{MTX5,		    0x3d},
	{MTX6,		    0x5a},
	{MTX_Ctrl,      0x1e},
	{BRIGHT,	    0x00},
	{CNST,		    0x25},
	{USAT,		    0x65},
	{VSAT,		    0x65},
	{UVADJ0,	    0x81},
	{SDE,		    0x06},
	{GAM1,		    0x0c},
	{GAM2,		    0x16},
	{GAM3,		    0x2a},
	{GAM4,		    0x4e},
	{GAM5,		    0x61},
	{GAM6,		    0x6f},
	{GAM7,		    0x7b},
	{GAM8,		    0x86},
	{GAM9,		    0x8e},
	{GAM10,		    0x97},
	{GAM11,		    0xa4},
	{GAM12,		    0xaf},
	{GAM13,		    0xc5},
	{GAM14,		    0xd7},
	{GAM15,		    0xe8},
	{SLOP,		    0x20},
	{HUECOS,	    0x80},
	{HUESIN,	    0x80},
	{DSPAuto,	    0xff},
	{DM_LNL,	    0x00},
	{BDBase,	    0x99},
	{BDMStep,	    0x03},
	{LC_RADI,	    0x00},
	{LC_COEF,	    0x13},
	{LC_XC,		    0x08},
	{LC_COEFB,      0x14},
	{LC_COEFR,      0x17},
	{LC_CTR,	    0x05},
	{COM3_,		    0xd0},
	{COM5,			0x00}, //F5
};

uint8_t cameraConfigLength = sizeof(cameraConfig)/sizeof(cameraConfig[0]);

uint8_t sccbWriteByte(uint16_t address,uint8_t data);
uint8_t sccbReadByte(uint8_t* buffer, uint16_t length, uint8_t address);

//sccb
uint8_t cameraSccbInit()
{
	tim_rcc_init(SCCB_TIM);
	SCCB_TIM->PSC = 0;
	SCCB_TIM->ARR = SCCB_PSC;
	SCCB_TIM->CNT = 0;
	gpio_init(SCCB_SCL, GPIO_Mode_Out_OD);
	gpio_init(SCCB_SDA, GPIO_Mode_Out_OD);
	
	//init config
	uint8_t ov7725ID = 0;
	if(!sccbWriteByte(COM7,0x80))
		return ERROR ;
	if(!sccbReadByte( &ov7725ID,1,PID))	
		return ERROR;
	if(ov7725ID != OV7725ID_PID)
		return ERROR;
	if(!sccbReadByte( &ov7725ID,1,VER))	
		return ERROR;
	if(ov7725ID != OV7725ID_VER)
		return ERROR;
	for(uint16_t i=0;i<cameraConfigLength;i++)
		if(!sccbWriteByte(cameraConfig[i].address,cameraConfig[i].data))
			return ERROR;
		//8bit greyscale - capture with image, recommended
		sccbWriteByte(COM7,0x40);
		//16bit greyscale - capture with colourImage
		//sccbWriteByte(SDE,0x26);
		//sccbWriteByte(UFix,0x80);
		//sccbWriteByte(VFix,0x80);
	
	return SUCCESS;
}

static void sccbDelay(void)
{	
	SCCB_TIM->CR1 |= TIM_CR1_CEN;
	SCCB_TIM->SR &= ~TIM_SR_UIF;
	SCCB_TIM->CNT = 0;
	while (!(SCCB_TIM->SR & TIM_SR_UIF));
	SCCB_TIM->CR1 &= ~TIM_CR1_CEN;
}

static uint8_t sccbStart(void)
{
	SDA_H;
	SCL_H;
	sccbDelay();
	if(!SDA_read)
	return DISABLE;
	SDA_L;
	sccbDelay();
	if(SDA_read) 
	return DISABLE;
	SDA_L;
	sccbDelay();
	return ENABLE;
}

static void sccbStop(void)
{
	SCL_L;
	sccbDelay();
	SDA_L;
	sccbDelay();
	SCL_H;
	sccbDelay();
	SDA_H;
	sccbDelay();
}

static void sccbAck(void)
{	
	SCL_L;
	sccbDelay();
	SDA_L;
	sccbDelay();
	SCL_H;
	sccbDelay();
	SCL_L;
	sccbDelay();
}

static void sccbNoAck(void)
{	
	SCL_L;
	sccbDelay();
	SDA_H;
	sccbDelay();
	SCL_H;
	sccbDelay();
	SCL_L;
	sccbDelay();
}

static uint8_t sccbWaitAck(void) 	
{
	SCL_L;
	sccbDelay();
	SDA_H;			
	sccbDelay();
	SCL_H;
	sccbDelay();
	if(SDA_read)
	{
      SCL_L;
      return DISABLE;
	}
	SCL_L;
	return ENABLE;
}

static void sccbSendByte(uint8_t SendByte) 
{
	uint8_t i = 8;
	while(i--)
	{
		SCL_L;
		sccbDelay();
		if(SendByte & 0x80)
			SDA_H;  
		else 
			SDA_L;   
		SendByte <<= 1;
		sccbDelay();
		SCL_H;
		sccbDelay();
	}
	SCL_L;
}

static uint8_t sccbReceiveByte(void)  
{ 
    uint8_t i = 8;
    uint8_t receiveByte = 0;
    SDA_H;				
    while(i--)
    {
      receiveByte <<= 1;      
      SCL_L;
      sccbDelay();
			SCL_H;
      sccbDelay();	
      if(SDA_read)
        receiveByte |= 0x01;
    }
    SCL_L;
    return receiveByte;
}

uint8_t sccbWriteByte(uint16_t address,uint8_t data)
{
	if(!sccbStart())
		return DISABLE;
	sccbSendByte(OV7725ADR);
	if(!sccbWaitAck())
	{
		sccbStop(); 
		return DISABLE;
	}
	sccbSendByte((uint8_t)(address & 0x00FF));     
	sccbWaitAck();	
	sccbSendByte(data);
	sccbWaitAck();   
	sccbStop(); 
	return ENABLE;
}

uint8_t sccbReadByte(uint8_t* buffer, uint16_t length, uint8_t address)
{
	if(!sccbStart())
		return DISABLE;
	sccbSendByte(OV7725ADR);
	if(!sccbWaitAck())
	{
		sccbStop(); 
		return DISABLE;
	}
	sccbSendByte(address);
	sccbWaitAck();
	sccbStop();
	if(!sccbStart())
		return DISABLE;
	sccbSendByte( OV7725ADR + 1 );
	if(!sccbWaitAck())
	{
		sccbStop(); 
		return DISABLE;
	}
	while(length)
	{
		*buffer = sccbReceiveByte();
		if(length == 1)
			sccbNoAck();
		else
			sccbAck(); 
		buffer++;
		length--;
	}
	sccbStop();
	return ENABLE;
}

#endif //__OV7725DEFINE_H


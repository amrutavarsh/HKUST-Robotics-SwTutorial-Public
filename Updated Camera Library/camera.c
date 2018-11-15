/*	
 *	Camera library - internal 2017/18
 *	Mode 		: ov7725
 *  Author  : Emmett Yim
 *  Contact : yhyim@ust.hk 
 *						66816823
 *	Lib			: camera.c
 */

#include "camera.h"
#include "pwm.h"
#include "stm32f10x_tim.h"
#include "rcc.h"
#include "ov7725define.h"

volatile uint8_t camState = 0;
uint8_t image[ImageLength][ImageWidth];
uint16_t imageToPrint[ImageLength][ImageWidth];

static DMA_InitTypeDef camera_printing_dma;

//ov7725
uint8_t camera_init() {	
	//sccb init
	if(!cameraSccbInit())
		return ERROR;

	//camera status init
	camState = 0;

	//fifo init
	gpio_init(FIFO_OE, GPIO_Mode_Out_PP);
	gpio_init(FIFO_RRST, GPIO_Mode_Out_PP);
	gpio_init(FIFO_WEN, GPIO_Mode_Out_PP);
	gpio_init(FIFO_WRST, GPIO_Mode_Out_PP);
	gpio_init(FIFO_RCLK, GPIO_Mode_Out_PP);
	gpio_init(FIFO_VSYNC, GPIO_Mode_IN_FLOATING);
	
	//		Data
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FIFO_DMASK;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(FIFO_DPORT, &GPIO_InitStructure);
	
	gpio_exti_init(FIFO_VSYNC, EXTI_Trigger_Falling);

	FIFO_OE_L();
	FIFO_WEN_H();

	dma_rcc_init(DMA1);

	//TFT DMA

	DMA_DeInit(DMA1_Channel5);
	camera_printing_dma.DMA_PeripheralBaseAddr = (u32) &TFT_SPI.periph->DR;
	camera_printing_dma.DMA_MemoryBaseAddr = (u32) &imageToPrint[0][0];
	camera_printing_dma.DMA_DIR = DMA_DIR_PeripheralDST;
	camera_printing_dma.DMA_BufferSize = ImageLength*ImageWidth*2;
	camera_printing_dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	camera_printing_dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
	camera_printing_dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	camera_printing_dma.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	camera_printing_dma.DMA_Mode = DMA_Mode_Normal;
	camera_printing_dma.DMA_Priority = DMA_Priority_High;
	camera_printing_dma.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5, &camera_printing_dma);

	SPI_I2S_DMACmd(TFT_SPI.periph, SPI_I2S_DMAReq_Tx, ENABLE);

	return SUCCESS;
}


uint8_t camera_ready() {
	return camState == 2;
}

__attribute__((always_inline))
#define skip_pixel(rclkh, rclkl, rclkp) { \
	*rclkh = rclkp; \
	*rclkl = rclkp; \
	*rclkh = rclkp; \
	*rclkl = rclkp; \
}

__attribute__((always_inline))
static inline u8 camera_receive_one(volatile u16* idr, volatile u16* rclkh, volatile u16* rclkl, u16 rclkp) {
	u16 t = *idr;
	skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 1
	skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 2
	skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 3
	skip_pixel(rclkh, rclkl, rclkp);
#endif
#endif
#endif
	return t;
}

__attribute__((always_inline))
static inline void skip_row(volatile u16* rclkh, volatile u16* rclkl, u16 rclkp) {
	u32 i = ImageWidth;
	while(i) {
		i--; \
		skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 1
		skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 2
		skip_pixel(rclkh, rclkl, rclkp);
#if OverSampling > 3
		skip_pixel(rclkh, rclkl, rclkp);
#endif
#endif
#endif
	}
}

__attribute__((always_inline))
static inline void camera_receive_row(u8* ptr, volatile u16* idr, volatile u16* rclkh, volatile u16* rclkl, u16 rclkp) {
	u8* end = ptr + ImageWidth;
	do {
			*ptr++ = camera_receive_one(idr, rclkh, rclkl, rclkp);\
			*ptr++ = camera_receive_one(idr, rclkh, rclkl, rclkp);\
			*ptr++ = camera_receive_one(idr, rclkh, rclkl, rclkp);\
			*ptr++ = camera_receive_one(idr, rclkh, rclkl, rclkp);
	} while(ptr != end);
}

uint8_t camera_receive_frame(void) {
	if(camState != 2)
		return ERROR;
	
	FIFO_READY;
	
		u8* ptr = &image[0][0];
		volatile u16* idr = (volatile u16*) &FIFO_DPORT->IDR;
		u8* end = ptr + (ImageLength*ImageWidth);
		
		volatile u16* rclkh = (volatile u16*) FIFO_RCLK.port->BSRR;
		volatile u16* rclkl = (volatile u16*) FIFO_RCLK.port->BRR;
		u16 rclkp = *FIFO_RCLK.pin;
	
		do {
			camera_receive_row(ptr, idr, rclkh, rclkl, rclkp);
			ptr += ImageWidth;
#if OverSampling > 1
			skip_row(rclkh, rclkl, rclkp);
#if OverSampling > 2
			skip_row(rclkh, rclkl, rclkp);
#if OverSampling > 3
			skip_row(rclkh, rclkl, rclkp);
#endif
#endif
#endif
		} while(ptr != end);
	
	camState = 0;

	return SUCCESS;
}

uint16_t grey_to_rgb565(uint8_t input){
	return ((input << 8) & 0xF800) | ((input << 3) & 0x07E0) | (input >> 3);
}
static inline uint16_t grey_to_rgb565_r(uint8_t input) {
	return (input & 0xF8) | ((input >> 5) & 0x07) | ((input << 11) & 0xE000) | ((input << 5) & 0xFF00);
	// return rotate(grey_to_rgb565(input));
}

void camera_copy() {
	u8* ptr2 = &image[0][0];
	for (u16* ptr=&imageToPrint[0][0]; ptr!=&imageToPrint[59][80];) {
		// *ptr++ = grey_to_rgb565_r(*ptr2++);
		COPY_PX_GREYSCALE(*ptr2++, *ptr++);
	}
}

void camera_print(uint8_t x, uint8_t y) {
	// while (!camera_printing_done());
	tft_set_region(x, y, ImageWidth-1, ImageLength-1);
	// camera_copy();
	DMA_DeInit(DMA1_Channel5);
	DMA_Init(DMA1_Channel5, &camera_printing_dma);
	DMA_Cmd(DMA1_Channel5, ENABLE);
}

uint8_t camera_printing_done() {
	return DMA_GetFlagStatus(DMA1_FLAG_TC5);
}

void EXTI12_IRQHandler(void) {
	if(camState == 0)
	{
		FIFO_WRST_L();
		FIFO_WEN_L();
		camState = 1;	   	
		FIFO_WEN_H();
		FIFO_WRST_H();
	}
	else if(camState == 1)
	{
		FIFO_WEN_L();
		camState = 2;
	}
}

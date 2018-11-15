/*	
 *	Camera library - internal 2017/18
 *	Mode 		: ov7725
 *  Author  : Emmett Yim
 *  Contact : yhyim@ust.hk 
 *						66816823
 *	Lib			: camera.h
 */

#ifndef __OV7725_H
#define __OV7725_H
#define OverSampling 4 //1, 2, 3, 4 //Fix Field of View Problem
#define HOFFSET 0 //Fix Image Centering Problem
#define VOFFSET 0
#define ImageLength 60
#define ImageWidth 80
#include "stm32f10x.h"
#include "ticks.h"
#include "lcd_main.h"

extern uint8_t image[ImageLength][ImageWidth];
extern uint16_t colourImage[ImageLength][ImageWidth];
extern uint16_t imageToPrint[ImageLength][ImageWidth];

/**
 * @brief      Initialize the Camera module
 *
 * @return     { description_of_the_return_value }
 */
uint8_t camera_init(void);

/**
 * @brief      Check whether there is a image ready to receive in the FIFO buffer
 *
 * @return     true/false
 */
uint8_t camera_ready(void);

/**
 * @brief      Receive the image from the FIFO buffer into image[][]
 *               colourImage[][]
 *
 * @return     { description_of_the_return_value }
 */
uint8_t camera_receive_frame(void);

/**
 * @brief      copy the pixels in image[][] or colourImage[][] 
 *              to the imageToPrint[][] buffer for printing
 */
void camera_copy(void);

/**
 * @brief      Print out the imageToPrint[][] buffer to the screen
 *  NOTE: this action occurs in the background
 *
 * @param[in]  x     X coord of the top left corner
 * @param[in]  y     Y coord of the top left corner
 */
void camera_print(uint8_t x, uint8_t y);

/**
 * @brief      Has the image finished printing to the screen
 * 	IMPORTANT: do not attempt to print anything else to the screen 
 * 	           while camera printing is ongoing
 *
 * @return     true/false
 */
uint8_t camera_printing_done(void);

/**
 * @brief      convert a 8 bit greyscale value to equivalent 16 bit RGB565 value
 *
 * @param[in]  8 bit greyscale pixel
 *
 * @return     16 bit rgb565 pixel
 */
uint16_t grey_to_rgb565(uint8_t);

#endif //__OV7725_H

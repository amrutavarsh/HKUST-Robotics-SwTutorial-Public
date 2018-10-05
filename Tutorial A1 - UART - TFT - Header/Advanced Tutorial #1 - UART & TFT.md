# Advanced Tutorial #1 - UART & TFT
Author: Jason Ieong(UART)
Contact: zljieong@connect.ust.hk

Author : Morris Tseng(TFT)
Contact: mtseng@connect.ust.hk 

[TOC]

# TFT
>By Morris Tseng
## Initialize
```C
void tft_init(u8 oritentation, u16 in_bg_color, u16 in_text_color, u16 in_text_color_sp);
```
*    oritentation: range from 0 to 3 
(Entering 0 would takes the position of the tft pins as top, then turn in the clockwise direction for 1 to 3.)
* in_bg_color, in_text_color, and in_text_color_sp: in_bg_color, in_text_color and in_text_color_sp : 
colour for background, text, and special text respectively

Default colours:
```C
define WHITE (RGB888TO565(0xFFFFFF))
define BLACK (RGB888TO565(0x000000))
define DARK_GREY (RGB888TO565(0x555555))
define GREY (RGB888TO565(0xAAAAAA))
define RED (RGB888TO565(0xFF0000))
define ORANGE (RGB888TO565(0xFF7700))
define YELLOW (RGB888TO565(0xFFFF00))
define GREEN (RGB888TO565(0x00FF00)
define DARK_GREEN (RGB888TO565(0x00CC00))
define BLUE (RGB888TO565(0x0000FF))
define SKY_BLUE (RGB888TO565(0x11CFFF)
define DARK_GREEN (RGB888TO565(0x8888FF))
define BLUE (RGB888TO565(0x660066))
```

## Clear
Functions for clearing the tft screen
```C
void tft_clear(void);//clear all character output on tft
void tft_force_clear(void);//clear all the output on tft
void tft_clear_line(u8 line);// clear one row
```
*    line : n-th line to be cleared, ranged from 0 to 9


## Print String
```C
void tft_prints(u8 x, u8 y, const char* pstr, ...);
```
*    x : n-th horizontal pixel, ranged from 0 to 127 (i.e. 128 pixels per row)
*    y : n-th vertical pixel, ranged from 0 to 159 (i.e. 160 pixels per column)
*    color : colour of the pixel (in RGB565 format)

Example:
```C
tft_prints(0, 0, "Robotics %d", 2018);
```

## Print Pixels
```C
void tft_put_pixel(u8 x, u8 y, u16 color);
```
*    x : n-th horizontal pixel, ranged from 0 to 127 (i.e. 128 pixels per row)
*    y : n-th vertical pixel, ranged from 0 to 159 (i.e. 160 pixels per column)
*    color : colour of the pixel, also in RGB565 format

p.s. useful in printing camera output

## Update
```C
void tft_update(void);
```
Function for outputing the data stored inside the buffer to tft.
It has to be called after all TFT print function.


# UART
>By Jason Ieong
## Introduction
UART, which stands for Universal Asynchronous Receiver-Transmitter, is a protocol for serial communication and is used when the rate of transmission is not the concern. For example, sending control commands may be fine but it is certainly not suitable for sending high-resolution images.

In tutorial 1, you have learned to use UART for flashing your program, but in this tutorial, we will focus on using UART alongside with Bluetooth such that you can control and debug your robot wirelessly.

As time is limited in class, the tutorial will focus on using the devices and the knowledge of programming will be covered in the "Extra" part, but please try to read it before doing homework/advanced tutorial 3.
# Sending and receiving data with UART
UART(Universal asynchronous receiver-transmitter) sends your data in serial in asynchronous mode.
Serial communication is the process of sending data one bit at a time, and asynchronous means that there is no common clock signal between the sender and receivers. (or in another word, the clock of STM32 and the Bluetooth device may be different, this is why you need to set the baud rate on both sides)

## Initialization the ports on your STM32


As any other modules, you need to initialize UART on stm32 before using it.
Note that this process configures the port(s) and the timer on your board, the ports can initialize with or without connecting to other devices.
```C
// uart.h

/**
 * @brief      Initialize the given UART Port
 *
 * @param      uart      The UART Port Handle
 * @param[in]  baudrate  The Baudrate
 */
void uart_init(UARTPort* uart, u32 baudrate);
```
```C
//call this function for initialization 
uart_init(COM1, 115200);//this initialized port com1 with 115200 baud rate
uart_init(COM3, 115200);//this initialized port com3 with 115200 baud rate
```
Details of this function are covered in the extra part.
## Connecting STM32 to the computer via USB-TTL
The UART port you have been using to flash program in boot mode is called "COM1" (COM stands for communication). This port can works as a normal UART port in the normal mode, so you don't need to change any wire to use the same port for flashing and communicating.

## Sending message from STM32 to computer
>We use Coolterm for demonstration, but there are different ways to interact UART signal. Examples are Tera term, mobile application, and python/C# program written by yourself using Bluetooth stack. However, we may not be able to provide support to people not using Coolterm.

Flash the following programe to the board
```C
#include "main.h"
#include "rcc.h"
#include "ticks.h"
#include "gpio.h"
#include "uart.h"
int main() {
    // Initialize Everything Here
    rcc_init();
    ticks_init();        
    uart_init(COM1,115200);
    uint32_t lastticks=get_ticks();
    while(1){
        if(lastticks!=get_ticks()){
            lastticks=get_ticks();
            if(!(lastticks%250) ){
                uart_tx_str(COM1
                ,"This text is sent every 250 ms \n"); 
                
            }
        }
    }        
}
```
After that, open coolterm and set the followings
TL;DR version:
**option -> serial port-> port = port you used for flahing program
serial port -> baud rate = 115200
serial port -> data bits = 8 bit
serial port -> parity = none
serial port -> stop bits = 1**

**terminal -> termianl mode = line/raw mode 
terminal -> Enter key emulation = CR/LF
terminal -> local echo = check
close option, press connect and run your board, and the messages should appears.**

Explanation:
Baud rate basically means the number of bits of the signal sent per second. 115200 is basically the quickest speed that can works on most devices without any problem. For example, standard windows (or, .net) utilities does not support anything above 115200.
According to the standard of uart, it sends 1 start bit (must), 5/6/7/8 bits of data, 1 bit of parity check (optional),1/1.5/2 bit of stop bit. Our setting uses 1 start bit, 8 data bits, 0 parity bit and 1 stop bit, which means that 8 bit = 1 byte out of 10 bits sent are data, with a baud rate of 115200, effectively 11520 bytes of data could be sent in one second.
**The two extra bit of start bit and stop bit are handled automatically by stm32 and coolterm and you don't have to worry about them.**
For the terminal, raw mode means that data will be sent when you press a key on the keyboard, Whereas there will be an extra line for you to input a whole string and sed at once in line-mode. This two modes mostly matter when configuring the Bluetooth device and will be covered later.
Local echo means does cool term display what you typed and does not affect what you send/receive.

**Please complete this part to test that your computer configuration work before continue.** 

## Sending message from the computer to STM32
>This part uses function pointer for the hardware interrupt, which will be explained only briefly in the extra part, and the pointer may be hard for beginners to understand. However, as long as you follow the given syntax, setting up an interrupt to be called is not that hard.
### interrupt
As you can tell from the name "interrupt" when the board detects some special condition, the main program that is running will be "interrupted" to stop and run another function that is set corresponding to this condition. The main program will start running again only when the interrupt is handled. The corresponding function is often called a listener or handler. For example, a function that handles a button press can be called "ButtonOnPressHandler" or "ButtonOnPressListener".
Remember to init the port before init the rx_port.
```C
//uart.h

//this define data type UARTOnReceiveListener
typedef void (*UARTOnReceiveListener)(const uint8_t byte);


//call this function for initializing a listener
void uart_rx_init(UARTPort* uart, UARTOnReceiveListener listener);
```
**"UARTOnReceiveListener"** is a user-defined type **of the function pointer, where the function takes a const uint8_t as the argument and have no return.**
After you call uart_rx_init() and set up the listener, the function will trigger every time it receives 1 byte of data(or, equivalently 10 bits signal). As one character of English in ASCII is also one byte, then the listener will trigger once per character typed in Coolterm.

skeleton code: 
```C
//a function that takes a uint8_t as argument and have no return 
void UARTOnReceiveHandler(const u8 received){
    //whenever you type something in coolterm, 
    //each character will triger this function 
    //the character will be the argument for this function
    return;
}

int main() {
    // Initialize Everything Here
    rcc_init();
    ticks_init();    
    uart_init(COM1,115200);
    //call uart_rx_init 
    uart_rx_init(COM1,&UARTOnReceiveHandler);
    uint32_t lastticks=get_ticks();
    while(1){
        if(lastticks!=get_ticks()){
            lastticks=get_ticks();
        }
    }        
}
```
Note: Define your listener function **Outside** other function. **Add a "&" sign before the name of the listener function to pass the pointer of this function.** Adding space between or not does not matter. The programe **Can compile** even if the **function prototype of your function is wrong**, so make sure your function **return void** and **takes a uint8_t as argument.**
Avoid doing runtime consuming stuff in such handler or werid stuff may happen. 

## Setup Your Bluetooth device
>This process may or may not have done for you, so it may be a better idea to do it by yourself

>Technically all uart port can be used to config the Bluetooth, including the stm32, but using Coolterm is just the quicker way.

>The way of configuring HC05 is provided, and other devices such as HC06, HM10 may be different
1. Connect USB-TTL with your device: 5v/VCC to 5v, GND to GND, TX to RX and RX to TX.
2. Hold the button on HC05 while plugging in the USB to the computer
3. Release the button, HC05 should be in "AT" mode and the led should flash slowly.
4. Set coolterm baud rate to 38400 and connect.
5. Type "AT" and press enter. If it replies "OK", then you can use the following AT commands to configure the device. Otherwise, check the steps above again.
6. Note that some commands (such as AT+NAME=.../AT+NAME?) may require you to hold the button while pressing enter to work.
7. Note that AT command is case-sensitive

List of commands:

1. AT (for Testing)
2. AT+RESET (back to normal mode, doesn't mean reset configs)
3. AT+NAME? (return name of the device)
4. AT+NAME=<Param>  (set name)
5. AT+ PSWD?  (return password)
6. AT+ PSWD=<Param>  (set password)
7. AT+UART=<Param>,<Param2>,<Param3> 
(set baud rate,stop bit (0 -- 1 bit,1 -- 2 bit),no. of parity bit)
recommended settings: AT+UART=115200,0,0
8. AT+UART?  (return setting of uart)
9. AT+ORGL  (reset all setting to default ones)

After configuring the device, you may plug it onto COM3 of your STM32 board(Note that COM3 is directly below of COM1). The computer should be able to find the device when power is given to HC05. After pairing with the device, rescan the port in the "serial port" option of coolterm and new ports should appear. The port that requires time connecting is likely the correct port, as your computer is acting as the master side and need to wait for HC05 to respond, while the other port waits for HC05 actively connect with the computer(which will not happen).

Adding in HC05 allow you to communicate wirelessly, but the actual usage is the same with connecting directly. 

# Classwork
1. Complete the given skeleton code of listener such that the display of the TFT will be the same as what you have typed on the computer (with local echo).
2. As uart, interrupt can also set up for the button. Given the type of ButtonListener is a function pointer that has**no return and no argument**, set up the interrupt with the function below for each button such that the board sends out a string to the computer to show which button is pressed and the time duration.
```C
 /**
 * @brief      Sets the button down listener.
 *
 * @param      button    The button
 * @param[in]  listener  The listener
 */
void set_button_down_listener(Button button, ButtonListener listener);

/**
 * @brief      Sets the button up listener.
 *
 * @param      button    The button
 * @param[in]  listener  The listener
 */
void set_button_up_listener(Button button, ButtonListener listener);
```
3. Set up a "Debug mode" for your STM32 such that you can wirelessly control:
* servo to specific angle
* each motor to a specific duty cycle
* on/off of each led and buzzer
* on/off of GPIO 5~8 output
* on/off the TFT
TFT should keep updating and display the status of other devices when it is "on" and clear and stop updating if it is "off".
Feel free to make up your own protocol or make a programme to control.
The programme should throw some respond such as "ok" if the control success.
Exmaple of protocol:"%MOTOR1 12!";"%GPIO1 ON!"







# Advanced Tutorial #3 - STM32 Timers

Today is a short tutorial on one of the most powerful and versatile peripherals in the STM32, the Timer. You already know its use in output compare mode for generating PWM signals but it can be used in a few other ways as well. I will also touch on how the hardware and Standard Peripheral Library of the STM32 is setup in order to be able to write your own libraries that use low-level hardware features.

We will not be providing any libraries for using the timer in these advanced ways, instead we will help present the theory of operation and hope that you will be able to write your own library, as that is a valuable skill you may need as a robotics team member.

----

## As a Clock

### The Time base Unit

The Timer consists of many parts that work together. It contains a **Time Base Unit** which counts at a certain rate according to the prescaler and auto-reload value. 

Also, it has up to 6 **capture/compare channels** which connects the time base and input or output pins to perform certain functions, these are the channels you used for generating PWM. 

If we only initialize the time base unit the timer can be used *purely internally in code* to keep track of time, either periodically like a clock, or as a one-off event like a stopwatch.

We know that a timer internally counts at a specific frequency defined by the prescaler, we can access the value of this counter from software and use it to see how much time has passed since we started the timer. But we can do better, we can use the timers' *status register*

### Peripheral Registers

Registers are a key part of the interaction between hardware peripherals and software code, these are blocks of memory in the hardware peripheral but they are mapped to appear almost like a variable so they can be manipulated from code just like any variable or pointer. 

You have **control registers** that set the parameters for various aspects of the peripheral and **status registers** that store the state of the peripheral. Specific bits in each register perform different functions, each bit (or sometimes pair/triplets) are usually known as **flags**.

The timer has a flag known as the update interrupt flag, which gets set when the internal counter value hits the auto-reload value. As you already know how to make this period an arbitrary length you should understand how to time out an arbritrary length of time by just checking a single bit of memory. 

By default, the timer wraps but keeps running after it hits the auto-reload value, so if you reset the bit every time you read it, you have generated a very precise clock in software that uses very little memory or cpu time. Alternatively by setting the timer to One Pulse Mode it will automaticaly stop after hitting the auto-reload value.

### Connecting multiple peripherals

To go even more advanced, many times the update event of the timer can be used to trigger functions in many of the other peripherals like the ADC/DAC/DMA/Other timers. This exemplifies how the true essence of embedded microcontroller programming is not always to write code for your desired logic, but to configure the hardware peripherals to do that logic for you. Thus it can be faster, more efficient, more accurate, and allow you to do multiple things at once.

---

## As a Timer (of external signals)

### Input Capture

The IO channels of the timer are in fact called **Capture/Compare Channels**, this alludes to the fact that they have 2 modes: Output Compare (as you already know) and Input Capture.

Input Capture is used to measure the timing of a signal coming into the pin, specifically it remembers the time of the last rising/falling/either edge. The internal counter operates as usual, and when the Input Capture channel sees the edge its looking for it *captures* the value of the counter into the **Capture/Compare Register**

Additionally, while each CC channel has its own IO pin, in IC mode 2 channels can be configured to use the same IO pin, where the second channel is said to be in slave mode. Thus each channel can be configured to capture a different edge simultaneously and separately. 

The application of this you will most likely be interested in is to read the output of **ultrasonic sensors**. Ultrasonic sensors echo output goes high for a length of time proportional to the distance of the object in front of it, this can be timed and measured accurately and completely in the background by the timer peripheral. You could even control the sensors trigger pin at regular intervals by a different channel of the same timer. Remember, dont write the logic, make the hardware do the logic.

----

## As a Counter (of external signals)

Till now we have used the time base unit with the internal clock, however it also also possible to make it count using one or more external signals.

At its most basic, you could count the number of edges of the input signal. However more importantly, the counter can be used to read quadrature encoders.

### What are Encoders?

Encoders convert physical information (usually position or angle) into digital or analog electrical signals. The kind relevant to you in this competition is the **Optical Rotary Incremental Quadrature Encoder**. Lets break that down:

 - Optical: uses light to measure
 - Rotary: measures angle
 - Incremental: actually measures *changes* in angle
 - Quadrature: the output is a pair of series of pulses, 90 degrees out of phase

Specifically, the encoder has a disk with a series of lines cut into it, on either side is a LED and a light sensor. When the transparent line is in the reading position the light sensor can see the LED and outputs a 1, and when the opaque line is in the reading position it can't see any light and outputs a 0. In this way we can tell when the disk (and shaft that its attached to) rotates

![](https://i.imgur.com/Jrqdsjf.png)
http://www.creative-robotics.com/quadrature-intro

### What does Quadrature Mean?

Technically it means that the output is a pair of signals that are 90 degrees out of phase. Specifically it means that every unit of change of angle produces a pulse on each output, but not a the same time, each output takes turns with the rising and falling edges. (I hope my in-person explanation is better, feel free to stop me and ask me to repeat my explanation until you get it, this can be confusing)

This has the benefit of quadrupling our resolution compares to the density of lines on the disk, as well as allowing us to know the direction of rotation as well as the magnitude.

### Encoder counters

The Quadrature signal can be represented as a fairly simple FSM and thus with a little bit of memory and some boolean logic we can count the pulses of the encoder along with the direction to get a measure of how much the shaft has rotated. ST has kindly already implemented this on their timers, and thus you can quickly use encoders by connecting the 2 signals to 2 channels of a timer configured in encoder mode and reading the counter register.

### What do I use it for?

Keep track of position and velocity. Measuring these is a common and important form of feedback that can be used to make our control more accurate. I will not go into much detail but logically you can realise that unless you can 100% predict exactly what a motor/actuator will do when given some signal, it is not enough to just output a specific signal and hope it does what you want. This is called open loop control.

What you must do is "close the loop", that is you have to get feedback from the real world about what your actuators/motors are doing and the error from what you want, and adjust your output signal based on this error feedback.

Finally: look up and learn PID control. Go slow, its slightly complex but one of the most important topics in robotics.

---

## General Hardware Peripheral Requirements

If a hardware peripheral wants to use a pin for any kind of IO, you must initialize the GPIO pin to a suitable mode: IN_FLOATING, IPU or IPD for input and AF_PP and AF_OD for output (not OUT_PP);

Most Peripherals give you a choice of multiple pins to perform the same IO functions. This is handled by the `GPIO_PinRemapConfig(GPIO_Remap_XYZ, ENABLE)` function, to know what value to pass you must read the Reference Manual and/or the Standard Peripheral Library docs/code.

Finally but most importantly the peripheral must be enabled and clocked to work at all, this is handled by the RCC (Reset and Clock Circuitry). Generally this requires careful reading of the reference manual and flipping select bits in registers. We(I) have helpfully wrapped this up in a few function in rcc.c/.h

```
void gpio_rcc_init(GPIO_TypeDef* gpio);
void uart_rcc_init(USART_TypeDef* uart);
void tim_rcc_init(TIM_TypeDef* tim);
void spi_rcc_init(SPI_TypeDef* spi);
void adc_rcc_init(ADC_TypeDef* adc);
void dma_rcc_init(DMA_TypeDef* dma);
```
for other peripherals, good luck and have fun ;)

---

## Tips for writing Libraries for hardware

Always look at the datasheet and schematic for the functionality of different pins

Read the reference manual for *deep* dive (1132 pages for stm32f10x) into the functionality of different peripherals. Tells you **all** about the registers and their flags.

Read the code and comments of the Standard Peripheral Library (stm32f10x_abcd.c/.h) to see specifically how that deals with the peripheral.

Read example code from the internet. STM32 have a few core libraries that people use, the SPL (which we use), as well as the HAL and LL. While HAL and LL examples may be useful for understanding the sequence of operations, SPL examples will be more directly usable. (https://github.com/avislab/STM32F103)

Find the compromise between generality and specificity. Support every single mode of operation (even ones you wont use)? Itll be very complex, maybe slow, and annoying to read and debug. Support a very specific function? Very convenient and easy to do that, but then it becomes hard when it turns out you need to do something else. Usually you should have layers that build on each other, getting more specific so you can easily use common specific functions, but also extend functionality well.

Specifically for timers:
 - https://www.st.com/resource/en/application_note/dm00236305.pdf
 - https://www.st.com/resource/en/application_note/dm00042534.pdf

---

## Use header files to define and document the interface of your library

It is important to write code that your teammates can read. But what is even better is if you can write code that they don't have to read. A well defined and easy to understand interface can make using a library much easier.

Header files encode the public interface into the code such that it can be easily understood and checked by the compiler. 

A few main components of a good header file:

**Declare all the functions that you want others to use,** generally an init function, plus various functions to use it. Add a doxygen formatted comment to describe the functionality of each function.

-Use `#define` to give meaningful names to constants, eg

    #define MOTOR_TIM TIM3 //Rename hardware peripherals so that reading and writing code 
    #define LED1 &PC14 //is more natural, and is easy to change if something changes
    #define CHAR_HEIGHT 16 //Name all 'magic numbers' so that people know what it means
    #define SKY_BLUE (RGB888TO565(0x11CFFF)) //and so that you never have to remember them
    

-Use `typedef struct` to define types that can help pack related data together and give meaningful names to them and their relationship, eg:

    typedef struct {
	    USART_TypeDef* periph;
        const GPIOPin* tx_pin;
        const GPIOPin* rx_pin;
        UARTOnReceiveListener rx;
        UARTTransmissionHandler tx;
        u32 remap;
    } UARTPort;

-Use `typedef enum` to give meaningful names and types to numbers that are related, and/or to states for your internal FSMs, eg:

    
    typedef enum {
    	PWM_CHANNEL_1,
    	PWM_CHANNEL_2,
    	PWM_CHANNEL_3,
    	PWM_CHANNEL_4,
    } PWMChannelID; //PWM Channel Number, Enums are more clear than bare numbers
   
    typedef enum{
    	CLAMPED,
    	UNCLAMPED,
    	SHOOTING,
    	RELEASED,
    	READY,
    }SHOOTER_STATE; //FSM states (from our last year Robocon robot)
    
    typedef enum {
	    DONT_RELEASE,
	    DO_RELEASE,
    } DO_RELEASE_STATE; //Even binary values can be made more clear using enums

---

# Internal Competition Q&A Session

Ask Us Anything about softwares role in the internal compeition, if you don't have any questions, you can leave :-)

---

Anshuman Medhi - amedhi@connect.ust.hk - 68925193

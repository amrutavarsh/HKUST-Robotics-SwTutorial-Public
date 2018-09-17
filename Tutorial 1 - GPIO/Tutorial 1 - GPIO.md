# Tutorial 1: GPIO

Author: Joseph Lam<br>
Contact: mhlamaf@ust.hk

## Basic

#### What is GPIO?
A **general-purpose input/output (GPIO)** is an uncommitted digital signal pin on an integrated circuit or electronic circuit board whose behavior—including whether it acts as an input or output—is controllable by the user at run time.

<br>

### Fundamental Program Structure
```C
#include "main.h"

// Include Library Headers Here
#include "rcc.h"
#include "ticks.h"
#include "gpio.h"
#include "leds.h"
#include "buttons.h"
#include "buzzer.h"

int main() {
	// Initialize Everything Here
	rcc_init();
	ticks_init();

	// I hope you can understand how the following 4 lines of code work
	while (1) {
		static u32 this_ticks = 0;
		while (get_ticks() == this_ticks);
		this_ticks = get_ticks();

		// Everything from here will run every 1ms

		static u32 last_led_ticks=0;
		if ((this_ticks - last_led_ticks) >= 25) {
			last_led_ticks = this_ticks;
			//Code in here will run every 25ms
		}
	}
}
```
Try not to use `int`, `long`, `long long`, `float`, `double` for embedded system programming. Instead, use the followings:

| Full name | Short form | Meaning                  |
| :-------: | :--------: | :----------------------: |
| uint8_t   | u8         | unsigned 8 bits integer  |
| uint16_t  | u16        | unsigned 16 bits integer |
| uint32_t  | u32        | unsigned 32 bits integer |
| uint64_t  | u64        | unsigned 64 bits integer |
|           |            |                          |
| int8_t    | s8         | signed 8 bits integer    |
| int16_t   | s16        | signed 16 bits integer   |
| int32_t   | s32        | signed 32 bits integer   |
| int64_t   | s64        | signed 64 bits integer   |

Both full name and short form work.<br>
**Note:** We seldom use `float` and `double` as floating point calculation take more time than integer calculation.

<!--
 ██████  ██████  ██  ██████       ██████  ██████  ███    ██ ███████ ██  ██████
██       ██   ██ ██ ██    ██     ██      ██    ██ ████   ██ ██      ██ ██
██   ███ ██████  ██ ██    ██     ██      ██    ██ ██ ██  ██ █████   ██ ██   ███
██    ██ ██      ██ ██    ██     ██      ██    ██ ██  ██ ██ ██      ██ ██    ██
 ██████  ██      ██  ██████       ██████  ██████  ██   ████ ██      ██  ██████
-->

<br>

### GPIO Configuration

#### Initialization of GPIO
The `gpio_init()` function initializes a GPIO pin with the following parameters:
- `gpio`: indicates which GPIO pin to be initialized
- `mode`: indicates which GPIO mode to be applied for this GPIO pin

```C
static inline void gpio_init(const GPIOPin* gpio, GPIOMode_TypeDef mode);
```

##### *Definition of `GPIOPin`*
```C
#define GPIO1 &PA0
#define GPIO2 &PA1
#define GPIO3 &PA2
#define GPIO4 &PA3
#define GPIO5 &PA4
#define GPIO6 &PA5
#define GPIO7 &PA6
#define GPIO8 &PA7
#define GPIO9  &PA13
#define GPIO10 &PA14
```

##### *Definition of `GPIOMode_TypeDef`*
```C
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
} GPIOMode_TypeDef;
```
For **input**, use the following modes:
- `GPIO_Mode_AIN`
- `GPIO_Mode_IN_FLOATING`
- `GPIO_Mode_IPD`
- `GPIO_Mode_IPU`

Usually, `GPIO_Mode_IPD` / `GPIO_Mode_IPU` is used, depending on the hardware situation.

For **output**, use the following modes:
- `GPIO_Mode_Out_OD`
- `GPIO_Mode_Out_PP`
- `GPIO_Mode_AF_OD`
- `GPIO_Mode_AF_PP`

Usually, `GPIO_Mode_Out_PP` is used.

##### Example:
```C
/* GPIO Pin Init*/

// configure as input
gpio_init(GPIO1, GPIO_Mode_IPU);
gpio_init(GPIO2, GPIO_Mode_IPU);
gpio_init(GPIO3, GPIO_Mode_IPD);
gpio_init(GPIO4, GPIO_Mode_IPD);

// configure as output
gpio_init(GPIO5, GPIO_Mode_Out_PP);
gpio_init(GPIO6, GPIO_Mode_Out_PP);
gpio_init(GPIO7, GPIO_Mode_Out_PP);
gpio_init(GPIO8, GPIO_Mode_Out_PP);
```

<br>

#### Reading GPIO Input
The `gpio_read()` function reads the GPIO input with the following parameter:
- `gpio`: indicates which GPIO pin to be read

```C
static inline u8 gpio_read(const GPIOPin* gpio);
```

##### Example:
```C
// getting the GPIO1 input
// 1 for high, 0 for low if the GPIO mode is GPIO_Mode_IPD
u8 input = gpio_read(GPIO1);
```

<br>

#### Writing GPIO Output
The `gpio_write()` function writes GPIO pin with the following parameters:
- `gpio`: indicates which GPIO pin to be written
- `bit`: indicates it is written as digital `high`(`1`) or `low`(`0`)

```C
static inline void gpio_write(const GPIOPin* gpio, u8 bit);
```

Alternatively, the following two functions write the GPIO pin directly with the following parameter:
- `gpio`: indicates which GPIO pin to be written

```C
static inline void gpio_set(const GPIOPin* gpio);
```
```C
static inline void gpio_reset(const GPIOPin* gpio);
```
`gpio_set()` write the GPIO pin as `high` while `gpio_reset()` write the GPIO pin as `low`

##### Example:
```C
// set GPIO1 to high
gpio_write(GPIO1, 1);
// set GPIO1 to low
gpio_write(GPIO1, 0);

// alternative way to set GPIO1 to high
gpio_set(GPIO1);
// alternative way to set GPIO1 to low
gpio_reset(GPIO1);
```

***Library Reference:***
- `/src/libiary/gpio.c`
- `/src/libiary/gpio.h`
- `/src/stm32f10x_std/inc/stm32f10x_gpio.h`

<!--
██      ███████ ██████       ██████  ██████  ███    ██ ████████ ██████   ██████  ██
██      ██      ██   ██     ██      ██    ██ ████   ██    ██    ██   ██ ██    ██ ██
██      █████   ██   ██     ██      ██    ██ ██ ██  ██    ██    ██████  ██    ██ ██
██      ██      ██   ██     ██      ██    ██ ██  ██ ██    ██    ██   ██ ██    ██ ██
███████ ███████ ██████       ██████  ██████  ██   ████    ██    ██   ██  ██████  ███████
-->

<br>

### LED Control

#### Initialization
The `leds_init()` function initializes all two LEDs on the mainboard.
```C
void leds_init(void);
```

<br>

#### Turn on LED
The `led_on()` function turns on a LED with the following parameter:
- `led`: indicates which led to be turned on

```C
void led_on(LED led);
```

##### *Definition of `LEDHandle`*
```C
#define LED1 &PC1
#define LED2 &PC2
```

##### Example:
```C
// turn on LED1
led_on(LED1);
```

<br>

#### Turn off LED
The `led_off()` functions turn off a LED with the following parameter:
- `led`: indicates which led to be turned off

```C
void led_off(LED led);
```

##### Example:
```C
// turn off LED1
led_off(LED1);
```

***Library Reference:***
- `/src/libiary/led.c`
- `/src/libiary/led.h`

<!--
██████  ██    ██ ███████ ███████ ███████ ██████
██   ██ ██    ██    ███     ███  ██      ██   ██
██████  ██    ██   ███     ███   █████   ██████
██   ██ ██    ██  ███     ███    ██      ██   ██
██████   ██████  ███████ ███████ ███████ ██   ██
-->

<br>

### -Buzzer-

#### Initialization
```C
void buzzer_init(void);
```

#### Buzzer on
```C
void buzzer_on(void);
```

#### Buzzer off
```C
void buzzer_off(void);
```

#### Remark:
- It can be used to show state / debug, similar to leds
- Please do not *distroy* other's ears ^ ^

##### Example:
```C
// initialize the buzzer
buzzer_init();

// turn on the buzzer
buzzer_on();

// turn off the buzzer
buzzer_off();
```

***Library Reference:***
- `/src/libiary/buzzer.c`
- `/src/libiary/buzzer.h`

<!--
██████  ██    ██ ████████ ████████  ██████  ███    ██
██   ██ ██    ██    ██       ██    ██    ██ ████   ██
██████  ██    ██    ██       ██    ██    ██ ██ ██  ██
██   ██ ██    ██    ██       ██    ██    ██ ██  ██ ██
██████   ██████     ██       ██     ██████  ██   ████
-->

<br>

### Button

#### Initialization
The `buttons_init()` function initializes all buttons on the mainboard.

```C
void buttons_init(void);
```

<br>

#### Button Input
The `button_pressed()` function reads the button input with the following parameter:
- `button`: indicates which button to be read

```C
u8 button_pressed(Button button);
```

##### *Definition of `Button`*
```C
typedef enum {
	BUTTON1,
	BUTTON2,
	BUTTON3,
} Button;
```

##### Example:
```C
// getting BUTTON1 input, 1 for pressed, 0 for not pressed
u8 pressed = button_pressed(BUTTON1);
```

<br>

#### Software Debouncing
**Bouncing** may occur when two metal contacts as they bounce apart one or more times before making steady contact. Thus, multiple signals are generated. Therefore, hardware or software **debouncing** is needed to ensure only **one signal** is generated when the contact is closing or opening.

##### Implementation
```C
if (this_ticks - last_ticks >= 50) {
  static u8 debounce;

  // reset debounce if button is not pressed
  if (!button_pressed(BUTTON1) && debounce) {
    debounce = 0;
  }

  // set debounce if button is initially pressed
  if (button_pressed(BUTTON1) && !debounce) {
    debounce = 1;
  }

  // handle button triggered event after debouncing
  else if (button_pressed(BUTTON1) && debounce) {
    // button triggered event
  }
}
```
***Library Reference:***
- `/src/libiary/button.c`
- `/src/libiary/button.h`

<br>

## Extra

<!--
███████ ███    ██ ██    ██ ███    ███
██      ████   ██ ██    ██ ████  ████
█████   ██ ██  ██ ██    ██ ██ ████ ██
██      ██  ██ ██ ██    ██ ██  ██  ██
███████ ██   ████  ██████  ██      ██
-->

### Enum
An **enumeration** is a type that can hold a finite set of symbolic objects, which are represented as integers internally. By default, the first object is given the value `0`, then the subsequent object is assigned a value **one greater** than the previous object's value. It is very useful in writing libraries as it increases the **readability** of the program, so everyone can understand the program easily.

Syntax of define a new enum:
```
typedef enum {<identifier1> [=value1], <identifier2> [=value2], ...} <new_datatype>;
```

The following is an example of `enum`:
``` C
typedef enum {
	BUTTON1,  // BUTTON1 = 0
	BUTTON2,  // BUTTON2 = 1
	BUTTON3,  // BUTTON3 = 2
} Button;

// define a variable with the new enum
Button btn = BUTTON1;
// assign a new value to variable "btn"
btn = BUTTON2;
// assign a new value by integer
// remember to cast it into Button type, otherwise warning will be given while compiling, but the program can still be compiled
btn = (LED_ID) 2;  // equivalent to btn = BUTTON3;
```

Alternatively, you can assign an integer value to the object in enum:
``` C
typedef enum {
	BUTTON1 = 1,  // BUTTON1 = 1
	BUTTON2,      // BUTTON2 = 2
	BUTTON3,      // BUTTON3 = 3
} Button;
```

<!--
███████ ████████ ██████  ██    ██  ██████ ████████
██         ██    ██   ██ ██    ██ ██         ██
███████    ██    ██████  ██    ██ ██         ██
     ██    ██    ██   ██ ██    ██ ██         ██
███████    ██    ██   ██  ██████   ██████    ██
-->

### Struct
A **Structure** is a collection of different kinds of objects. You can define a new user-defined data type by using `struct`. `struct` is more convenient than defining multiple variables.

Syntax of define a new `struct`:
```
typedef struct {
	<data_type> <identifier for the 1st member>;
	<data_type> <identifier for the 2nd member>;
	...
} <struct identifier>;
```

The following is an example of defining a 3D coordinate without struct:
```C
// define all variables
uint8_t x = 0;
uint8_t y = 0;
uint8_t z = 0;
// assign new values to variables
x = 1;
y = 2;
z = 3;
```

The following is an example of defining a 3D coordinate with struct:
```C
// define a new struct "Coordinate"
typedef struct {
	uint8_t x;
	uint8_t y;
	uint8_t z;
} Coordinate;
// define and initialize a struct variable
Coordinate coor = {0, 0, 0};  // {x, y, z}
// assign new values to variables
coor.x = 1;
coor.y = 2;
coor.z = 3;
```

<!--
██████  ███████ ███████ ██ ███    ██ ███████
██   ██ ██      ██      ██ ████   ██ ██
██   ██ █████   █████   ██ ██ ██  ██ █████
██   ██ ██      ██      ██ ██  ██ ██ ██
██████  ███████ ██      ██ ██   ████ ███████
-->

### Define
Similar to `const`, `#define` is used to create a **constant** in program, but using `#define` is different from using `const`. When using `#define`, things defined by `#define` are replaced to be the value before compilation. When using `const`, the value is still being stored inside a variable. Using `#define` can increase the readability of code and increase the ease of changing value.

Syntax of `#define`:
```
#define NAME <value>
```

The following is an example of using `#define`:
```C
#define DefaultLED 1
uint8_t led = DefaultLED;

// The above code is equivalent to the following:
uint8_t led = 1;
```

Note: `#define` can also be used to define macro function, but we won't discuss that in here.

<br>

### GPIO Setup

To set up a GPIO pin, the following should be done:
- Enable the peripheral clock for GPIOx - `RCC_APB2Periph_GPIOx`
- specify the following information:
		1. GPIO port - `GPIOx`
		2. GPIO pin - `GPIO_Pin_x`
		3. GPIO mode
		4. GPIO speed - `GPIO_Speed_50MHz`(set as this normally)
- Initialize the corresponding GPIO port

Taking the gpio_init for `GPIO1`(`PA0`) as an example:
```C
//GPIO setup for GPIO1(PA0)
GPIO_InitTypeDef GPIO_InitStructure;
//enable the peripheral clock for GPIOA
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//set the pin as GPIO_Pin_0
GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
//set the gpio mode to input pull up
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
//set the speed as 50MHz
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//initialize it to gpio port GPIOA
GPIO_Init(GPIOA, &GPIO_InitStructure);
```

<br>

#### GPIO port & GPIO pin
There are **4 peripherals** (GPIOA, GPIOB, GPIOC, GPIOD), each would have 16 pins(from 0 to 15) maximum.<br>
For example, GPIO1 in this mainboard is assigned to `PA0`, where A means GPIOA and 0 means `Pin_0`.

#### Peripheral clock
Each GPIOx has its own peripheral clock for its own timing purpose.<br>
`APB2` means it is a high speed peripheral clock(72MHz, as fast as the MCU frequency).

#### GPIO_Mode
Among
```C
typedef enum
{ GPIO_Mode_AIN = 0x0,
  GPIO_Mode_IN_FLOATING = 0x04,
  GPIO_Mode_IPD = 0x28,
  GPIO_Mode_IPU = 0x48,
  GPIO_Mode_Out_OD = 0x14,
  GPIO_Mode_Out_PP = 0x10,
  GPIO_Mode_AF_OD = 0x1C,
  GPIO_Mode_AF_PP = 0x18
}GPIOMode_TypeDef;
```
only ```GPIO_Mode_IPD```, ```GPIO_Mode_IPU```, ```GPIO_Mode_Out_OD``` and ```GPIO_Mode_Out_PP``` will be covered.

#### GPIO_Mode_IPD
**Input Pull Down** (**IPD**) has to be set when the GPIO is connected to a pull down resistor.<br>

 Hardware connection:<br>
![when the GPIO is connected to a pull down resistor](https://i.imgur.com/sd7FdFC.jpg)

#### GPIO_Mode_IPU
**Input Pull Up** (**IPU**) has to be set when the GPIO is connected to a pull up resistor.<br>

 Hardware connection:<br>
![when the GPIO is connected to a pull up resistor](https://i.imgur.com/iS3Od90.jpg)

#### GPIO_Mode_Out_OD
**Output Open Drain** (**Out_OD**) can be used for the following function:q
1. communication pin setting (e.g. i2c).
2. power external circuit which would consume higher voltage(>3.3V) with suitable hardware circuit.
3. many other usage that you may do research yourself.

#### GPIO_Mode_Out_PP
**Output Push Pull** (**Out_PP**) outputs ```VCC``` when GPIO is set to ```high```; ```GND``` when GPIO is set to ```low```.<br>

Hardware connection:<br>
![outputs ```VCC``` when GPIO is set to ```high```; ```GND``` when GPIO is set to ```low```](https://i.imgur.com/UerwY9k.png)

#### GPIO speed
GPIO speed is the maximum `SET` / `RESET` access you can make every second.<br>
Normally, it is set to its maximum supported speed by hardware : `GPIO_Speed_50MHz`<br>
```C
typedef enum
{
  GPIO_Speed_10MHz = 1,
  GPIO_Speed_2MHz,
  GPIO_Speed_50MHz
}GPIOSpeed_TypeDef;
```

---
### EXTI & NVIC

*the following code is taking GPIO1 (PA0) as an example*

#### Definition of EXTI
**EXTI** means **external interrupt**.<br>
Interrupt is a prioritized event that would be handled first at any time, while temporarily pausing the current event until the interrupt is finished.<br>
External interrupt is an interrupt triggered by an external device through GPIO, for example the input from a limit switch.<br>
**Advantage** : does not need to perform GPIO input checking with gpio_read frequently<br>
**Disavantage** : interrupt will happened for multiple times if there is input bouncing as EXTI has no hardware debouncing while software debouncing is also not applicable.

#### EXTI setup example
```C
EXTI_InitTypeDef EXTI_InitStructure;
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
EXTI_InitStructure.EXTI_Line = EXTI_Line0;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//interrupt triggered by rising edge
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//interrupt triggered by falling edge
//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling ;
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);
EXTI_GenerateSWInterrupt(EXTI_Line0);
```

#### Definition of NVIC
**NVIC** means **Nested Vectored Interrupt Controller**.<br>
It controlls the handling of different interrupts (*EXTI, ADC and TIM*) and their priorities.

#### NVIC setup example
```C
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
```

#### IRQ Handler example
```C
//checking the flag for external interupt for line 0
if ( EXTI_GetITStatus(EXTI_Line0) != RESET )
{
   //your code here
   //...

   //clear the flag
   EXTI_ClearITPendingBit(EXTI_Line0);
}
```

#### Sample setup of `GPIO1` as external interrupt source
```C
//GPIO setup
GPIO_InitTypeDef GPIO_InitStructure;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_Init(GPIOA, &GPIO_InitStructure);
//EXTI setup
EXTI_InitTypeDef EXTI_InitStructure;
GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
EXTI_InitStructure.EXTI_Line = EXTI_Line0;
EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//interrupt triggered by rising edge
EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
//interrupt triggered by falling edge
//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
EXTI_InitStructure.EXTI_LineCmd = ENABLE;
EXTI_Init(&EXTI_InitStructure);
EXTI_GenerateSWInterrupt(EXTI_Line0);
//NVIC setup
NVIC_InitTypeDef NVIC_InitStructure;
NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
NVIC_Init(&NVIC_InitStructure);
```

#### Pin configuration reference for EXTI

| Pin | GPIO_Pin | GPIO_PinSource | EXTI_Line | NVIC_IRQChannel | IRQHandler |
| :---: | :---: | :---: | :---: | :---: | :---: |
| Pin 0 | GPIO_Pin_0 | GPIO_PinSource0 | EXTI_Line0 | EXTI0_IRQn | EXTI0_IRQHandler |
| Pin 1 | GPIO_Pin_1 | GPIO_PinSource1 | EXTI_Line1 | EXTI1_IRQn | EXTI1_IRQHandler |
| Pin 2 | GPIO_Pin_2 | GPIO_PinSource2 | EXTI_Line2 | EXTI2_IRQn | EXTI2_IRQHandler |
| Pin 3 | GPIO_Pin_3 | GPIO_PinSource3 | EXTI_Line3 | EXTI3_IRQn | EXTI3_IRQHandler |
| Pin 4 | GPIO_Pin_4 | GPIO_PinSource4 | EXTI_Line4 | EXTI4_IRQn | EXTI4_IRQHandler |
| Pin 5 - 9 | GPIO_Pin_5 to 9 | GPIO_PinSource5 to 9 | EXTI_Line9_5 | EXTI9_5_IRQn | EXTI9_5_IRQHandler |
| Pin 10 - 15 | GPIO_Pin_10 to 15 | GPIO_PinSource10 to 15 | EXTI_Line15_10 | EXTI15_10_IRQn | EXTI15_10_IRQHandler |


## Homework
release during your tutorial section via email

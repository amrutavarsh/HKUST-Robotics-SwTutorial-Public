# Tutorial #2 - PWM

Today we will see how PWM Signals are a way of producing a **Analog** signal, and how we can actually generate these signals with a **Timer**

But first, what *is* PWM?

---

## Pulse Width Modulation = Varying the duty cycle of a Square Wave 

What!?

A Square Wave is a basically a series of square shaped pulses, pretty self explanatory. But it has many properties that make it incredibly useful.

### Duty Cycle

The most important property is the duty cycle. Aka what proportion of time the signal is high for. (Although it is usually represented as a percentage)

**Duty Cycle = T_on / T_period = T_on / (T_on + T_off)**

![](https://i.imgur.com/Zp5b5Bl.png)

Duty cycle is also known as the pulse width. Modulation means varying some property to add information to a signal. Putting it together you get the name: **Pulse Width Modulation**.

Other important properties are the Peak Voltage & PWM Frequency. These are also important to getting the correct output or action from a PWM Signal, however we generally do not vary them over time within the same signal, ie we don't modulate them.

### PWM Signalling

A PWM Signal is a digital signal that emulates an anlog signal hence acheiving many benefits of both of them

1. PWM Signals can vary continuously just like normal analog signals, and unlike digital signals.
2. Digital signals have higher tolerance for noise, as it doesnt matter whether the high voltage varies, only that it is 1) above a certain threshold and 2) the edges of the signal are still distinguishable.
3. Digital signals are much easier to generate, just connect to Vcc or GND, while analog signals require complex ICs to generate (DACs). Theyre also much easier to amplify for high power uses.

Thus many devices will use PWM signals to send or receive analog information. The most commonly used of such devices are RC Servos. The desired target angle is sent from the microcontroller as a PWM signal, with a certain duty cycle corresponding to the minimum angle, and another corresponding to the maximum angle, with everything else in between.

### PWM Powering

The Duty Cycle directly relates to the average voltage, and due to Ohms Law, also relates to the average current and average power. In fact it relates very simply, **Average Voltage = Duty Cycle * Peak Voltage**

![](https://i.imgur.com/pFmItvU.png)

Thus PWM is useful when you need to control the power going into some output load, like a motor or an LED. Of course the voltage and power into the load aren't actually equal to the average voltage, you can either make the PWM period small enough that you don't notice the switching. OR some kind of output loads will actually smooth out the voltage/current for you, because they physically cannot turn on/off fast enough (like LEDs or motors again).

---

## Generating PWM Signals

Timers in microcontrollers, especially STM32, can do just about anything to do with time, time-varying signals and even counting internal or external signals/events. More will be covered in the advanced tutorials. What we are interested in specifically is the Output Compare Mode.

Simply put, the timer will count up at a specific frequency. The value of the counter is then compared to **The Output Compare Value** and if the counter is less than the compare value, a high signal is output, and if it is greater than the compare value, a low signal is output. Hence the compare value controls the *PWM Duty Cycle*. 

The value of the counter wraps around when it hits **The Auto Reload Value**, so that the output periodically repeats, this is the value that controls the *PWM Frequency*.

![](https://i.imgur.com/kovNh8F.png)

It is important to note that a single timer has 4 output compare channels, that share the prescaler and auto-reload values but have independent output-compare values.

### The Maths

Internally all microcontrollers have a system clock, this provides the central time-keeping and synchronization for all aspects of the MCU, including the timers. This system core clock is 72MHz in the STM32F103 MCU used on your mainboard, and can be up to 200-400MHz in higher end MCUs. This is by far too high a frequency to be counting at, since there is a limit to how high they can count (usually 16bits=65535), which limits how low we can make the PWM Frequency.

We use a prescaler to reduce the counting frequency of the timer. The equation is:

**p = c/f_t - 1**

where **c** is the clock rate, f_t is the desired counting frequency, and **p** is the prescaler value

Then the auto-reload value is set according to the desired pwm frequency **f_p**

**a = f_t/f_p**

You may have noticed there are many combinations of prescaler and auto-reload value that give the desired pwm frequency. You will generally want to maximise the counting frequency as that will give the highest resolution for varying the duty cycle of the PWM signal.

Finally the output compare value **OC** controls the duty cycle through the very simple formula:

**Duty Cycle = Output Compare / Auto-Reload**

---

### Task 1 (30pts)

Suppose that we want to control a servo using PWM. We know that the signal must have a frequency of 50Hz, and that the servo can recognize a difference in on-time of 4us.

**1.** What is the correct timer frequency? *(5pts)*

**2.** What is the required prescaler value? *(5pts)*

**3.** What is the correct auto-reload value? *(5pts)*

Now assume the servo could recognize an infinitesimally small difference in on-time. So we would like to generate a PWM signal with as high as possible resolution to take advantage of this fact

**4.** What is the correct auto-reload value and prescaler? *(10pts)*

**5.** What is the timer frequency? *(5pts)*

---

## Servo Control

RC Servos take a PWM signal as an input and use the on time of the signal as an analog value telling it the target angle to turn to. Individual servos may differ slightly on the parameters of the PWM signal however the major convention is as follows:

1. PWM Frequency of 50Hz
2. Midpoint is 1.5ms on-time
3. Leftmost position is 0.9ms and Rightmost position is 2.1ms

### The Servo Control Library ``(pwm.c/.h)``

The 3 defines `SERVO1`, `SERVO2`, `SERVO3` refer to the 3 servo ports on the board for the purposes of this library, they have the type const ServoPort*.

    //Definition
    void servo_init(const ServoPort* servo, u16 prescaler, u16 autoreload, u16 initial);
    //example usage:
    servo_init(SERVO1, 100, 100, 0);

The function `servo_init(...)` will initialize all the hardware related to a single servo port. This mainly includes the Timer used to generate the PWM frequency, the Output Compare used to generate the PWM output signal and the pins to output the signal. 

It takes a prescaler and autoreload value to customize the PWM frequency and an initial on time value. 

Keep in mind that every servo port shares the same internal timer, so if you call servo_init multiple times with different prescaler and autoreload it will change to the newest one, this may cause problems.

    //Definition
    void servo_control(const ServoPort* servo, u16 position);
    //example usage:
    servo_control(SERVO1, 50);

This simply changes the on-time value of the PWM output of the given servo port, effective immediately. While the parameter is named `position` it does not actually equal to the real world position (dont pass in 180 and expect it to move to the other side). It takes the on time in terms of timer counts (depends on prescaler)

---

### Redownload the Project ZIP file

in the sidebar find the file dma.c, right click and remove file from project
open camera.c, and remove the line `include "dma.h"`

open configure flash tools, redo whatever is needed from Tutorial 1
 - external programmer
 - flash.bat
 - your COM Port ID

### Task 2 (40pts)

***Always*** verify the signal using an oscilloscope with the help of a tutor first, then try it on a servo motor if available.

**1.** Initialize the Servo port using the library with the correct PWM Frequency and an initial position of the midpoint (on-time = 1.5ms) *[10 pts]*

**2.** Now you will have to create a more complex program to move the Servo over time and in response to button inputs. *[30 pts]*

a. Initialize the servo at the leftmost position *[5 pts]*

b. Change the servo position over time such that it reaches the rightmost position in *exactly 1 second* *[10 pts]*

c. Similarly, move the arm back to the leftmost position in 1 second *[10 pts]*

d. Wait at the leftmost position until BUTTON1 is pressed then repeat steps **a & b** *[5 pts]*

---

## Motor Control

PWM is used to control the power going into a motor, because it requires high voltage and high current we use transistors to amplify the signal from the MCU. A transistor is essentially a switch that is electrically controlled rather than mechanically.

Additionally to adjust the direction of the motor, we must switch which terminal of the motor is positive and which is negative. This is achieved by a circuit known as a H-Bridge.

![](https://i.imgur.com/KAMZUIK.png)
![](https://i.imgur.com/xA2IoDB.png)

Selecting the PWM frequency requires you to consider a few factors. Without going deep into the mechanical or hardware aspects the factors are:

1. MOSFET transistors (most commonly used for motor drivers) consume energy while switching from on to off or back, but not while constantly on/off. So **higher PWM Frequency reduces efficiency** and heats up the motor driver
2. Current slowly increases within motors when given voltage. If PWM frequency is too high the motor will not have enough time to build up to high enough power. So **higher PWM Frequency reduces power and torque** and the relationship between speed and voltage becomes more nonlinear.
3. The switching of power by PWM in the MOSFETs and Motors creates a noise at the frequency of the PWM and all multiples of it. So **higher PWM Frequency reduces noise** by pushing it out of the audible range
4. Increasing the PWM frequency smoothens the current in the motors and **reduces jitteriness in the rotation**

Putting all of these together the common range for PWM frequency is 5-10kHz.

### The Motor Control Library
    
The 3 defines `MOTOR1`, `MOTOR2` and `MOTOR3` can be used to refer to each of the 3 motor ports on the mainboard, they have type const MotorPort*.

    //definition
    void motor_init(const MotorPort* motor, u16 prescaler, u16 autoreload，u16 magnitude, u8 direction);
    //exmaple usage
    motor_init(MOTOR1, 72, 200);

`motor_init` works similar to `servo_init`, taking 2 initialization parameters, `magnitude` and `direction`

    //definition
    void motor_control(const MotorPort* motor, u16 magnitude, u8 direction);
    //example usage
    motor_control(MOTOR1, 100, 1);
    
`motor_control` work similar to `servo_control` except you can also control the direction pin on the motor port

---

### Task 3 (30pts)

1. Initialize the motor port and timer with a PWM Frequency of 5kHz and a suitable Timer frequency *[5pts]*

2. Each time BUTTON1 is pressed, increase duty cycle by 10%, and each time BUTTON2 is pressed, decrease duty cycle by 10% *[10pts]*

3. Extend the program to work such that -10% is equivalent to 10% duty cycle with a reverse direction. *[5pts]*

4. Extend the program to work such that button presses change the final value just like the previous parts, but only changes the duty cycle at a rate of 10% per second. [10pts] ie. if i click BUTTON1 twice it will increase by 20% in 2 seconds.

---

Anshuman Medhi - amedhi@connect.ust.hk - 68925193

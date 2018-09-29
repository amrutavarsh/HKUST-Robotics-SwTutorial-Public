# Tutorial #2 - Homework

## Trajectory generation

In motor control, the time varying nature of the position, velocity and acceleration (and any further derivatives) is known as a trajectory, generating the trajectory is known as motion planning. This trajectories must account for the physical limitations of the motor and robot. This homework will involve you generating various trajectories to test your logical, mathematical and pwm skills.

It is obvious that we cannot change position instantly, so we apply a constant velocity over time that results in the final position. However in fact, in real life we cannot instantly apply a velocity either, we must apply a constant acceleration to reach that velocity, and a constant decceleration to stop again. This is known as a trapezoidal velocity trajectory

![](https://i.imgur.com/jnmSdTP.png)

---

**Your task** is to write a program that given a `final_position` (in cm), `max_velocity` (cm/s) and `max_acceleration` (cm/s^2) as global variables will calculate and generate a trapezoidal velocity trajectory in PWM, that limits the acceleration, velocity and reaches the final position. *(60pts)*

The trajectory starts everytime you click any button, you must ignore all button presses until it finishes.

**assume that the percentage duty cycle is exactly equal to the resulting velocity in m/s**, ie 50% duty cycle is 50m/s, 100% -> 100m/s etc.

You should update the PWM value every 10ms.

This should work in both directions, with -ve values meaning moving backwards.

*Hint:* The distance travelled at constant acceleration is `s = 0.5*a*t^2`.

You should test and demo your program on an oscilloscope

---

## Pretty colors

Another common use of PWM is to control the brightness and color of LEDs. Using PWM we can control the average voltage applied to the LED, and thus we can control the brightness. Additionally multicolor LEDs have multiple pins where the voltage on each of them control the brightness of a different color that gets mixed to produce a wide range colors.

![](https://i.imgur.com/lf5N8Xu.png)

We will provide a board that has a ring of multicolor LEDs that can be controlled together to produce various colors. We use this to control the lighting of our camera setting, you will use it to make a pretty light show :) (we use it for this sometimes too)

---

**Your task** is to make the color of the LEDs smoothly vary from red to green to blue and then back to red, passing through all other colors on the way. One cycle should take 3 seconds. Clicking `BUTTON1` should make the cycle move in reverse

The LED board should be connected to the 3 servo ports.

You may test the program using oscilloscopes in the lab and finally demo it on the RGB ring board.

### Detailed Steps

1. Make the brightness of the LEDs linearly increase and decrease in a cycle, taking into account that brightness varies with the square of voltage, not directly. *(20pts)*

![](https://i.imgur.com/g1e5Dxv.png)


2. Cycle through the 3 color channels applying the increasing and decreasing brightness to each color in turns, only one color should be on at a time *(20pts)*

![](https://i.imgur.com/slA56cl.png)


3. Cycle through the 3 color channels applying the increasing and decreasing brightness but with 2 colors on at a time, such that while one color is increasing, the next is decreasing, and the 3rd is off. *(20pts)*

![](https://i.imgur.com/5CqEV5d.png)

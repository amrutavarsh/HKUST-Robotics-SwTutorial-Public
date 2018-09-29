# Tutorial #2 - Homework

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

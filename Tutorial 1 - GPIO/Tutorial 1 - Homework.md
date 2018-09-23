# GPIO Homework

**Note:** Finish your homework and demonstrate the program in CYT Rm3007B to any of the software seniors before your next tutorial start.

**Construct a program that contains different modes and fulfills the following requirments:**

#### Normal Mode [60 pts]
- When BUTTON1 is pressed, switch off the current LED and switch on another LED (e.g. [LED1]->[LED2] or [LED2]->[LED1]), the LED that is on is called the selected LED ***[10 pts]***

- When BUTTON1 is held(continuously pressed for 500+ ms), LEDs light up alternatively with an inteval of 300ms (e.g. [LED1]->[LED2]->[LED1]...), stop when BUTTON1 is released and the currently on LED is the selected LED ***[20 pts]***

- When BUTTON2 or BUTTON3 is pressed while BUTTON1 is held, pause the above lighting procedure, resume the procedure when back to only BUTTON1 is held ***[20 pts]***

- When all three buttons are held for 500ms, the buzzer beep once for 100ms ***[20 pts]***

#### Special Mode [40 pts]
- When a button is pressed twice within 300ms, it is considered as a double click
- If BUTTON2 is double-clicked, enter Special Mode and turn off all LEDs ***[20 pts]***
- Buttons will perform the following functions: ***[10 pts]***
  - when **ONLY** BUTTON1 is pressed, LED1 turns on
  - when **ONLY** BUTTON2 is pressed, LED2 turns on
  - when **ONLY** BUTTON3 is pressed, buzzer beeps
- If BUTTON2 double-clicked again, switch back to Normal Mode and the selected LED should be on ***[10 pts]***

#### Bonus Mode [80 pts]
  - In Normal Mode, when all three buttons are held for 500ms, enter Bonus Mode
  - the sequence of the buttons been pressed is set as the password for exiting Bonus Mode ***[20 pts]***
    - i.e. If the sequence is [BUTTON1]->[BUTTON2]->[BUTTON3] when entering Bonus Mode, the same sequence should be perform in order to exit Bonus mode, other sequence will not work
    
    
  - Buttons perform no function in Bonus Mode ***[10 pts]***
  
  
  - Choose either one of the following:
    1. LED Flashing ***[10 pts]***
        - The selected LED flashes with a 300ms interval
        
    2. LED Flashing with pattern ***[40 pts]***
        - The pattern is based on the password
        - e.g. If the sequence is [BUTTON**3**]->[BUTTON**1**]->[BUTTON**2**], the selected LED flash **thrice**, then **once**, then **twice**, then flashes with a 300ms interval
        - A walk through example after entering Bonus Mode with the sequence above
          1. LED turns off for 1000ms
          2. LED flashes thrice with a 100ms interval
          3. LED turn off for 500ms
          4. LED flashes once with a 100ms interval
          5. LED turn off for 500ms
          6. LED flashes twice with a 100ms interval
          7. LED turn off for 500ms
          8. LED flashes with a 300ms interval
        - By pressing any of the three buttons, the whole process above will restart again


**Remark:**
- The Bonus Mode is an optional task. You should finish the Normal Mode and Special Mode before challenging yourself. **No mark** will be given in Bonus Mode if you haven't completed the above modes.
- There is two task in Bonus Mode, which they shouldn't be coexist. Thus, you can only choose to do either one of the task in a single demonstration.
- Task 1 is easier than Task 2, you should choose to do which task base on your ability.

**Modification of Homework**
21/09/2018 (Clarification)
- "When BUTTON1 is pressed, LED1 turns on" -> "[**ONLY**] when BUTTON1 is pressed, LED1 turns on"
- "When BUTTON2 is pressed, LED2 turns on" -> "[**ONLY**] when BUTTON2 is pressed, LED2 turns on"
- "When BUTTON3 is pressed, buzzer [start beeping]" -> "[**ONLY**] when BUTTON2 is pressed, buzzer [beeps]"
- "When all three buttons are held for 500ms, enter Bonus Mode" -> "[In Normal Mode, ]when all three buttons are held for 500ms, enter Bonus Mode"

[]: part where is modified

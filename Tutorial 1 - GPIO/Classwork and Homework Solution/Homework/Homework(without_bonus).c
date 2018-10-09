/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Homework (without bonus)
 *
 *	Author  : Joseph Lam
 *	Contact : mhlamaf@connect.ust.hk
 *
 *	Please rename the file name to "main.c" before copying the file to the project
 *	or you can copy and paste the content to the original "main.c" file in the project
 */

#include "main.h"

// Include Required Library Headers Here
#include "rcc.h"
#include "ticks.h"
#include "leds.h"
#include "buzzer.h"
#include "buttons.h"

// a enum that represent different modes
typedef enum {
	NORMAL = 0,
	SPECIAL
} MODE;

LED selectedLED = LED1;  // variable that remember the selected LED

void switchLED(void); // a 

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	leds_init();
	buzzer_init();
	buttons_init();

	led_on(selectedLED);  // turn on the default selected LED

	MODE mode = NORMAL;  // variable that remember the current mode
	u32 btn[3] = {0, 0, 0}; // debounce variable which also remember the button press time
	u32 lastBtn2Ticks = 0;  // variable that remember the last BUTTON2 press time
	u32 last_switch_led_ticks = 0;  // remember the last switch LED time, when BUTTON1 is holding
	u32 buzzer_ticks = 0;  // remember when the buzzer start beep
	u8 allBtnRelease = 0;  // debounce variable for three button press together

	while (1) {
		static u32 this_ticks = 0;
		while (get_ticks() == this_ticks);
		this_ticks = get_ticks();

		static u32 last_led_ticks=0;
		if ((this_ticks - last_led_ticks) >= 25) {
			// get all the button input first
			u8 btn1State = button_pressed(BUTTON1);
			u8 btn2State = button_pressed(BUTTON2);
			u8 btn3State = button_pressed(BUTTON3);

			// Do you remember the Finite State Machine(FSM) concept\?
			// using switch and cases is a way to implement FSM
			switch (mode) {
				case NORMAL:  // Normal mode
					// if you remember, elements in an enum are basically an integer
					// so we can also use the elements inside enum for indexing in array
					if (!btn1State && btn[BUTTON1]) btn[BUTTON1] = 0;
					if (btn1State && !btn[BUTTON1]) {
						btn[BUTTON1] = this_ticks;
						switchLED(); // switch the LEDs
					} else if (btn1State && btn[BUTTON1]) {
						if (this_ticks - btn[BUTTON1] >= 500            // if BUTTON1 is hold for 500ms
							&& this_ticks - last_switch_led_ticks >= 300  // and last switching ticks is over 300ms
							&& !btn2State && !btn3State) {                // and both BUTTON2 and BUTTON3 is not pressed
							switchLED();  // switch the LEDs
							last_switch_led_ticks = this_ticks;
						}
					}

					if (!btn2State && btn[BUTTON2]) btn[BUTTON2] = 0;
					if (btn2State && !btn[BUTTON2]) {
						btn[BUTTON2] = this_ticks;
						if (this_ticks - lastBtn2Ticks <= 300) {  // when a double click happens
							mode = SPECIAL;  // change the mode to SPECIAL mode
							led_off(selectedLED);  // turn off the selected LED
						} else {
							lastBtn2Ticks = this_ticks;
						}
					}

					if (!btn3State && btn[BUTTON3]) btn[BUTTON3] = 0;
					if (btn3State && !btn[BUTTON3])
						btn[BUTTON3] = this_ticks;

					// if every button is released, reset the debounce variable
					if (!btn1State && !btn1State && !btn1State && allBtnRelease) allBtnRelease = 0;
					if (btn[BUTTON1] && btn[BUTTON2] && btn[BUTTON3]  // if all three buttons is pressed
						&& this_ticks - btn[BUTTON1] >= 500             // and all of them are holded over 500ms
						&& this_ticks - btn[BUTTON3] >= 500
						&& this_ticks - btn[BUTTON3] >= 500
						&& !allBtnRelease) {                            // and the debounce variable is 0
						buzzer_on();  // turn on the buzzer
						buzzer_ticks = this_ticks;  // remember when the buzzer is on
						allBtnRelease = 1;
					}
					break;

				case SPECIAL:  // Special mode
					if (!btn1State && btn[BUTTON1]) {
						led_off(LED1);
						btn[BUTTON1] = 0;
					}
					
					if (!btn2State && btn[BUTTON2]) {
						led_off(LED2);
						btn[BUTTON2] = 0;
					}

					if (!btn3State && btn[BUTTON3]) {
						buzzer_off();
						btn[BUTTON3] = 0;
					}
					
					// if no button is pressed
					if (!btn[BUTTON1] && !btn[BUTTON2] && !btn[BUTTON3]) {
						if (btn1State && !btn[BUTTON1]) {
							led_on(LED1);
							btn[BUTTON1] = this_ticks;
						}

						if (btn2State && !btn[BUTTON2]) {
							btn[BUTTON2] = this_ticks;

							// if double click happen, switch back to Normal mode
							if (this_ticks - lastBtn2Ticks <= 300) {
								mode = NORMAL;
								led_on(selectedLED);  // turn on the selected LED
							} else {
								led_on(LED2);
								lastBtn2Ticks = this_ticks;
							}
						}
						
						if (btn3State && !btn[BUTTON3]) {
							buzzer_on();
							btn[BUTTON3] = this_ticks;
						}
					}
					break;
			}

			if (buzzer_ticks && this_ticks - buzzer_ticks >= 100) {
				buzzer_off();
				buzzer_ticks = 0;
			}

			last_led_ticks = this_ticks;
		}
	}
}

// a helper function that help switch the LED
void switchLED(void) {
	led_off(selectedLED);

	if (selectedLED == LED1)
		selectedLED = LED2;
	else
		selectedLED = LED1;

	led_on(selectedLED);
}

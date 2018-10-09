/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 3.1
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
#include "buttons.h"

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	leds_init();
	buttons_init();
	
	u8 btn1 = 0, btn2 = 0, btn3 = 0;  // debounce variables that remember if the button is pressed or not
	
	while (1) {
		static u32 this_ticks = 0;
		while (get_ticks() == this_ticks);
		this_ticks = get_ticks();

		static u32 last_led_ticks=0;
		if ((this_ticks - last_led_ticks) >= 25) {
			// get all the state of button first
			u8 btn1State = button_pressed(BUTTON1);
			u8 btn2State = button_pressed(BUTTON2);
			u8 btn3State = button_pressed(BUTTON3);
			
			// BUTTON1 Event
			if (btn1State && !btn1) {  // if the button is pressed
				btn1 = 1;
				led_on(LED1);          // turn on the LED
			}
			if (!btn1State && btn1) {  // if the button is released
				btn1 = 0;
				led_off(LED1);         // turn off the LED
			}
			
			// the logic of BUTTON2 and BUTTON3 are more or less the same,
			// so I won't explain the detail of it
			//BUTTON2 Event
			if (!btn2State && btn2) {
				btn2 = 0;
				led_off(LED2);
			}
			if (btn2State && !btn2) {
				btn2 = 1;
				led_on(LED2);
			}

			// BUTTON3 Event
			if (btn3State && !btn3) {
				btn3 = 1;
				led_on(LED1);
				led_on(LED2);
			}
			if (!btn3State && btn3) {
				btn3 = 0;
				led_off(LED1);
				led_off(LED2);
			}
			
			last_led_ticks = this_ticks;
		}
	}
}

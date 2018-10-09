/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 3.3
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

u8 led1 = 0, led2 = 0;     // variables remember the current state of LEDs
void led_toggle(LED led);  // a declaration of the led toggle function

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	leds_init();
	buttons_init();
	
	u8 btn1 = 0, btn2 = 0, btn3 = 0;  // variables that remember if the button is pressed or not
	
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
			
			if (!btn1State && btn1) btn1 = 0;
			if (!btn2State && btn2) btn2 = 0;
			if (!btn3State && btn3) btn3 = 0;
			
			if (btn1State && !btn1) {  // if the button is pressed
				btn1 = 1;
				led_toggle(LED1);        // toggle the LED
			}
			
			if (btn2State && !btn2) {
				btn2 = 1;
				led_toggle(LED2);
			}
			
			if (btn3State && !btn3) {
				btn3 = 1;
				led_toggle(LED1);
				led_toggle(LED2);
			}
			
			last_led_ticks = this_ticks;
		}
	}
}

void led_toggle(LED led) {  // a function that toggle the required LED
	if (led == LED1) {
		if (led1) {
			led1 = 0;
			led_off(LED1);
		} else {
			led1 = 1;
			led_on(LED1);
		}
	} else {
		if (led2) {
			led2 = 0;
			led_off(LED2);
		} else {
			led2 = 1;
			led_on(LED2);
		}
	}
}

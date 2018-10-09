/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 1
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

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	leds_init();
	
	LED currentLED = LED1; // a variable that store the LED that is currently on
	u8 isLEDon = 1;        // a variable that store if the LED is on
	led_on(currentLED);    // turn on that LED first
	
	while (1) {
		static u32 this_ticks = 0;
		while (get_ticks() == this_ticks);
		this_ticks = get_ticks();

		static u32 last_led_ticks=0;
		if ((this_ticks - last_led_ticks) >= 500) { // the LEDs will alternate with an inteval of 500ms
			if (isLEDon) {
				led_off(currentLED);
				isLEDon = 0;
				
				// alternate the leds
				if (currentLED == LED1)
					currentLED = LED2;
				else
					currentLED = LED1;
				
			} else {
				led_on(currentLED);
				isLEDon = 1;
			}
			
			last_led_ticks = this_ticks;
		}
	}
}

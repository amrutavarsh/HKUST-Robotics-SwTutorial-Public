/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 3.5
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
#include "buzzer.h"
#include "buttons.h"

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	buzzer_init();
	buttons_init();
	
	u8 beep = 0;
	
	while (1) {
		static u32 this_ticks = 0;
		while (get_ticks() == this_ticks);
		this_ticks = get_ticks();

		static u32 last_led_ticks=0;
		if ((this_ticks - last_led_ticks) >= 25) {
			// as it will enter a while loop if any button is pressed, so there is no need to implement debounce
			// if BUTTONx is pressed, set beep to x
			if (button_pressed(BUTTON1)) beep = 1;
			if (button_pressed(BUTTON2)) beep = 2;
			if (button_pressed(BUTTON3)) beep = 3;
			
			// if beep is not zero, enter the beep while loop
			// this while loop also prevent the program reading other button input while beeping
			u32 beep_ticks = this_ticks;
			while(beep) {
				buzzer_on();
				// a 300ms delay, we can't use this_ticks as this_ticks is not updated in this while loop
				while (get_ticks() - beep_ticks < 300);
				beep_ticks = get_ticks();  // reset beep_ticks to current ticks
				
				buzzer_off();
				beep--;  // since we beep once, beep variable decrement by 1
				if (!beep) break;  // if there is no beep left, there is no point to wait for another 300ms delay, so just break the loop
				// another 300ms delay
				while (get_ticks() - beep_ticks < 300);
				beep_ticks = get_ticks();
			}
			
			last_led_ticks = this_ticks;
		}
	}
}

/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 2
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

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	buzzer_init();
	
	// as the question just ask you to beep twice,
	// there is no purpose to have a while(1) infinite loop here
	
	u32 last_ticks = get_ticks();
	
	// a for-loop that make buzzer beeps twice
	for (u8 i = 0; i < 2; ++i) {
		if (i) while (get_ticks() - last_ticks < 500);  // 500 ms delay, but if it is the first beep(i=0), there should be no delay
		buzzer_on();
		last_ticks = get_ticks();

		while (get_ticks() - last_ticks < 300);  // 300 ms delay
		buzzer_off();
		last_ticks = get_ticks();
	}
}

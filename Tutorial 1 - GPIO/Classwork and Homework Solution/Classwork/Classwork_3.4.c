/*	
 *	UST Robotics Team Internal 2018
 *
 *  Author  : Anshuman Medhi
 *  Contact : amedhi@connect.ust.hk 
 *						68925193
 *
 *
 *	HKUST Robotics Team Softwart Tutorial 1
 *	Classwork 3.4
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

u8 led1 = 0, led2 = 0;     // variables remember the current state of LEDs
void led_toggle(LED led);  // a declaration of the led toggle function

int main() {
	// this is the set-up of the program, including init all the required stuff
	rcc_init();
	ticks_init();
	leds_init();
	buzzer_init();
	buttons_init();
	
	u8 btn1 = 0, btn2 = 0, btn3 = 0;  // variables that remember if the button is pressed or not
	u32 btn1Ticks = 0, btn2Ticks = 0, btn3Ticks = 0;  // variables that remember the time of last button press
	u32 led1FlashTicks = 0, led2FlashTicks = 0;  // variables that remember whether LED is flashing and when is the last flash
	u32 buzzerTicks = 0;  // variable that remember whether buzzer is beeping and when it starts to beep

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
			
			// BUTTON1 event
			if (btn1State && !btn1) {  // if the button is pressed
				btn1 = 1;
				if (!led1FlashTicks)
					led_toggle(LED1);        // toggle the LED
				
				// if button pressed of last time and this time is less than or equal to 300ms
				// it is considered as a double click
				if (this_ticks - btn1Ticks <= 300) {
					buzzer_on();
					buzzerTicks = this_ticks;  // remember when the buzzer start beeping
					
					if (led1FlashTicks)             // if LED1 is flashing
						led1FlashTicks = 0;           // turn the flashing off
					else
						led1FlashTicks = this_ticks;  // otherwise start flashing
					
				} else {
					btn1Ticks = this_ticks;  // if it is not a double click, remember the current button press time
				}
			}
			
			// BUTTON2 event
			if (btn2State && !btn2) {
				btn2 = 1;
				if (!led2FlashTicks)
					led_toggle(LED2);
				
				if (this_ticks - btn2Ticks <= 300) {
					buzzer_on();
					buzzerTicks = this_ticks;
					
					if (led2FlashTicks)
						led2FlashTicks = 0;
					else
						led2FlashTicks = this_ticks;
					
				} else {
					btn2Ticks = this_ticks;
				}
			}
			
			// BUTTON3 event
			if (btn3State && !btn3) {
				btn3 = 1;
				if (!led1FlashTicks)
					led_toggle(LED1);
				if (!led2FlashTicks)
					led_toggle(LED2);
				
				if (this_ticks - btn3Ticks <= 300) {
					buzzer_on();
					buzzerTicks = this_ticks;
					
					if (led1FlashTicks)
						led1FlashTicks = 0;
					else
						led1FlashTicks = this_ticks;
					
					if (led2FlashTicks)
						led2FlashTicks = 0;
					else
						led2FlashTicks = this_ticks;
				} else {
					btn3Ticks = this_ticks;
				}
			}
			
			// flash LED1 if it is in flashing mode every 300ms
			if (led1FlashTicks && this_ticks - led1FlashTicks >= 300) {
				led_toggle(LED1);
				led1FlashTicks = this_ticks;
			}
			
			// flash LED2 if it is in flashing mode every 300ms
			if (led2FlashTicks && this_ticks - led2FlashTicks >= 300) {
				led_toggle(LED2);
				led2FlashTicks = this_ticks;
			}
			
			// if buzzer is beeping and beeps over 100ms
			if (buzzerTicks && this_ticks - buzzerTicks >= 100) {
				buzzer_off();
				buzzerTicks = 0;  // remember buzzer is off now
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

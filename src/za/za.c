/*
 * Pokémon ZA automation
 */

#include <util/delay.h>

#include "automation-utils.h"
#include "user-io.h"

/* Static functions */
static void reroll_area(void);
static void area1(void);
static void area2(void);
static void area3(void);
static void area4(void);
static void area5(void);
static void area6(bool);
static void area7(void);
static void area8(void);
static void area9(void);
static void area10(void);
static void area11(void);
static void area12(void);
static void area13(void);
static void area14(void);
static void area15(void);
static void area16(void);
static void area17(void);
static void area18(void);
static void area19(void);
static void area20(void);
// void reroll_static_area(void);
static void hold_down(void);
static void reroll_teleporter(void);

static void honedge(void);

static void move_cusror(struct stick_coord, int8_t);


int main(void)
{
	init_automation();
	init_led_button();

	/* Initial beep to confirm that the buzzer works */
	beep();
	sync_controller();
	beep();

	
	for (;;) {
		/* Set the LEDs, and make sure automation is paused while in the
		   menu */
		set_leds(BOTH_LEDS);
		pause_automation();

		/* Feature selection menu */
		uint8_t count = count_button_presses(100, 900);

		for (uint8_t i = 0 ; i < count ; i += 1) {
			beep();
			_delay_ms(100);
		}
		switch(count){
			case 1:
				reroll_area();
			break;

			case 2:
				hold_down();
			break;

			case 3:
				reroll_teleporter();
			break;

			case 4:
				honedge();
			break;
			
			default:
				/* Wrong selection */
				delay(100, 200, 1500);
			break;
		}
		
	}
}

static void move_cusror(struct stick_coord direction, int8_t times){
	for (uint8_t i = 0 ; i < times; i += 1) {
		send_update(BT_NONE,	DP_NEUTRAL, direction, S_NEUTRAL);
		send_update(BT_NONE,	DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	}
}

static void hold_down(){
	for(;;){
		send_update(BT_A,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	}
}	

static void reroll_area(){
	set_leds(BOTH_LEDS);
	pause_automation();

	pause_automation();

		/* Feature selection menu */
	uint8_t count = count_button_presses(100, 900);

	for (uint8_t i = 0 ; i < count ; i += 1) {
		beep();
		_delay_ms(100);
	}
	if(count > 4) return;

	/* Feature selection menu */
	uint8_t area = count_button_presses(100, 900);

	for (uint8_t i = 0 ; i < area ; i += 1) {
		beep();
		_delay_ms(100);
	}

	if(area > 5) return;

	area += (5 * (count-1));

	bool isInitial = true;

	set_leds(BOTH_LEDS);
	for (;;) {
		
		//run to gate enterance for ~4 m more of spawns
		for (uint8_t i = 0 ; i < 20; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
		}
		pause_automation();
		_delay_ms(1100);
		
		//open map
		SEND_BUTTON_SEQUENCE(
			{ BT_P, DP_NEUTRAL,	SEQ_HOLD,	10 },	/* open map */
		);

		pause_automation();
		_delay_ms(500);


		//zoom out map to max
		if(isInitial){
			for (uint8_t i = 0 ; i < 2; i += 1) {
				send_update(BT_NONE,	DP_NEUTRAL, S_NEUTRAL, S_BOTTOM);
				pause_automation();
				_delay_ms(200);
			}
		}

		//cursor to area
		switch (area){
			case 1: 
				area1();
			break;
			case 2: 
				area2();
			break;
			case 3: 
				area3();
			break;
			case 4: 
				area4();
			break;
			case 5: 
				area5();
			break;	
			case 6: 
				area6(isInitial);
			break;
			case 7: 
				area7();
			break;
			case 8: 
				area8();
			break;
			case 9: 
				area9();
			break;
			case 10: 
				area10();
			break;
			case 11: 
				area11();
			break;
			case 12: 
				area12();
			break;
			case 13: 
				area13();
			break;
			case 14: 
				area14();
			break;
			case 15: 
				area15();
			break;
			case 16: 
				area16();
			break;
			case 17: 
				area17();
			break;
			case 18: 
				area18();
			break;
			case 19: 
				area19();
			break;
			case 20: 
				area20();
			break;
			default:
				/* Wrong selection */
				delay(100, 200, 1500);
			break;
		}
		
		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH,	10 },	/* confirm travel */
		);

		isInitial = false;
		pause_automation();
		_delay_ms(4050);
	}

}

static void area1(void){
	move_cusror(S_LEFT, 4);

	move_cusror(S_BOTTOM, 1);
}

static void area2(void){
	move_cusror(S_TOP, 3);
}

static void area3(void){
	move_cusror(S_TOP, 1);
}

static void area4(void){
	move_cusror(S_RIGHT, 3);
}

static void area5(void){
	move_cusror(S_TOP, 3);

	move_cusror(S_RIGHT, 1);
}

static void area6(bool isInitial){
	if(isInitial){
		move_cusror(S_RIGHT, 1);

		move_cusror(S_TOP, 5);

		move_cusror(S_LEFT, 1);
	}
	else{
		move_cusror(S_TOP, 2);

		move_cusror(S_RIGHT, 1);
	}	
}

static void area7(void){
	move_cusror(S_LEFT, 2);

	move_cusror(S_TOP, 1);
}

static void area8(void){
	move_cusror(S_LEFT, 2);

	move_cusror(S_BOTTOM, 1);
}

static void area9(void){

}

static void area10(void){
	move_cusror(S_RIGHT, 2);

	move_cusror(S_TOP, 1);
}

static void area11(void){
	move_cusror(S_LEFT, 5);
	move_cusror(S_TOP, 2);
}

static void area12(void){

}

static void area13(void){
	move_cusror(S_LEFT,3);

	move_cusror(S_BOTTOM, 1);
}

static void area14(void){
	move_cusror(S_LEFT, 1);

	move_cusror(S_BOTTOM, 2);
}

static void area15(void){
	move_cusror(S_RIGHT, 2);

	move_cusror(S_BOTTOM, 2);
}

static void area16(void){

}

static void area17(void){
	
}

static void area18(void){
	move_cusror(S_LEFT, 1);

	move_cusror(S_BOTTOM, 1);
}

static void area19(void){
	move_cusror(S_BOTTOM, 2);

	move_cusror(S_LEFT, 1);
}

static void area20(void){

}

static void reroll_teleporter(void){
	for(;;){
		SEND_BUTTON_SEQUENCE(
			{ BT_A,		DP_NEUTRAL,	SEQ_MASH,	5 }
		);
	}
}

static void honedge(void){
	for(;;){
		for (uint8_t i = 0 ; i < 65; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
		}
		for (uint8_t i = 0 ; i < 73; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
		}
		SEND_BUTTON_SEQUENCE(
				{ BT_A,		DP_NEUTRAL,	SEQ_MASH,	5 }
		);
		pause_automation();
		_delay_ms(2500);
		SEND_BUTTON_SEQUENCE(
				{ BT_A,		DP_NEUTRAL,	SEQ_MASH,	5 }
		);
		pause_automation();
		_delay_ms(2500);
	}
}

// void reroll_static_area(){
// 	for (;;) {
// 		SEND_BUTTON_SEQUENCE(
// 			{ BT_P, DP_NEUTRAL,	SEQ_HOLD,	10 },	/* open map */
// 		);
// 		pause_automation();
// 		for (uint8_t i = 0 ; i < 3 ; i += 1) {
// 			send_update(BT_NONE,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
// 		}
// 		send_update(BT_NONE,	DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
// 		for (uint8_t i = 0 ; i < 3 ; i += 1) {
// 			send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
// 		}
// 		send_update(BT_NONE,	DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
// 		SEND_BUTTON_SEQUENCE(
// 			{ BT_A, DP_NEUTRAL,	SEQ_MASH,	10 },	/* confirm travel */
// 		);
// 		pause_automation();
// 		_delay_ms(4050);
// 	}
// }
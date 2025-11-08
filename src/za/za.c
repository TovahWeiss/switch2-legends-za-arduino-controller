/*
 * Pokémon ZA automation
 */

#include <util/delay.h>

#include <math.h>

#include "automation-utils.h"
#include "user-io.h"

/* Static functions */
static void open_map(bool);
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
static void area16(bool);
static void area17(void);
static void area18(void);
static void area19(void);
static void area20(void);
static void hold_down(void);
static void reroll_teleporter(void);
static void bench_reset(void);
static void honedge(void);
static void move_cursor(struct stick_coord, int8_t);
static void sewers(void);
static void warp_to_sewer_enterance(void);
static void sewer_1(void);
static void sewer_2(void);
static void bench_to_drampa(void);
static void drampa_to_bench(void);
static void smart_drampa(void);
static void bench_reset_alpha_exploit(void);
static void helioptile(void);
static void indiv_menu(void);

//utility
static void run_units(struct stick_coord direction, int16_t units, bool isRunningAlready){
	double units_per_cycle = 2.941176470588235;
	uint16_t cycles = (int) lround(units_per_cycle * (double) units);
	enum button_state run = BT_B;
	if(isRunningAlready){
		run = BT_NONE;
	}

	for(uint16_t i = 0; i < cycles; i+=1){
		send_update(run, DP_NEUTRAL, direction, S_NEUTRAL);
	}
}

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
				bench_reset();
			break;

			case 5:
				indiv_menu();
			break;

			case 6: 
				sewers();
			break;

			case 7:
				bench_reset_alpha_exploit();
			break;
					
			default:
				/* Wrong selection */
				delay(100, 200, 1500);
			break;
		}
		
	}
}

static void move_cursor(struct stick_coord direction, int8_t times){
	for (uint8_t i = 0 ; i < times; i += 1) {
		send_update(BT_NONE,	DP_NEUTRAL, direction, S_NEUTRAL);
		send_update(BT_NONE,	DP_NEUTRAL, S_NEUTRAL, S_NEUTRAL);
	}
}

static void hold_down(){
	for(;;){
		send_update(BT_A,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
		send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	}
}	

static void reroll_area(){
	set_leds(BOTH_LEDS);
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
		
		//run to gate enterance for ~8 m more of spawns
		if(area != 6){
			run_units(S_TOP, 8, false);
			pause_automation();
			_delay_ms(900);
		}
	
		open_map(isInitial);

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
				area16(isInitial);
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

static void helioptile(void){
	bool isInitial = true;

	for(;;){
		run_units(S_TOP, 8, false);
		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH,	4 },	/* confirm travel */
		);
		pause_automation();
		_delay_ms(1800);
		
		run_units(S_TOP, 20, false);
		pause_automation();
		_delay_ms(1000);
		

		run_units(S_BOTTOM, 20, false);
		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH,	10 },	/* confirm travel */
		);
		
		pause_automation();
		_delay_ms(2000);

		open_map(isInitial);
		
		area14();

		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH,	10 },	/* confirm travel */
		);

		isInitial = false;
		pause_automation();
		_delay_ms(4050);
	}
}

static void open_map(bool isInitial){
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
}

static void area1(void){
	move_cursor(S_LEFT, 4);

	move_cursor(S_BOTTOM, 1);
}

static void area2(void){
	move_cursor(S_TOP, 3);
}

static void area3(void){
	move_cursor(S_TOP, 1);
}

static void area4(void){
	move_cursor(S_RIGHT, 3);
}

static void area5(void){
	move_cursor(S_TOP, 3);

	move_cursor(S_RIGHT, 1);
}

static void area6(bool isInitial){
	if(isInitial){
		move_cursor(S_RIGHT, 1);

		move_cursor(S_TOP, 5);

		move_cursor(S_LEFT, 1);
	}
	else{
		for (uint8_t i = 0 ; i < 2; i += 1) {
			send_update(BT_NONE,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
		}

		move_cursor(S_RIGHT, 1);
	}	
}

static void area7(void){
	move_cursor(S_LEFT, 2);

	move_cursor(S_TOP, 1);
}

static void area8(void){
	move_cursor(S_LEFT, 2);

	move_cursor(S_BOTTOM, 1);
}

static void area9(void){

}

static void area10(void){
	move_cursor(S_RIGHT, 2);

	move_cursor(S_TOP, 1);
}

static void area11(void){
	move_cursor(S_LEFT, 3);
	move_cursor(S_TOP, 2);
}

static void area12(void){

}

static void area13(void){
	move_cursor(S_LEFT,3);

	move_cursor(S_BOTTOM, 1);
}

static void area14(void){
	move_cursor(S_LEFT, 1);

	move_cursor(S_BOTTOM, 2);
}

static void area15(void){
	move_cursor(S_RIGHT, 2);

	move_cursor(S_BOTTOM, 2);
}

static void area16(bool isInitial){
	if(isInitial){
		move_cursor(S_RIGHT, 4);

		move_cursor(S_TOP, 6);
	}
	else{
		area5();
	}
}

static void area17(void){
	move_cursor(S_RIGHT, 1);

	move_cursor(S_TOP, 3);	
}

static void area18(void){
	move_cursor(S_LEFT, 1);

	move_cursor(S_BOTTOM, 1);
}

static void area19(void){
	move_cursor(S_BOTTOM, 2);

	move_cursor(S_LEFT, 1);
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

static void bench_reset_alpha_exploit(void){
	for(;;){
		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH, 50},	
		);
		pause_automation();
		_delay_ms(14500);
		//
		run_units(S_RIGHT, 12, false);
		pause_automation();
		_delay_ms(1000);
		run_units(S_LEFT, 12, false);
		run_units(S_BOTTOM, 1, true);
		//
		send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	}
}

static void bench_reset(void){
	for(;;){
		SEND_BUTTON_SEQUENCE(
			{ BT_A, DP_NEUTRAL,	SEQ_MASH, 50},	
		);
		pause_automation();
		_delay_ms(14500);
		send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	}
}

static void sewers(void){
	set_leds(BOTH_LEDS);
	pause_automation();

		/* Feature selection menu */
	uint8_t count = count_button_presses(100, 900);

	for (uint8_t i = 0 ; i < count ; i += 1) {
		beep();
		_delay_ms(100);
	}

	set_leds(BOTH_LEDS);
	switch (count){
		case 1:
			sewer_1();
			return;
		break;

		case 2:
			sewer_2();
			return;
		break;
	
		default:
			return;		
		break;
	}
}

static void warp_to_sewer_enterance(void){
	open_map(false);

	SEND_BUTTON_SEQUENCE(
		{BT_Y, DP_NEUTRAL, SEQ_HOLD, 10},
		{ BT_A, DP_NEUTRAL,	SEQ_MASH,	10 }
	);

	pause_automation();
	_delay_ms(2500);
}

static void sewer_1(){
	//open map
	bool isInit = true;

	for(;;){
		if(isInit){
			warp_to_sewer_enterance();
			isInit = false;
		}
		
		//go from ladder to spawn point
		for (uint16_t i = 0 ; i < 210; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
		}
		for (uint16_t i = 0 ; i < 112; i += 1) {
			send_update(BT_NONE,	DP_NEUTRAL, S_RIGHT, S_NEUTRAL);
		}
		pause_automation();
		_delay_ms(500);
		
		//runback - cant warp b/c combat with alphas
		for (uint16_t i = 0 ; i < 111; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_LEFT, S_NEUTRAL);
		}
		for (uint16_t i = 0 ; i < 210; i += 1) {
			send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
		}
		pause_automation();
		_delay_ms(500);
	}
	return;
}

static void sewer_2(void){
	bool isInit = true;
	for(;;){
		if(isInit){
			warp_to_sewer_enterance();
			for (uint16_t i = 0 ; i < 119; i += 1) {
				send_update(BT_B,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
			}
			for (uint16_t i = 0 ; i < 115; i += 1) {
				send_update(BT_NONE, DP_NEUTRAL, S_LEFT, S_NEUTRAL);
			}
			pause_automation();
			_delay_ms(1400);
			for (uint16_t i = 0 ; i < 74; i += 1) {
				send_update(BT_B, DP_NEUTRAL, S_LEFT, S_NEUTRAL);
			}
			pause_automation();
			_delay_ms(500);
			isInit = false;
		}
		for (uint16_t i = 0 ; i < 210; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
		}
		pause_automation();
		_delay_ms(500);
		for (uint16_t i = 0 ; i < 210; i += 1) {
			send_update(BT_B,	DP_NEUTRAL, S_TOP, S_NEUTRAL);
		}
		pause_automation();
		_delay_ms(500);
	}
	return;
}

static void bench_to_drampa(void){
	run_units(S_LEFT, 3, false);
	run_units(S_BOTTOM, 27, true);
	run_units(S_RIGHT, 40, true);
}

static void drampa_to_bench(void){
	run_units(S_LEFT, 46, false);
	run_units(S_TOP, 27, true);
	run_units(S_RIGHT, 1, true);
	run_units(S_BOTTOM, 1, false);

	send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	//reset back to day
	SEND_BUTTON_SEQUENCE(
		{ BT_A, DP_NEUTRAL,	SEQ_MASH, 50},	
	);
	pause_automation();
	_delay_ms(14500);
	
	send_update(BT_NONE,	DP_NEUTRAL, S_BOTTOM, S_NEUTRAL);
	
	SEND_BUTTON_SEQUENCE(
		{ BT_A, DP_NEUTRAL,	SEQ_MASH, 50},	
	);
	pause_automation();
	_delay_ms(14500);
}

static void smart_drampa(void){
	//change to day
	SEND_BUTTON_SEQUENCE(
		{ BT_A, DP_NEUTRAL,	SEQ_MASH, 50},	
	);
	pause_automation();
	_delay_ms(14500);

	for(;;){
		//setup from bench
		bench_to_drampa();
		pause_automation();
		_delay_ms(1000); //wait for drampa to spawn in
		
		//spawn loop
		for(uint8_t i = 0; i < 8; i+=1){
			run_units(S_LEFT, 73, false);
			pause_automation();
			_delay_ms(500);

			run_units(S_RIGHT, 72, false);
			pause_automation();
			_delay_ms(1000);
		}	
		drampa_to_bench();
	}
}

static void indiv_menu(void){
	set_leds(BOTH_LEDS);
	pause_automation();

		/* Feature selection menu */
	uint8_t count = count_button_presses(100, 900);

	for (uint8_t i = 0 ; i < count ; i += 1) {
		beep();
		_delay_ms(100);
	}

	set_leds(BOTH_LEDS);
	switch (count){
		case 1:
			honedge();
		break;

		case 2:
			smart_drampa();
		break;
	
		case 3:
			helioptile();		
		break;

		default:
			return;
		break;
	}
}
	
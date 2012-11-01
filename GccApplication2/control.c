/*
 * control.c
 *
 * Created: 2012.10.25 19:03:01
 *  Author: Karolis
 */ 

#include <avr/io.h>
#include "Global_defs.h"
#include "control.h"
#include "measurement_buffs.h"

#define TURBINE_CNTRL_DIRECTION DDRC
#define TURBINE_CNTRL_PORT PORTC
#define TURBINE_TRN_LFT_PIN PC0
#define TURBINE_TRN_RGT_PIN PC1
#define TURBINE_STOP_PIN PC2

#define BUZZER_CNTRL_DIRECTION DDRD
#define BUZZER_CNTRL_PORT PORTD
#define BUZZER_PIN PD7

#define LOAD_ON 1
#define LOAD_OFF 0

static unsigned int get_voltage(void);
static void turbine_load(unsigned char state);
static unsigned int get_wind_angle(void);


void output_port_config(void){
	
	TURBINE_CNTRL_DIRECTION |= (1 << TURBINE_TRN_LFT_PIN); 
	TURBINE_CNTRL_DIRECTION |= (1 << TURBINE_TRN_RGT_PIN);
	TURBINE_CNTRL_PORT |= (1 << TURBINE_TRN_LFT_PIN);
	TURBINE_CNTRL_PORT |= (1 << TURBINE_TRN_RGT_PIN);
	
	TURBINE_CNTRL_DIRECTION |= (1 << TURBINE_STOP_PIN);
	TURBINE_CNTRL_PORT |= (1 << TURBINE_STOP_PIN);
	
	BUZZER_CNTRL_DIRECTION |= (1 << BUZZER_PIN);
	BUZZER_CNTRL_PORT |= (1 << BUZZER_PIN);
	
}

void control_task(void){
	//sitas taskas perziuri visus buferius ir yra atsakingas uz ju nunulinima (jeigu persipildo-negerai)
	//pagal buferiuose esancias reiksmes jis valdo sunta ir pasuka maluna reikiamu kampu
	//TODO: implement
	//------------------------------------------------------------------
	buff_eval_task();//patikrinti buferius, jei reik nunulinti, uzstatyti flagus shunt_control ir rotation task'ams
	rotation_task();
	shunt_control_task();
	//------------------------------------------------------------------
	//
	//------------------------------------------------------------------	
}

void buff_eval_task(void){//patikrinti buferius, jei reik nunulinti, uzstatyti flagus shunt_control ir rotation task'ams

	//TODO: implement	
}

void rotation_task(void){
		//TODO: implement	
}

void shunt_control_task(void){
	//------------------------------------------------------------------
	unsigned int voltage = 0;
	//------------------------------------------------------------------
	voltage = get_voltage();
	//------------------------------------------------------------------
	if((voltage >= PANIC_VOLTAGE)&&(voltage != 0)){
		//------------------------------------------------------------------
		turbine_load(LOAD_ON);	
		//------------------------------------------------------------------
	}	
	//------------------------------------------------------------------	
}

static unsigned int get_voltage(void){
	//------------------------------------------------------------------
	uint16_t result = 0;
	unsigned char i = 0;
	//------------------------------------------------------------------
	if(G_voltage_measurement_Buff.length<=0){return 0;};
	//-------------------------------------------------------------------
	for(i = 0; i < G_voltage_measurement_Buff.length; i++){
		//-------------------------------------------------------------------
		result += (uint16_t)G_voltage_measurement_Buff.buff;
		//-------------------------------------------------------------------
	}	
	//------------------------------------------------------------------
	result /= (uint16_t)G_voltage_measurement_Buff.length;
	//-------------------------------------------------------------------
	return result;
	//------------------------------------------------------------------
}

static void turbine_load(unsigned char state){
	//------------------------------------------------------------------
	if (state == LOAD_ON){
		//------------------------------------------------------------------
		TURBINE_CNTRL_PORT &= ~(1 << TURBINE_STOP_PIN);
		//------------------------------------------------------------------		
	}else if (state == LOAD_OFF){
		//------------------------------------------------------------------
		TURBINE_CNTRL_PORT |= (1 << TURBINE_STOP_PIN);
		//------------------------------------------------------------------	
	}else{
		// UNDEF	
	}
	//------------------------------------------------------------------
}

static unsigned int get_wind_angle(void){	
	//------------------------------------------------------------------
	uint16_t result = 0;
	unsigned char i = 0;
	//------------------------------------------------------------------
	if(G_WindAngle_Buff.length<=0){return 0;};
	//-------------------------------------------------------------------	
	for(i = 0; i < G_WindAngle_Buff.length; i++){
		//-------------------------------------------------------------------
		result += (uint16_t)G_WindAngle_Buff.buff;
		//-------------------------------------------------------------------
	}
	//------------------------------------------------------------------
	result /= (uint16_t)G_WindAngle_Buff.length;	
	//------------------------------------------------------------------
}

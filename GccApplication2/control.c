/*
 * control.c
 *
 * Created: 2012.10.25 19:03:01
 *  Author: Karolis
 */ 

#include "Global_defs.h"
#include "control.h"

void control_task(void)
{
	//sitas taskas perziuri visus buferius ir yra atsakingas uz ju nunulinima (jeigu persipildo-negerai)
	//pagal buferiuose esancias reiksmes jis valdo sunta ir pasuka maluna reikiamu kampu
	//TODO: implement
	
	buff_eval_task();//patikrinti buferius, jei reik nunulinti, uzstatyti flagus shunt_control ir rotation task'ams
	rotation_task();
	shunt_control_task();
	
	
}

void buff_eval_task(void)//patikrinti buferius, jei reik nunulinti, uzstatyti flagus shunt_control ir rotation task'ams
{
	//TODO: implement	
}
void rotation_task(void)
{
		//TODO: implement	
}
void shunt_control_task(void)
{
	//TODO: implement		
}
/*
 * control.h
 *
 * Created: 2012.10.25 19:03:19
 *  Author: Karolis
 */ 

void control_task(void);
void buff_eval_task(void);//patikrinti buferius, jei reik nunulinti, uzstatyti flagus shunt_control ir rotation task'ams
void rotation_task(void);
void shunt_control_task(void);

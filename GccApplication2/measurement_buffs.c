/*
 * measurement_buffs.c
 *
 * Created: 2012.10.22 21:46:46
 *  Author: Karolis
 */ 
#include <string.h>
#include "measurement_buffs.h"


void wind_angle_buff_init(void)
{
	
	G_WindAngle_Buff.length = 0;
	G_WindAngle_Buff.index = 0;
	
	memset(G_WindAngle_Buff.buff,0,WIND_ANGLE_BUFF_SIZE);
	
}

void wind_speed_buff_init(void)
{
	
	G_WindSpeed_Buff.length = (0);
	G_WindSpeed_Buff.index = 0;

	memset(G_WindSpeed_Buff.buff,0,WIND_ANGLE_BUFF_SIZE);
}

void voltage_measurement_buff_init(void)
{
	
	G_voltage_measurement_Buff.length = 0;
	G_voltage_measurement_Buff.index = 0;
	
	memset(G_voltage_measurement_Buff.buff,0,WIND_ANGLE_BUFF_SIZE);
}

void buffs_init(void)
{
	wind_angle_buff_init();
	wind_speed_buff_init();
	voltage_measurement_buff_init();
	
}


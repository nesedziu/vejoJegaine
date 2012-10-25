/*
 * measurements.c
 *
 * Created: 2012.10.22 21:20:32
 *  Author: Karolis
 */ 
#include "measurements.h"
#include "Global_defs.h"
#include "measurement_buffs.h"



unsigned int measure_voltage(void)
{
	//TODO: implement
	return  0;
}

unsigned int measure_windSpeed(void)
{
	//TODO: implement
	return 0;
}

void measurements_task(void)
{
	if (G_voltage_Measurement_s >= VOLTAGE_MEASUREMENT_PERIOD)
	{
		G_voltage_Measurement_s = 0;
		G_voltage_measurement_Buff.buff[G_voltage_measurement_Buff.index] = measure_voltage();
		G_voltage_measurement_Buff.index++;
		G_voltage_measurement_Buff.length++;
	}
	if (G_windAngle_measurement_s >= WIND_ANGLE_MEASUREMENT_PERIOD)
	{//kai sitie buferiai persipildo juos nunulina control task
		G_windAngle_measurement_s = 0;
		G_voltage_measurement_Buff.buff[G_voltage_measurement_Buff.index] = measure_windSpeed();
		G_voltage_measurement_Buff.index++;
		G_voltage_measurement_Buff.length++;
		
	}
	//matavaimai bus atliekami pertrauktimi, pasinaudojus kitu taimeriu
/*	if (G_windSpeed_measurement_s >= WIND_SPEED_MEASUREMENT_PERIOD)
	{
		G_windAngle_measurement_s = 0;
		//TODO: implement
	}*/
}

void measurements_init(void)
{
	G_voltage_Measurement_s = 0;
	G_windAngle_measurement_s = 0;
	G_windSpeed_measurement_s =0;
}

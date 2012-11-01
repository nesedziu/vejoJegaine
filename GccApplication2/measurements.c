/*
 * measurements.c
 *
 * Created: 2012.10.22 21:20:32
 *  Author: Karolis
 */ 
#include "measurements.h"
#include "Global_defs.h"
#include "measurement_buffs.h"
#include "ADC.h"

extern unsigned int G_anemometer_freq_s;

unsigned int measure_voltage(void)
{
int i =0;
unsigned int voltage = 0;
	
	//Atsakymas isduodamas milivoltais//
	//TODO: isduoda butent tiek voltu kiek mato, perdaryti, kad paverstu i itampa gaunama is jegaines
	for (i = 0; i < 10; i++)
	{
		voltage += (adc_read(VOLTAGE_MEASUREMENT_DIFF1_ADC_PIN) - adc_read(VOLTAGE_MEASUREMENT_DIFF2_ADC_PIN))*5;
	}	
	
	voltage /= 10;
	return voltage;
}

unsigned int measure_windAngle(void)
{
int i = 0;
unsigned int angle = 0;

	for (i = 0; i < 10; i++)
	{
		 angle += adc_read(WIND_ANGLE_ADC_PIN);
	}
	
	angle /= 27;
	
	if (angle > 360)
		angle = 360;
		
	return angle;// grazina laipsniais
}

void measurements_task(void)
{
	if (G_voltage_Measurement_s >= VOLTAGE_MEASUREMENT_PERIOD)
	{
		G_voltage_Measurement_s = 0;
			
		if(G_voltage_measurement_Buff.index >= VOLTAGE_MEASUREMENT_BUFF_SIZE)
		{
			G_voltage_measurement_Buff.index = 0;
		}
	
		G_voltage_measurement_Buff.buff[G_voltage_measurement_Buff.index] = measure_voltage();
		G_voltage_measurement_Buff.index++;
		
		if(!(G_voltage_measurement_Buff.length >= VOLTAGE_MEASUREMENT_BUFF_SIZE))
			G_voltage_measurement_Buff.length++;
	}
	if (G_windAngle_measurement_s >= WIND_ANGLE_MEASUREMENT_PERIOD)
	{//kai sitie buferiai persipildo juos nunulina control task
		G_windAngle_measurement_s = 0;
		
		if(G_WindAngle_Buff.index >= WIND_ANGLE_BUFF_SIZE)
		{
			G_WindAngle_Buff.index = 0;
		}
		
		G_WindAngle_Buff.buff[G_voltage_measurement_Buff.index] = measure_windAngle();
		G_WindAngle_Buff.index++;
		
		if(!(G_WindAngle_Buff.length >= VOLTAGE_MEASUREMENT_BUFF_SIZE))
			G_WindAngle_Buff.length++;
		
	}
	//matavaimai bus atliekami pertrauktimi, pasinaudojus kitu taimeriu
	if (G_windSpeed_measurement_s >= WIND_SPEED_MEASUREMENT_PERIOD)
	{
		G_windSpeed_measurement_s = 0;
		if(G_WindSpeed_Buff.index >= WIND_ANGLE_BUFF_SIZE)
		{
			G_WindSpeed_Buff.index = 0;
		}
		
		G_WindSpeed_Buff.buff[G_voltage_measurement_Buff.index] = G_anemometer_freq_s;
		G_WindSpeed_Buff.index++;
		
		if(!(G_WindSpeed_Buff.length >= VOLTAGE_MEASUREMENT_BUFF_SIZE))
			G_WindSpeed_Buff.length++;
		//TODO: implement
	}
}

void measurements_init(void)
{
	G_voltage_Measurement_s = 0;
	G_windAngle_measurement_s = 0;
	G_windSpeed_measurement_s =0;
}

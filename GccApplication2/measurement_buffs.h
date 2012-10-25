/*
 * measurement_buffs.h
 *
 * Created: 2012.10.22 21:42:36
 *  Author: Karolis
 */ 


#ifndef MEASUREMENT_BUFFS_H_
#define MEASUREMENT_BUFFS_H_

//kiek matavimu reikia kaupti?
#define WIND_ANGLE_BUFF_SIZE 10				
#define WIND_SPEED_BUFF_SIZE 10
#define VOLTAGE_MEASUREMENT_BUFF_SIZE 10

extern unsigned int G_voltage_Measurement_s;
extern unsigned int G_windSpeed_measurement_s;
extern unsigned int G_windAngle_measurement_s;


struct wind_angle_buff{
	unsigned int buff[WIND_ANGLE_BUFF_SIZE];
	unsigned int length;
	unsigned int index;
};
struct wind_angle_buff G_WindAngle_Buff;

struct wind_speed_buff{
	unsigned int buff[WIND_SPEED_BUFF_SIZE];
	unsigned int length;
	unsigned int index;
};
struct wind_speed_buff G_WindSpeed_Buff;

struct voltage_measurement_buff{
	unsigned int buff[VOLTAGE_MEASUREMENT_BUFF_SIZE];
	unsigned int length;
	unsigned int index;
};
struct voltage_measurement_buff G_voltage_measurement_Buff;


void buffs_init(void);


#endif /* MEASUREMENT_BUFFS_H_ */

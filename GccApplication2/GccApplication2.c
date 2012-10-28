/*
 * GccApplication2.c
 *  Wind power turbine controller
 *  Created: 2012.10.22 18:46:25
 *  Code Author: Karolis Stanius
 *  Hardware Author: Tomas Sinkunas
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Global_defs.h"
#include "measurements.h"
#include "measurement_buffs.h"
#include "control.h"
#include "ADC.h"


unsigned int G_voltage_Measurement_s;
unsigned int G_windSpeed_measurement_s;
unsigned int G_windAngle_measurement_s;

unsigned int G_anemometer_freq_s = 0;

void input_task(void)
{	
	//nuskaito mygtukus
	//TODO: implement
	//interrupts?
}
void output_task(void)
{
	//pakolkas naudojamas tik info atvaizdavimui i lcd
	//TODO: implement
}

void timers_init(void)
{
	/*ne mano, paemiau is neto, testu nera*/
	//http://www.avrfreaks.net/index.php?name=PNphpBB2&file=printview&t=50106&start=0
	//Timer1
   TCCR1B |= (1 << WGM12); // Configure timer 1 for CTC mode

   TIMSK |= (1 << OCIE1A); // Enable CTC interrupt

   //sei(); //  Enable global interrupts

   OCR1A   = 15624; // Set CTC compare value to 1Hz at 1MHz AVR clock, with a prescaler of 64

   TCCR1B |= ((1 << CS10) | (1 << CS11)); // Start timer at Fcpu/64
   //-----------------------------------------------------------------------------------
   // Timer0
   //-----------------------------------------------------------------------------------	
	DDRB &= ~(1 << PB0);     // Clear the PD4 pin
	// PD4 is now an input

	//PORTB |= (1 << PB4);   // turn On the Pull-up
	// PD4 is now an input with pull-up enabled

	TCCR0 |= (1 << CS02) | (1 << CS01) | (1 << CS00);
	// Turn on the counter, Clock on Rise

	// enable global interrupts
	sei(); //  Enable global interrupts

   //-----------------------------------------------------------------------------------
} 

int main(void)
{
	buffs_init();
	timers_init();
	measurements_init();
	adc_init();
	sei();
	
    while(1)
    {
		measurements_task();	//renka matavimus
		control_task();			//ivertina matavimus, atlieka sunto ir pasukimo valdyma
		input_task();			//TODO: interrupt driven?	/mygtukai
		output_task();			//lcd..	
    }
}

ISR(TIMER1_COMPA_vect)
{
	G_voltage_Measurement_s++;
	G_windAngle_measurement_s++;
	G_windSpeed_measurement_s++;
	
	G_anemometer_freq_s = TCNT0;
	TCNT0 = 0;
}
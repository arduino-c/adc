
#include <avr/io.h>

/*
При такой конфигурации есть дин прикол: нужно читать оба регистра ADCL и ADCH причем именно в этой последовательности
иначе ADC уходит в иной мир и с него читается какаято херь. Или можно читать ADCW - этот макрос все сделает правильно
и вернет int.
*/

void adc_init() {
	/* 16Mhz/128 = 125Khz the ADC reference clock */
	ADCSRA |= (_BV(ADPS2) | _BV(ADPS1) | _BV(ADPS0));
	/* Voltage reference from Avcc (5v) */
	ADMUX |= _BV(REFS0);
	/* Turn on ADC */
	ADCSRA |= _BV(ADEN);
	/* Do an initial conversion because this one is the slowest
	and to ensure that everything is up and running */
	ADCSRA |= _BV(ADSC);
}

int adc_read(char ch) {
	/* Clear the older channel that was read */
	ADMUX &= 0xF0;
	/* Defines the new ADC channel to be read */
	ADMUX |= ch;
	/* Starts a new conversion */
	ADCSRA |= _BV(ADSC);
	/* Wait until the conversion is done */
	while(ADCSRA & _BV(ADSC));
	return ADCW;
}

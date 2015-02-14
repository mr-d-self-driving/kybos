/*
 * AD8557.h
 *
 *  Created on: 29.12.2014
 *      Author: struppi
 */

#ifndef AD8557_H_
#define AD8557_H_

#include "../GPIO.h"

class AD8557 {
public:
	AD8557();
	AD8557(GPIOPin in);
	AD8557(GPIOPin in, GPIOPin out);

	int setup();

	int setGain(uint8_t firstStage, uint8_t secondStage);
	//int readGain(uint8_t &firstStage, uint8_t &secondStage);
private:

	typedef enum {AD8857_FCT_SENSE, AD8857_FCT_SIMULATE, AD8857_FCT_PROGRAM, AD8857_FCT_READ} ad8857_function_t;
	typedef enum {AD8857_PARAM_SECOND_STAGE, AD8857_PARAM_FIRST_STAGE, AD8857_PARAM_OUTPUT_OFFSET, AD8857_PARAM_OTHER} ad8857_parameter_t;

	GPIOPin _pinDigIn;
	GPIOPin _pinDigOut;

	int sendPacket(ad8857_function_t function, ad8857_parameter_t parameter, uint8_t &value);
	int send1();
	int send0();
};

#endif /* AD8557_H_ */

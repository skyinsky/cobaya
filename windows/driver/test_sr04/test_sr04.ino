#include <NewPing.h>

//----------------------------------------------
// SR04
//----------------------------------------------
#define SERIAL_BAUD	9600
#define SR_TRIG_PORT	5	//d-pin
#define SR_ECHO_PORT	6	//d-pin
#define SR_MAX_DIST	400	// Maximum sensor distance is rated at 400-500cm.

NewPing sonar(SR_TRIG_PORT, SR_ECHO_PORT, SR_MAX_DIST);

unsigned int read_sonar()
{
	unsigned int us = sonar.ping();

	us /= US_ROUNDTRIP_CM;

	return us;
}

//----------------------------------------------
// main
//----------------------------------------------
void setup()
{
	Serial.begin(SERIAL_BAUD);
}

void loop()
{
	unsigned int cur_dist;

	cur_dist = read_sonar();

	Serial.println(cur_dist);

	delay(100);
}

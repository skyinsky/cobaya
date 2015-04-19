//----------------------------------------------
// global nano resource
//----------------------------------------------
#define SERIAL_BAUD	9600

// x:A1, y:A4, z:A7
#define ADXL_X_PORT	1	//a-pin
#define ADXL_Y_PORT	4	//a-pin
#define ADXL_Z_PORT	7	//a-pin

#define ADXL_X_DIFF	10	//DEC
#define ADXL_Y_DIFF	10	//DEC
#define ADXL_Z_DIFF	10	//DEC

//----------------------------------------------
// adxl335
//----------------------------------------------
#define SAMPLE_TIMES	10

int last_x;	// x axis variable
int last_y;	// y axis variable
int last_z;	// z axis variable

int read_axis(int pin)
{
	long reading = 0;

	analogRead(pin);
	delay(1);

	for (int i = 0; i < SAMPLE_TIMES; i++) {
		reading += analogRead(pin);
	}
	return reading / SAMPLE_TIMES;
}

void setup_adxl335()
{
	Serial.print("************* begin setup adxl335 module *************\n");
	
	last_x = 0;
	last_y = 0;
	last_z = 0;

	delay(2000);

	last_x = read_axis(ADXL_X_PORT);
	last_y = read_axis(ADXL_Y_PORT);
	last_z = read_axis(ADXL_Z_PORT);

	Serial.print("training x-y-z as follow\n");
	Serial.print("X: ");
	Serial.print(last_x);
	Serial.print("  Y: ");
	Serial.print(last_y);
	Serial.print("  Z: ");
	Serial.print(last_z);
	Serial.print("\n");

	Serial.print("************** end setup adxl335 module **************\n");
}

//----------------------------------------------
// main
//----------------------------------------------
void setup()
{
	Serial.begin(SERIAL_BAUD);
	Serial.print("setup begin\n");

	setup_adxl335();

	Serial.print("setup end\n");
}

void loop()
{
	bool find_x = false;
	bool find_y = false;
	bool find_z = false;

	int this_x;
	int this_y;
	int this_z;

	int diff_x;
	int diff_y;
	int diff_z;

	this_x = analogRead(ADXL_X_PORT);
	this_y = analogRead(ADXL_Y_PORT);
	this_z = analogRead(ADXL_Z_PORT);

	diff_x = this_x - last_x;
	diff_y = this_y - last_y;
	diff_z = this_z - last_z;

	last_x = this_x;
	last_y = this_y;
	last_z = this_z;

	if (abs(diff_x) > ADXL_X_DIFF) {
		find_x = true;
	}
	if (abs(diff_y) > ADXL_Y_DIFF) {
		find_y = true;
	}
	if (abs(diff_z) > ADXL_Z_DIFF) {
		find_z = true;
	}

	if (find_x || find_y || find_z) {
		Serial.print("++++++++++\n");
	} else {
		Serial.print("-----------------------\n");
	}

	delay(100);
}

#include <ESP8266.h>
#include <SoftwareSerial.h>

//----------------------------------------------
// global nano resource
//----------------------------------------------
#define SERIAL_BAUD	115200

// RX:D3, TX:D2
#define WIFI_TX_PORT	4	//d-pin
#define WIFI_RX_PORT	7	//d-pin

// x:A1, y:A4, z:A7
#define ADXL_X_PORT	1	//a-pin
#define ADXL_Y_PORT	4	//a-pin
#define ADXL_Z_PORT	7	//a-pin

#define ADXL_X_DIFF	10	//DEC
#define ADXL_Y_DIFF	10	//DEC
#define ADXL_Z_DIFF	10	//DEC

#define SSID        "ct001"
#define PASSWORD    "hspmtc9310lsoge8429g"
#define HOST_NAME   "10.10.3.112"
//#define HOST_NAME   "192.168.1.100"
#define HOST_PORT   (11612)

#define MSG_HAS_PERSON	"CT_001:1"
#define MSG_NOT_PERSON	"CT_001:0"
#define MSG_LENGTH	8

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

	last_x = read_axis(ADXL_X_PORT);
	last_y = read_axis(ADXL_Y_PORT);
	last_z = read_axis(ADXL_Z_PORT);

	Serial.print("training x-y-z as follow\n");
	Serial.print("X: ");
	Serial.print(last_x);
	Serial.print("Y: ");
	Serial.print(last_y);
	Serial.print("Z: ");
	Serial.print(last_z);
	Serial.print("\n");

	Serial.print("************** end setup adxl335 module **************\n");
}

//----------------------------------------------
// wifi
//----------------------------------------------
bool wifi_connected = false;

// RX:D3, TX:D2
SoftwareSerial wifi_serial(WIFI_RX_PORT, WIFI_TX_PORT);
ESP8266 wifi(wifi_serial, SERIAL_BAUD);

void setup_wifi()
{
	Serial.print("************* begin setup wifi module *************\n");

	Serial.print("firmware version:");
	Serial.println(wifi.getVersion().c_str());

	if (wifi.setOprToStation(1, 1)) {
		Serial.print("start station module ok\n");
	} else {
		Serial.print("start station module err\n");
	}

	if (wifi.joinAP(SSID, PASSWORD)) {
		Serial.print("join ");
		Serial.print(SSID);
		Serial.print(" success\n");
		Serial.print("IP:");
		Serial.println( wifi.getLocalIP().c_str());       
	} else {
		Serial.print("join ");
		Serial.print(SSID);
		Serial.print(" failed\n");
	}

	if (wifi.disableMUX()) {
		Serial.print("single user ok\n");
	} else {
		Serial.print("single user err\n");
	}

	Serial.print("************** end setup wifi module **************\n");
}

void send_server(bool has_person)
{
	bool send_res;
	
	if (!wifi_connected) {
		if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
			Serial.print("create tcp ok\n");
			wifi_connected = true;
		} else {
			Serial.print("create tcp err\n");
			return;
		}
	}

	if (has_person) {
		send_res = wifi.send((const uint8_t*)MSG_HAS_PERSON, MSG_LENGTH);
	} else {
		send_res = wifi.send((const uint8_t*)MSG_NOT_PERSON, MSG_LENGTH);
	}
	if (!send_res) {
		wifi_connected = false;
	}
}

//----------------------------------------------
// main
//----------------------------------------------
void setup()
{
	Serial.begin(SERIAL_BAUD);
	Serial.print("setup begin\n");

	setup_wifi();
	setup_adxl335();

	Serial.print("setup end\n");
}

int abs(int v)
{
	return ((v >= 0) ? v : -v);
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
        send_server(true);
	} else {
        send_server(false);
	}

	//delay(1000);
}

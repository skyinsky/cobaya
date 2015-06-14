#include <ESP8266.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

//----------------------------------------------
// global nano resource
//----------------------------------------------
//#define SERIAL_BAUD	9600
#define SERIAL_BAUD	115200

#define WIFI_TX_PORT	4	//d-pin
#define WIFI_RX_PORT	7	//d-pin

#define SR_TRIG_PORT	5	//d-pin
#define SR_ECHO_PORT	6	//d-pin

#define SR_INIT_DIST	40	//没有人时，探头探测的距离
#define SR_MIN_DIST     100
#define SR_MAX_DIST     190
#define SR_HAS_PERSON	10	//人躺下的平均厚度
#define SR_MAX_DIST	400	// Maximum sensor distance is rated at 400-500cm.

#define SSID        "ct002"
#define PASSWORD    "hspmtc9310lsoge8429g"
#define HOST_NAME   "10.10.3.112"
//#define HOST_NAME   "192.168.1.100"
#define HOST_PORT   (11612)

#define MSG_HAS_PERSON	"CT_002:1"
#define MSG_NOT_PERSON	"CT_002:0"
#define MSG_LENGTH	8

//----------------------------------------------
// SR04
//----------------------------------------------
NewPing sonar(SR_TRIG_PORT, SR_ECHO_PORT, SR_MAX_DIST);

unsigned int read_sonar()
{
	unsigned int us = sonar.ping();

	us /= US_ROUNDTRIP_CM;

	return us;
}

//----------------------------------------------
// wifi
//----------------------------------------------
bool wifi_connected = false;

// RX:D3, TX:D2
SoftwareSerial wifi_serial(WIFI_RX_PORT, WIFI_TX_PORT);
ESP8266 wifi(wifi_serial);

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

	Serial.print("setup end\n");
}

void loop()
{
	 unsigned int diff_dist;
	 unsigned int cur_dist;

	cur_dist = read_sonar();
	if (cur_dist <= SR_MIN_DIST) {
		send_server(false);
		return;
	}
    if (cur_dist >= SR_MAX_DIST) {
        send_server(false);
		return;
    }
	
	diff_dist = SR_MAX_DIST - cur_dist;
	if (diff_dist >= SR_HAS_PERSON) {
		send_server(true);
	} else {
		send_server(false);
	}
}

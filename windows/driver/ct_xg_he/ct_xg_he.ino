#include <ESP8266.h>
#include <NewPing.h>
#include <SoftwareSerial.h>

//----------------------------------------------
// global nano resource
//----------------------------------------------
#define SERIAL_BAUD	9600

#define WIFI_TX_PORT	2
#define WIFI_RX_PORT	3

#define PIR_TX_PORT	4

#define SR_TRIG_PORT	5
#define SR_ECHO_PORT	6

#define MSG_HAS_PERSON	"CT_001:1"
#define MSG_NOT_PERSON	"CT_001:0"

#define SR04_MIN	40 
#define SR04_MAX	60
#define SR04_MIN_FACE	5
#define SR04_MAX_FACE	30

//----------------------------------------------
// SR04
//----------------------------------------------
#define MAX_DISTANCE 400 // Maximum sensor distance is rated at 400-500cm.

NewPing sonar(SR_TRIG_PORT, SR_ECHO_PORT, MAX_DISTANCE);

unsigned int last_dist = 0;

void setup_sr04()
{
	Serial.print("************* begin setup sonar module *************\r\n");

	last_dist = read_sonar();

	Serial.print("************** end setup sonar module **************\r\n");
}

unsigned int read_sonar()
{
	unsigned int us = sonar.ping();

	us /= US_ROUNDTRIP_CM;

	return us;
}

//----------------------------------------------
// pir
//----------------------------------------------
int read_pir()
{
	return digitalRead(PIR_TX_PORT);
}

//----------------------------------------------
// wifi
//----------------------------------------------
#define SSID        "ubuntu"
#define PASSWORD    "flywith9476"
#define HOST_NAME   "192.168.1.103"
#define HOST_PORT   (8090)

bool wifi_connected = false;

// RX:D3, TX:D2
SoftwareSerial wifi_serial(WIFI_RX_PORT, WIFI_TX_PORT);
ESP8266 wifi(wifi_serial, SERIAL_BAUD);

void setup_wifi()
{
	Serial.print("************* begin setup wifi module *************\r\n");

	Serial.print("firmware version:");
	Serial.println(wifi.getVersion().c_str());

	if (wifi.setOprToStation()) {
		Serial.print("start station module ok\r\n");
	} else {
		Serial.print("start station module err\r\n");
	}

	if (wifi.joinAP(SSID, PASSWORD)) {
		Serial.print("join ");
		Serial.print(SSID);
		Serial.print(" success\r\n");
		Serial.print("IP:");
		Serial.println( wifi.getLocalIP().c_str());       
	} else {
		Serial.print("join ");
		Serial.print(SSID);
		Serial.print(" failed\r\n");
	}

	if (wifi.disableMUX()) {
		Serial.print("single user ok\r\n");
	} else {
		Serial.print("single user err\r\n");
	}

	Serial.print("************** end setup wifi module **************\r\n");
}

void send_server(bool has_person)
{
	bool send_res;
	
    if (!wifi_connected) {
		if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
			Serial.print("create tcp ok\r\n");
			wifi_connected = true;
		} else {
			Serial.print("create tcp err\r\n");
			return;
		}
    }

    if (has_person) {
    	send_res = wifi.send((const uint8_t*)MSG_HAS_PERSON, 8);
		
    } else {
    	send_res = wifi.send((const uint8_t*)MSG_NOT_PERSON, 8);
		
    }
	if (!send_res) {
		wifi_connected = false;
		Serial.print("send err\r\n");
	} else {
            Serial.print("send ok\r\n");
	}

//    if (wifi.releaseTCP()) {
//        Serial.print("release tcp ok\r\n");
//    } else {
//        Serial.print("release tcp err\r\n");
//    }
}

//----------------------------------------------
// module 1
//----------------------------------------------
void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.print("setup begin\r\n");

    setup_wifi();

    Serial.print("setup end\r\n");
}

void loop()
{
	unsigned int diff_dist;
	unsigned int cur_dist = read_sonar();

	if (cur_dist < SR04_MIN) {
		send_server(true);
//		goto out;
                return;
	}

	diff_dist = last_dist - cur_dist;
	if (diff_dist > SR04_MIN_FACE && diff_dist < SR04_MIN_FACE) {
		send_server(true);
	} else {
		send_server(false);
	}
//
//out:
//	delay(1000);
}













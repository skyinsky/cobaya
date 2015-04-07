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


//----------------------------------------------
// SR04
//----------------------------------------------
#define MAX_DISTANCE 400 // Maximum sensor distance is rated at 400-500cm.

NewPing sonar(SR_TRIG_PORT, SR_ECHO_PORT, MAX_DISTANCE);

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
#define SSID        "ITEAD"
#define PASSWORD    "12345678"
#define HOST_NAME   "192.168.1.100"
#define HOST_PORT   (8090)

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

	Serial.print("************* end setup wifi module *************\r\n");
}

bool connect_server()
{
    if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
        Serial.print("create tcp ok\r\n");
	return true;
    } else {
        Serial.print("create tcp err\r\n");
	return false;
    }
}

void setup()
{
    Serial.begin(SERIAL_BAUD);
    Serial.print("setup begin\r\n");

}

void loop()
{

}

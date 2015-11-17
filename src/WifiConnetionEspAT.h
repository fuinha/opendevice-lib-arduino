/*
 * WifiConnetionEspAT.h
 *
 *  Created on: 12/11/2015
 *      Author: ricardo
 */

#ifndef LIBRARIES_OPENDEVICE_SRC_WIFICONNETIONESPAT_H_
#define LIBRARIES_OPENDEVICE_SRC_WIFICONNETIONESPAT_H_

#include <ESP8266AT.h>
#include <WifiClientAT.h>

#include "config.h"
#include "utility/Timeout.h"
#include "BaseWifiConnection.h"

using namespace od;

class WifiConnetionEspAT: public BaseWifiConnection {
public:

	ESP8266 *ESP;

	WifiConnetionEspAT();

	virtual ~WifiConnetionEspAT();

	void init(ESP8266 *impl);

	virtual void begin(void);

	virtual bool checkDataAvalible(void);

	virtual wl_status_t status();

	virtual void restart();

	virtual void disconnect(bool wifioff = false);

	virtual void mode(WiFiMode mode);

	virtual bool begin(const char* ssid, const char *passphrase);

    /* Set up a WPA2-secured access point
     *
     * param ssid: Pointer to the SSID string.
     * param passphrase: Pointer to passphrase, 8 characters min.
     * param channel: WiFi channel number, 1 - 13.
     */
    void softAP(const char* ssid, const char* passphrase, int channel = 1);

	virtual char* getIP();

private:
	const uint8_t DISCOVERY_ID = 3;
//	int stateFlags;
	WiFiMode _mode;
	bool softAPEnabled;
	wl_status_t _status;
	wl_status_t _statusTcp; // used to check if has reseted or wifi lost/reconnected
	Timeout statusTimeout;
	Timeout tcpTimeout;

	ESP8266Client client;
	uint8_t buffer[DATA_BUFFER] = {0};

	wl_status_t statusTcp(bool force = false);

};

extern WifiConnetionEspAT WiFi;

#endif /* LIBRARIES_OPENDEVICE_SRC_WIFICONNETIONESPAT_H_ */

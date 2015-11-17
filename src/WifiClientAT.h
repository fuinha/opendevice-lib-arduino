/*
 * ******************************************************************************
 *  Copyright (c) 2013-2014 CriativaSoft (www.criativasoft.com.br)
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *  Ricardo JL Rufino - Initial API and Implementation
 * *****************************************************************************
 */


#ifndef ESP8266CLIENT_H_
#define ESP8266CLIENT_H_

#include <Arduino.h>
#include <Stream.h>
#include <ESP8266AT.h>

#include "config.h"
#include "Command.h"
#include "utility/Logger.h"
#include "utility/StreamBuffer.h"

using namespace od;

/*
 * ESP8266Client
 *
 *  Created on: 05/10/2015
 *  Author: Ricardo JL Rufino
 */
class ESP8266Client : public Stream {
public:
	uint8_t id;
	ESP8266 *ESP;

	ESP8266Client();
	~ESP8266Client() {}

    inline int available(){ return buffer.available(); };
    inline int read(){ return buffer.read(); };
    inline int peek(){ return buffer.peek(); };
    inline void flush(){ buffer.flush(); };
    virtual size_t write(uint8_t);

    void setData(uint8_t *buffer, const uint16_t len);

private:
    uint8_t _buffer[DATA_BUFFER];
	StreamBuffer buffer;
};

#endif /* ESP8266CLIENT_H_ */

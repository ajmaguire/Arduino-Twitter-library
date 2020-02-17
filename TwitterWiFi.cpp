/*
  Twitter.cpp - Arduino library to Post messages to Twitter using OAuth.
  Copyright (c) NeoCat 2010-2011. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 */

// ver1.2 - Use <string.h>
// ver1.3 - Support IDE 1.0
// ver1.4 - Changed to use WiFi library instead of Ethernet. - ajm 2/17/20

#include <string.h>
#include "TwitterWiFi.h"

#define LIB_DOMAIN "arduino-tweet.appspot.com"

TwitterWiFi::TwitterWiFi(const char *token) : token(token)
{
}

bool TwitterWiFi::post(const char *msg)
{
	parseStatus = 0;
	statusCode = 0;
    
	if (client.connect(LIB_DOMAIN, 80)) {
		client.println("POST http://" LIB_DOMAIN "/update HTTP/1.1");
		client.print("Content-Length: ");
		client.println(strlen(msg)+strlen(token)+14);
		client.println("Host: " LIB_DOMAIN);
		client.println("Connection: close");
		client.println();
		client.print("token=");
		client.print(token);
		client.print("&status=");
		client.println(msg);
        
	} else {
		return false;
	}
	return true;
}

bool TwitterWiFi::checkStatus(Print *debug)
{
	if (!client.connected()) {
		if (debug)
			while(client.available())
				debug->print((char)client.read());
		client.flush();
		client.stop();
		return false;
	}
	if (!client.available())
		return true;
	char c = client.read();
	if (debug)
		debug->print(c);
	switch(parseStatus) {
	case 0:
		if (c == ' ') parseStatus++; break;  // skip "HTTP/1.1 "
	case 1:
		if (c >= '0' && c <= '9') {
			statusCode *= 10;
			statusCode += c - '0';
		} else {
			parseStatus++;
		}
	}
	return true;
}

int TwitterWiFi::wait(Print *debug)
{
	while (checkStatus(debug));
	return statusCode;
}

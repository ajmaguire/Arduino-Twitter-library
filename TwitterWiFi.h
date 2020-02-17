/*
  Twitter.cpp - Arduino library to Post messages to Twitter using OAuth.
  Copyright (c) NeoCat 2010-2011. All right reserved.
  
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 */

// ver1.2 - Use <Udp.h> to support IDE 0019 or later
// ver1.3 - Support IDE 1.0
// ver1.4 - Changed to use WiFi library instead of Ethernet. - ajm 2/17/20


#ifndef TWITTER_H
#define TWITTER_H

#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiMulti.h>
#include <WiFiUdp.h>
#include <WiFiScan.h>
#include <ETH.h>
#include <WiFiClient.h>
#include <WiFiSTA.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiGeneric.h>

#include <dummy.h>

#include <inttypes.h>
#include <pgmspace.h> // new location of pgmspace.h header file. - ajm

class TwitterWiFi
{
private:
	uint8_t parseStatus;
	int statusCode;
	const char *token;
    WiFiClient client; // changed object type to WiFiClient for WiFi connectivity.
    
public:
	TwitterWiFi(const char *user_and_passwd);
	
	bool post(const char *msg);
	bool checkStatus(Print *debug = NULL);
	int  wait(Print *debug = NULL);
	int  status(void) { return statusCode; }
};

#endif	//TWITTER_H

#pragma once
#include "constants.h"
#include <WiFi.h>
#include <time.h>
#include <Firebase_ESP_Client.h>
#include <secrets.h>

// Source pour la stratégie du temps : 
// https://youtu.be/CZH4DJAtAVU?si=vRSGo8eH1al1UC0o
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET -18000
#define DAYLIGHT_OFFSET_SEC 3600

void initTime();
bool getCurrentTime(struct tm *timeinfo);
String  getCurrentTimestamp();

void initWiFi();
void initFirebase();

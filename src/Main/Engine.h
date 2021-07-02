#ifndef _ENGINE_H_
#define _ENGINE_H_

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Libraries/ArduinoJson/ArduinoJson.h"
#include <EEPROM.h>

#include "Libraries/Timer.h"

#include "Libraries/SaveData.hpp"

#include "Libraries/Regexp/Regexp.h"

#include "Main/Libraries/HX711/src/HX711.h"
#include "Devices/Scales.hpp"

#include "Pages/index.h"

#include "Devices/TestData.hpp"

#include "Libraries/RegexParser.hpp"

#include "WebServer.hpp"

#endif
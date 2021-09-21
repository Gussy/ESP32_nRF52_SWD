/*
   Copyright (c) 2021 Aaron Christophel ATCnetz.de
   SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "defines.h"
#include "web.h"
#include "glitcher.h"
#include "nrf_swd.h"
#include "swd.h"

#ifdef ENABLE_OTA
#include <ArduinoOTA.h>
#endif

void setup()
{
  Serial.begin(115200);
  swd_begin();
  glitcher_begin();
  init_web();
  delay(1000);
  Serial.printf("SWD Id: 0x%08x\r\n", nrf_begin());

#ifdef ENABLE_OTA
  ArduinoOTA.begin();
#endif
}

long last_blink = 0;
void loop()
{
#ifdef ENABLE_OTA
  ArduinoOTA.handle();
#endif
  if (get_glitcher())
  {
    do_glitcher();
  }
  else
  {
    do_nrf_swd();
  }
  if (millis() - last_blink > 100)
  {
    last_blink = millis();
    digitalWrite(LED_B, !digitalRead(LED_B));
  }
}

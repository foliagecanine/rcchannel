/*	
 *
 * Example program showing how to use the RCChannel library.
 *
 * You can use this code freely (see license at bottom).
 *
 * If you have not already, use the BasicRC example to determine the min
 * and max value for your channel.
 *
 * Values will automatically be mapped and clamped between 0 and 255.
 *
 */

#include <RCChannel.h>

/* Change this value depending on your board and setup
 * See https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * for a table of pins that can be used on your board.
 * Pins 2 and 3 can be used on Arduino Uno */
#define RC_PIN 2

// Change these values based on the min and max values of your RC channel
#define RC_MIN 1000
#define RC_MAX 2000

RCChannel *rcPtr;
void rcIRQ() {
  rcPtr->pwmInterrupt();
} 

RCChannel rc(RC_PIN, rcIRQ, &rcPtr, RC_MIN, RC_MAX);

void setup() {
  Serial.begin(9600);
  Serial.println("RC Min and Max.");
  rc.begin();
  Serial.println("Online.");
}

void loop() {
  Serial.println(rc.getDataFromRC());
}

/*
 * Copyright (C) 2021 foliagecanine
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */
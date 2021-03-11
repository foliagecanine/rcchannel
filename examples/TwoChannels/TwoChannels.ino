/*	
 *
 * Example program showing how to use the RCChannel library.
 *
 * You can use this code freely (see license at bottom).
 *
 * This example shows how to use two RC channels at once.
 *
 */

#include <RCChannel.h>

/* Change these values depending on your board and setup
 * See https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * for a table of pins that can be used on your board.
 * Pins 2 and 3 can be used on Arduino Uno */
#define RC1_PIN 2
#define RC2_PIN 3

RCChannel *rcPtr1;
void rcIRQ1() {
  rcPtr1->pwmInterrupt();
} 

RCChannel *rcPtr2;
void rcIRQ2() {
  rcPtr2->pwmInterrupt();
} 

RCChannel rc1(RC1_PIN, rcIRQ1, &rcPtr1);
RCChannel rc2(RC2_PIN, rcIRQ2, &rcPtr2);

void setup() {
  Serial.begin(9600);
  rc1.begin();
  rc2.begin();
  Serial.println("Online.");
}

void loop() {
  Serial.print("RC1: ");
  Serial.print(rc1.getDataFromRC());
  Serial.print("\tRC2: ");
  Serial.println(rc2.getDataFromRC());
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
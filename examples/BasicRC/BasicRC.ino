/*	
 *
 * Example program showing how to use the RCChannel library.
 *
 * You can use this code freely (see license at bottom).
 *
 * The RCChannel library is for use with Remote Control systems which have a
 * connector similar to a servo connector:
 *
 * |S|+|-| 
 *
 * Where 'S' is signal, '+' is VCC (usually 5V), and '-' is ground.
 *
 * If you are using an Arduino Uno and a compatible 5V RC receiver, connect
 * as follows:
 *
 * Arduino UNO     RC Receiver
 * ----------------------------------
 *          5V --> Reciever VCC
 *         GND --> Receiver GND
 *       Pin 2 --> Channel Signal Pin
 * 
 * Once you upload the code, you should get a stream of numbers. On your remote
 * control, if you move the control that corresponds to the channel you are
 * using, you should see the number change (either up or down).
 * From this you can determine the values you will need to use for min and max
 * (see the RCMinMax example)
 *
 */

#include <RCChannel.h>

/* Change this value depending on your board and setup
 * See https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * for a table of pins that can be used on your board.
 * Pins 2 and 3 can be used on Arduino Uno */
#define RC_PIN 2

RCChannel *rcPtr;
void rcIRQ() {
  rcPtr->pwmInterrupt();
} 

RCChannel rc(RC_PIN, rcIRQ, &rcPtr);

void setup() {
  Serial.begin(9600);
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
/*	
 *
 *  You may use this code under the following license:
 *
 *  Copyright 2021 foliagecanine
 *	
 * 	Permission is hereby granted, free of charge, to any person obtaining a
 *	copy of this software and associated documentation files (the "Software"),
 *	to deal in the Software without restriction, including without limitation
 *	the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *	and/or sell copies of the Software, and to permit persons to whom the
 *	Software is furnished to do so, subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included
 *	in all copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *	FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *	DEALINGS IN THE SOFTWARE.
 *
 */

#include "RCChannel.h"

RCChannel::RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr) {
	_channel = channel;
	_useMap = false;
	_useDeadZone = false;
	_interruptFunction = interruptFunction;
	*rcPtr = this;
}

RCChannel::RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh) {
	_interruptFunction = interruptFunction;
	_channel = channel;
	_mapLow = mapLow;
	_mapHigh = mapHigh;
	_useMap = true;
	_minMap = 0;
	_maxMap = 255;
	*rcPtr = this;
	_useDeadZone = false;
}

RCChannel::RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh, int minMap, int maxMap) {
	_interruptFunction = interruptFunction;
	_channel = channel;
	_mapLow = mapLow;
	_mapHigh = mapHigh;
	_useMap = true;
	_minMap = minMap;
	_maxMap = maxMap;
	*rcPtr = this;
	_useDeadZone = false;
}

RCChannel::RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh, int minMap, int maxMap, int deadZoneMin, int deadZoneMax, int deadZoneValue) {
	_interruptFunction = interruptFunction;
	_channel = channel;
	_mapLow = mapLow;
	_mapHigh = mapHigh;
	_useMap = true;
	_minMap = minMap;
	_maxMap = maxMap;
	*rcPtr = this;
	_useDeadZone = true;
	_deadZoneMin = deadZoneMin;
	_deadZoneMax = deadZoneMax;
	_deadZoneValue = deadZoneValue;
}

void RCChannel::begin() {
	pinMode(_channel,INPUT);
	attachInterrupt(digitalPinToInterrupt(_channel), _interruptFunction, CHANGE);
}

void RCChannel::setMap(int mapLow, int mapHigh) {
	_mapLow = mapLow;
	_mapHigh = mapHigh;
	_useMap = true;
}

void RCChannel::setMap(int mapLow, int mapHigh, int minMap, int maxMap) {
	_mapLow = mapLow;
	_mapHigh = mapHigh;
	_minMap = minMap;
	_maxMap = maxMap;
	_useMap = true;
}

void RCChannel::setDeadZone(int deadZoneMin, int deadZoneMax, int deadZoneValue) {
	_useDeadZone = true;
	_deadZoneMin = deadZoneMin;
	_deadZoneMax = deadZoneMax;
	_deadZoneValue = deadZoneValue;
}

void RCChannel::disableMap() {
	_useMap = false;
}

void RCChannel::disableDeadZone() {
	_useDeadZone = false;
}

void RCChannel::pwmInterrupt() {
	if (digitalRead(_channel) == HIGH) {
		_lastTick = micros();
	} else {
		_channelData = micros() - _lastTick;
		_newData = true;
	}
}

int RCChannel::getDataFromRC() {
	while (!_newData)
		;
	return getMappedData();
}

int RCChannel::lastDataFromRC() {
	return getMappedData();
}

int RCChannel::getMappedData() {
	if (_useMap) {
		int mapped = map(_channelData,_mapLow,_mapHigh,_minMap,_maxMap);
		mapped = constrain(mapped,_minMap,_maxMap);
	if (mapped > _deadZoneMin && mapped < _deadZoneMax)
		return _deadZoneValue;
	return mapped;
	} else {
		return _channelData;
	}
}
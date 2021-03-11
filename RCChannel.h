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

#ifndef _RCCHANNEL_H
#define _RCCHANNEL_H

#include <Arduino.h>

class RCChannel {
public:
	RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr);
	RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh);
	RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh, int minMap, int maxMap);
	RCChannel(int channel, void (*interruptFunction)(void), RCChannel **rcPtr, int mapLow, int mapHigh, int minMap, int maxMap, int deadZoneMin, int deadZoneMax, int deadZoneValue);
	void begin();
	void setMap(int mapLow, int mapHigh);
	void setMap(int mapLow, int mapHigh, int minMap, int maxMap);
	void setDeadZone(int deadZoneMin, int deadZoneMax, int deadZoneValue);
	void disableMap();
	void disableDeadZone();
	void pwmInterrupt();
	int getDataFromRC();
	int lastDataFromRC();
private:
	int _channel;
	bool _useMap;
	int _mapHigh;
	int _mapLow;
	int _maxMap;
	int _minMap;
	bool _useDeadZone;
	int _deadZoneMin;
	int _deadZoneMax;
	int _deadZoneValue;
	void (*_interruptFunction)(void);
	volatile int _channelData = 0;
	volatile long _lastTick = 0;
	volatile bool _newData = false;
	int getMappedData();
};

#endif
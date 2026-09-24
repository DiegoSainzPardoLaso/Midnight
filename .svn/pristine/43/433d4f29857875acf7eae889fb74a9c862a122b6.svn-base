#pragma once

#include <iostream>
#include <cstdint>

#include "Time.h"

namespace Midnight { namespace Timer {

	enum Action : byte
	{
		Create,
		Destroy,
	};


	/*
		@param id:			Timer ID among the different active timer's 
		@param startTimer:  Tells the timer when to start counting down
		@param timerDone:   Checks if the timer has finished
		@param currentTime: The time that's left on the timer
	*/
	struct alignas(8) Data 
	{
		uint32_t id;
		
		float    startingCountDownTime;
		float    currentTime;
		
		uint8_t  startTimer;
		uint8_t  timerDone;
	};
 
} }

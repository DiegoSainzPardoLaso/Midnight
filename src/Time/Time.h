#pragma once

#include <iostream>
#include <chrono>
#include <Windows.h>

#include "../Engine/EngineConfig.h"

namespace Time 
{	
	// Chrono Implementation
	//
	extern std::chrono::time_point<std::chrono::high_resolution_clock> chronoCurrentFrameTime;
	extern std::chrono::time_point<std::chrono::high_resolution_clock> chronoLastFrameTime;

	// Windows Implementation
	//
	extern LARGE_INTEGER cpuClockFrequency;
	extern LARGE_INTEGER windowsCurrentFrameTime;
	extern LARGE_INTEGER windowsLastFrameTime;

	// @note (Diego)[02/09/2024] Delta time is calculated in seconds multiply times 1000 to get ms
	//
	extern float deltaTime;
	extern float currentDelta;
	extern float currentFPS;
	
	void  Initialize();
	bool  UpdateDeltaTime();
	void  UpdateDeltaTimeVSYNC(float delta);
	float DeltaTime();
	float FPS();

	void update_delta_time_VSYNC();



}


#ifndef TIME_H
#define TIME_H

#include "raylib.h"

class Time
{
public:
	static float DeltaTime;
	static float ElapsedTime;
	static float TimeScale;

	static void Tick();
};



#endif // !TIME_H

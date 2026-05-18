#include "Time.h"

float Time::TimeScale = 1;
float Time::DeltaTime = 0;
float Time::ElapsedTime = 0;

void Time::Tick()
{
	DeltaTime = GetFrameTime() * TimeScale;
	ElapsedTime += DeltaTime;
}
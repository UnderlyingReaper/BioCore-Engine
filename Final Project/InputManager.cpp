#include "InputManager.h"
#include <raylib.h>
#include "Time.h"

// Private Functions
InputManager::InputManager() : _isPaused(false) {}
InputManager::~InputManager() {}

void InputManager::SetTimeScale(int n) { Time::TimeScale = n; }

// Public Functions
InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

// Getters
bool InputManager::IsPaused() const { return _isPaused; }

// Setters
void InputManager::TogglePause()
{ 
	_isPaused = !_isPaused;

	if (_isPaused) EnableCursor();
	else DisableCursor();
}

// Functions
void InputManager::Update()
{
	if (IsKeyPressed(KEY_SPACE)) TogglePause();
	
	if (IsKeyPressed(KEY_ONE)) SetTimeScale(1);
	if (IsKeyPressed(KEY_TWO)) SetTimeScale(2);
	if (IsKeyPressed(KEY_FOUR)) SetTimeScale(4);
}
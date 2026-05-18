#include "InputManager.h"
#include <raylib.h>

InputManager::InputManager() : _isPaused(false) {}
InputManager::~InputManager() {}

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
}
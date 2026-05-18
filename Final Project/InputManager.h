#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager
{
private:
	bool _isPaused;

	InputManager();
	~InputManager();

public:
	static InputManager* GetInstance();

	// Getters
	bool IsPaused() const;

	// Setters
	void TogglePause();

	// Functions
	void Update();
};

#endif // !INPUT_MANAGER_H

#pragma once

#ifndef INPUT_GAMECONTROLLER_H_
#define INPUT_GAMECONTROLLER_H_

#include <vector>
#include "InputAction.h"

class GameController {
private:
	std::vector<ButtonAction> _buttonActions;
	std::vector<MouseButtonAction> _mouseButtonActions;
	MouseMovedAction _mouseMovedAction;

public:
	GameController();
	InputAction GetActionForKey(InputKey key);
	void AddInputActionForKey(const ButtonAction& buttonAction);
	void ClearAll();

	static bool IsPressed(InputState state);
	static bool IsReleased(InputState state);
	static InputKey ActionKey();
	static InputKey CancelKey();
	static InputKey LeftKey();
	static InputKey RightKey();
	static InputKey UpKey();
	static InputKey DownKey();

	inline MouseMovedAction GetMouseMoveAction() { return _mouseMovedAction; }
	inline void SetMouseMovedAction(const MouseMovedAction& mouseMovedAction) { _mouseMovedAction = mouseMovedAction; }

	MouseInputAction GetMouseButtonActionForMouseButton(MouseButton button);
	void AddMouseButtonAction(const MouseButtonAction& mouseButtonAction);

	static MouseButton LeftMouseButton();
	static MouseButton RightMouseButton();
};

#endif /* INPUT_GAMECONTROLLER_H_*/
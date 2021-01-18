#include "InputController.h"
#include <SDL.h>
#include "GameController.h"

InputController::InputController():_quit(nullptr), _noptrCurrentController(nullptr) {}

void InputController::Init(InputAction quitAction) {
	_quit = quitAction;
}

void InputController::Update(uint32_t dt) {
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT:
			{
				_quit(dt, SDL_PRESSED);
			}
			case SDL_MOUSEMOTION:
			{
				if (_noptrCurrentController) {
					if (MouseMovedAction mouseMoved = _noptrCurrentController->GetMouseMoveAction()) {
						MousePosition position;
						position.xPos = sdlEvent.motion.x;
						position.yPos = sdlEvent.motion.y;
						mouseMoved(position);
					}
				}
			}
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEBUTTONDOWN:
				if (_noptrCurrentController) {
					MouseInputAction action =
						_noptrCurrentController->GetMouseButtonActionForMouseButton(static_cast<MouseButton>(sdlEvent.button.button));

					MousePosition position;
					position.xPos = sdlEvent.button.x;
					position.yPos = sdlEvent.button.y;

					action(static_cast<InputState>(sdlEvent.button.state), position);
				}
				break;
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				if (_noptrCurrentController) {
					InputAction action = _noptrCurrentController->GetActionForKey(sdlEvent.key.keysym.sym);
					action(dt, static_cast<InputState>(sdlEvent.key.state));
				}
				break;
		}
	}
}

void InputController::SetGameController(GameController* controller) {
	_noptrCurrentController = controller;
}

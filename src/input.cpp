#include "input.h"

void Input::beginNewFrame() {
	pressed_keys_.clear();
	released_keys_.clear();

	pressed_buttons_.clear();
	released_buttons_.clear();
}

void Input::keyDownEvent(const SDL_Event& event) {
	pressed_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event) {
	released_keys_[event.key.keysym.scancode] = true;
	held_keys_[event.key.keysym.scancode] = false;
}

void Input::joyButtonDownEvent(const SDL_Event& event) {
	pressed_buttons_[event.jbutton.button] = true;
	held_buttons_[event.jbutton.button] = true;
}

void Input::joyButtonUpEvent(const SDL_Event& event) {
	released_buttons_[event.jbutton.button] = true;
	held_buttons_[event.jbutton.button] = false;
}

void Input::joyAxisEvent(const SDL_Event& event) {
	axis_value_[event.jaxis.axis] = event.jaxis.value;
}

bool Input::wasKeyPressed(SDL_Scancode key) {
	return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDL_Scancode key) {
	return released_keys_[key];
}

bool Input::isKeyHeld(SDL_Scancode key) {
	return held_keys_[key];
}

bool Input::wasJoyButtonPressed(Uint8 button) {
	return pressed_buttons_[button];
}

bool Input::wasJoyButtonReleased(Uint8 button) {
	return released_buttons_[button];
}

bool Input::isJoyButtonHeld(Uint8 button) {
	return held_buttons_[button];
}

int Input::getJoyAxis(Uint8 axis) {
	return (int) axis_value_[axis];
}

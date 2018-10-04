#include "input.h"

void Input::beginNewFrame() {
	pressed_keys_.clear();
	released_keys_.clear();
}

void Input::keyDownEvent(const SDL_Event& event) {
	pressed_keys_[event.key.keysym.sym] = true;
	held_keys_[event.key.keysym.sym] = true;
}

void Input::keyUpEvent(const SDL_Event& event) {
	released_keys_[event.key.keysym.sym] = true;
	held_keys_[event.key.keysym.sym] = false;
}

void Input::joyButtonDownEvent(const SDL_Event& event) {
	pressed_buttons_[event.jbutton.button] = true;
	held_buttons_[event.jbutton.button] = true;
}

void Input::joyButtonUpEvent(const SDL_Event& event) {
	released_buttons_[event.jbutton.button] = true;
	held_buttons_[event.jbutton.button] = false;
}

bool Input::wasKeyPressed(SDLKey key) {
	return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDLKey key) {
	return released_keys_[key];
}

bool Input::isKeyHeld(SDLKey key) {
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

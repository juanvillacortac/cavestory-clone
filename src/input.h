#ifndef INPUT_H_
#define INPUT_H_

#include <SDL2/SDL.h>
#include <map>

class Input {
	private:
		std::map<SDL_Scancode, bool> held_keys_;
		std::map<SDL_Scancode, bool> pressed_keys_;
		std::map<SDL_Scancode, bool> released_keys_;

		std::map<Uint8, bool> held_buttons_;
		std::map<Uint8, bool> pressed_buttons_;
		std::map<Uint8, bool> released_buttons_;

		std::map<Uint8, Sint16> axis_value_;
	public:
		SDL_Joystick *joy;

		Input() {
			if(SDL_NumJoysticks() > 0){
				joy = SDL_JoystickOpen(0);
			}
		}

		void beginNewFrame();

		void keyDownEvent(const SDL_Event& event);
		void keyUpEvent(const SDL_Event& event);

		void joyButtonDownEvent(const SDL_Event& event);
		void joyButtonUpEvent(const SDL_Event& event);

		void joyAxisEvent(const SDL_Event& event);

		bool wasKeyPressed(SDL_Scancode key);
		bool wasKeyReleased(SDL_Scancode key);
		bool isKeyHeld(SDL_Scancode key);

		bool wasJoyButtonPressed(Uint8 button);
		bool wasJoyButtonReleased(Uint8 button);
		bool isJoyButtonHeld(Uint8 button);

		int getJoyAxis(Uint8 axis);
};

#endif // INPUT_H_

#ifndef INPUT_H_
#define INPUT_H_

#include <SDL/SDL.h>
#include <map>

class Input {
	private:
		std::map<SDLKey, bool> held_keys_;
		std::map<SDLKey, bool> pressed_keys_;
		std::map<SDLKey, bool> released_keys_;

		std::map<Uint8, bool> held_buttons_;
		std::map<Uint8, bool> pressed_buttons_;
		std::map<Uint8, bool> released_buttons_;
	public:
		Input() {
			SDL_Joystick *joy;

			if(SDL_NumJoysticks()>0){
				joy=SDL_JoystickOpen(0);
			}
		}

		void beginNewFrame();

		void keyDownEvent(const SDL_Event& event);
		void keyUpEvent(const SDL_Event& event);

		void joyButtonDownEvent(const SDL_Event& event);
		void joyButtonUpEvent(const SDL_Event& event);

		bool wasKeyPressed(SDLKey key);
		bool wasKeyReleased(SDLKey key);
		bool isKeyHeld(SDLKey key);

		bool wasJoyButtonPressed(Uint8 button);
		bool wasJoyButtonReleased(Uint8 button);
		bool isJoyButtonHeld(Uint8 button);
};

#endif // INPUT_H_

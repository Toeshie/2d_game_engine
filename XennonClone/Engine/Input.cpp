#include "Input.h"
#include "SDL.h"
#include "InitError.h"
#include "MathHelper.h"

SDL_Event Input::event_;

// Static game controller variables
static SDL_GameController* m_GameController = nullptr;
constexpr int JOYSTICK_DEAD_ZONE = 8000;
constexpr int JOYSTICK_MAX = 25000;

Input::Input()
{
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		// Failed init
		return;
	}

	if (SDL_NumJoysticks() >= 1)
	{
		m_GameController = SDL_GameControllerOpen(0);
	}
}

void Input::receive_input_event(SDL_Event& ev)
{
	event_ = ev;
}

SDL_Event Input::get_input_event()
{
	return event_;
}

int Input::get_right_axis_value()
{
	int gamepadRightAxis = SDL_GameControllerGetAxis(m_GameController, SDL_CONTROLLER_AXIS_LEFTX);
	MathHelper::clamp_int_no_return(gamepadRightAxis, -JOYSTICK_MAX, JOYSTICK_MAX);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D] ||
		gamepadRightAxis > JOYSTICK_DEAD_ZONE || SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
	{
		return 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT] || currentKeyStates[SDL_SCANCODE_A] || gamepadRightAxis < -JOYSTICK_DEAD_ZONE || SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
	{
		return -1;
	}
	return 0;
}

int Input::get_up_axis_value()
{
	int gamepadUpAxis = SDL_GameControllerGetAxis(m_GameController, SDL_CONTROLLER_AXIS_LEFTY);
	MathHelper::clamp_int_no_return(gamepadUpAxis, -JOYSTICK_MAX, JOYSTICK_MAX);

	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_W] ||
		gamepadUpAxis < -JOYSTICK_DEAD_ZONE || SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_DPAD_UP))
	{
		return 1;
	}
	else if (currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S] || gamepadUpAxis > JOYSTICK_DEAD_ZONE || SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
	{
		return -1;
	}
	return 0;
}

bool Input::is_fire_key_down()
{
	short isGamepadButtonPressed = SDL_GameControllerGetButton(m_GameController, SDL_CONTROLLER_BUTTON_A);
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	return currentKeyStates[SDL_SCANCODE_SPACE] || isGamepadButtonPressed;
}


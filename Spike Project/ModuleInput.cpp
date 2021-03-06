#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"


ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_AXES; ++i)
		axes[i] = KEY_IDLE;
	for (uint i = 0; i < MAX_BUTTONS; ++i)
		buttons[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAMECONTROLLER could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			controller_init = true;
			break;
		}
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	for (int i = 0; i < SDL_NumJoysticks(); i++)
	{
		if (SDL_IsGameController(i))
		{
			controller = SDL_GameControllerOpen(i);
			controller_init = true;
			break;
		}
	}
	
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	

	axes[SDL_CONTROLLER_AXIS_LEFTX] = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	axes[SDL_CONTROLLER_AXIS_LEFTY] = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);



	button[SDL_CONTROLLER_BUTTON_A] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
	button[SDL_CONTROLLER_BUTTON_B] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B);
	button[SDL_CONTROLLER_BUTTON_Y] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y);
	button[SDL_CONTROLLER_BUTTON_X] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X);
	button[SDL_CONTROLLER_BUTTON_BACK] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_BACK);
	button[SDL_CONTROLLER_BUTTON_GUIDE] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_GUIDE);
	button[SDL_CONTROLLER_BUTTON_START] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_START);
	button[SDL_CONTROLLER_BUTTON_LEFTSTICK] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSTICK);
	button[SDL_CONTROLLER_BUTTON_RIGHTSTICK] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
	button[SDL_CONTROLLER_BUTTON_LEFTSHOULDER] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
	button[SDL_CONTROLLER_BUTTON_RIGHTSHOULDER] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
	button[SDL_CONTROLLER_BUTTON_DPAD_UP] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP);
	button[SDL_CONTROLLER_BUTTON_DPAD_DOWN] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	button[SDL_CONTROLLER_BUTTON_DPAD_LEFT] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	button[SDL_CONTROLLER_BUTTON_DPAD_RIGHT] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	button[SDL_CONTROLLER_BUTTON_MAX] = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_MAX);

	if (keyboard[SDL_SCANCODE_ESCAPE] ||
		buttons[SDL_CONTROLLER_BUTTON_B])
		return update_status::UPDATE_STOP;

	if (keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && 
		keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_IDLE && !App->player->godmode) 
	{
		App->player->godmode = true;
	}
	else if (keyboard[SDL_SCANCODE_F5] == KEY_STATE::KEY_DOWN && 
		keyboard[SDL_SCANCODE_LALT] == KEY_STATE::KEY_IDLE && App->player->godmode) 
	{
		App->player->godmode = false;
	}

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}
	
	for (int i = 0; i < MAX_BUTTONS; ++i)
	{
		if (button[i] == 1)
		{
			if (buttons[i] == KEY_IDLE)
				buttons[i] = KEY_DOWN;
			else
				buttons[i] = KEY_REPEAT;
		}
		else
		{
			if (buttons[i] == KEY_REPEAT || buttons[i] == KEY_DOWN)
				buttons[i] = KEY_UP;
			else
				buttons[i] = KEY_IDLE;
		}
	}

	if (axes[SDL_CONTROLLER_AXIS_LEFTX] < -5000)
	{
		if (axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_IDLE || axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_X_RIGHT_DOWN || axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_X_RIGHT_REPEAT)
		axis[SDL_CONTROLLER_AXIS_LEFTX] = AXIS_X_LEFT_DOWN;
		else axis[SDL_CONTROLLER_AXIS_LEFTX] = AXIS_X_LEFT_REPEAT;
	}
	
	else if (axes[SDL_CONTROLLER_AXIS_LEFTX] > 5000)
	{
		if (axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_IDLE || axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_X_LEFT_DOWN || axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_X_LEFT_REPEAT)
		axis[SDL_CONTROLLER_AXIS_LEFTX] = AXIS_X_RIGHT_DOWN;
		else axis[SDL_CONTROLLER_AXIS_LEFTX] = AXIS_X_RIGHT_REPEAT;
	}
	else axis[SDL_CONTROLLER_AXIS_LEFTX] = AXIS_IDLE;


	if (axes[SDL_CONTROLLER_AXIS_LEFTY] < -5000)
	{
		if(axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_IDLE || axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_Y_DOWN_DOWN || axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_Y_DOWN_REPEAT)
		axis[SDL_CONTROLLER_AXIS_LEFTY] = AXIS_Y_UP_DOWN;
		else axis[SDL_CONTROLLER_AXIS_LEFTY] = AXIS_Y_UP_REPEAT;
	}
	else if (axes[SDL_CONTROLLER_AXIS_LEFTY] > 5000)
	{
		if (axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_IDLE || axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_Y_UP_DOWN || axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_Y_UP_REPEAT)
		axis[SDL_CONTROLLER_AXIS_LEFTY] = AXIS_Y_DOWN_DOWN;
		else axis[SDL_CONTROLLER_AXIS_LEFTY] = AXIS_Y_DOWN_REPEAT;
	}
	else axis[SDL_CONTROLLER_AXIS_LEFTY] = AXIS_IDLE;
	
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	if (controller != nullptr)
	{
		SDL_GameControllerClose(controller);
		controller = nullptr;
		controller_init = false;
	}
	
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	LOG("Quitting SDL game controller subsystem");
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}
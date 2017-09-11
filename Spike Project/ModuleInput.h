#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_gamecontroller.h"

#define MAX_KEYS 300
#define MAX_AXES 2
#define MAX_BUTTONS 20

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

enum AXIS_STATE
{
	AXIS_IDLE = 0,
	AXIS_X_LEFT_DOWN,
	AXIS_X_LEFT_REPEAT,
	AXIS_X_RIGHT_DOWN,
	AXIS_X_RIGHT_REPEAT,
	AXIS_Y_DOWN_DOWN,
	AXIS_Y_DOWN_REPEAT,
	AXIS_Y_UP_DOWN,
	AXIS_Y_UP_REPEAT
};

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];
	AXIS_STATE axis[MAX_AXES];
	KEY_STATE buttons[MAX_BUTTONS];

	SDL_GameController *controller = nullptr;

	Sint16 axes[MAX_AXES];
	Uint8 button[MAX_BUTTONS];
	bool controller_init = false;
};

#endif // __ModuleInput_H__
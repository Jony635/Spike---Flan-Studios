#ifndef INGAMESCENE
#define INGAMESCENE

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleFood.h"



struct SDL_Texture;

class Pan{

public:
	uint speed = 0;
	Animation Anim;
	iPoint position;
	float T = 0.0f;
	int A = 0;
	float Timer = 0.0f;
	float FoodSpawnTimer = 0.0f;

	bool IsPanEmpty();

	Pan() {}
	~Pan() {}
};

bool Pan::IsPanEmpty()
{
	bool result = true;
	for (int i = 0; i < MAXFOOD; ++i)
	{
		if (App->food->FOOD[i].State == FoodState::ON_PAN)
		{
			result = false;
			break;
		}
	}
	return result;
}

class InGameScene : public Module
{
public:
	InGameScene();
	~InGameScene();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* background = nullptr;
	SDL_Texture* PanText = nullptr;
	Animation PanAnim;
	Animation PanThrowingFood;
	Pan* Panptr = nullptr;
};

#endif

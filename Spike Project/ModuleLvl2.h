#ifndef __MODULELVL2_H__
#define __MODULELVL2_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define NUM_COLLIDERSWALL 100
#define NUM_COLLIDERSWATER 100
#define MAX_COLLIDER_DOWNSTAIRS 20
#define NUM_COLLIDERSANTIBULLET 4
#define NUM_COLLIDERSANTIENEMY 2

struct SDL_Texture;

class Pan{

public:
	uint speed = 0;
	Animation Anim;
	iPoint position;
	float velo = 0;
	int amplitud = 0;
	float timer = 0;

	Pan() {}
	~Pan() {}
};
class ModuleLvl2 : public Module
{
public:
	ModuleLvl2();
	~ModuleLvl2();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* background = nullptr;
	SDL_Texture* PanText = nullptr;
	Animation PanAnim;
	Pan* Panptr = nullptr;
};

#endif

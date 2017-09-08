#ifndef MODULEFOOD
#define MODULEFOOD

#include "Globals.h"
#include "Animation.h"
#include "Module.h"

enum FoodTypes 
{
	NO_TYPE,
	PINEAPPLE,
	ONION,
	POOL_BALL,
	SAUSAGE,
	EGG,
	CHICKEN,
	COOKIE,
	NACHO,
	CANDY
};

class Food {
public:
	FoodTypes Type = FoodTypes::NO_TYPE;
	uint speed = 0;
	Animation Anim;

	Food(FoodTypes type, uint speed) : Type(type), speed(speed) {}
	~Food(){}
};

class ModuleFood :: public Module{
public:
	ModuleFood(){}
	~ModuleFood(){}
	Update(){}
	Clean(){}
	Start(){}
};


#endif
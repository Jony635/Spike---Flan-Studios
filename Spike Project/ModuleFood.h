#ifndef MODULEFOOD
#define MODULEFOOD

#include "Globals.h"
#include "Animation.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "p2Point.h"

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

enum FoodState
{
	NO_STATE,
	ON_PAN,
	ON_AIR,
	SPIKED,
	LOST
};

class Food {
public:
	FoodTypes Type = FoodTypes::NO_TYPE;
	uint speed = 0;
	iPoint position = { 0,0 };
	Animation Anim;
	FoodState State = FoodState::NO_STATE;
	Collider* col = nullptr;
	
	Food(){}
	Food(FoodTypes type, uint speed) : Type(type), speed(speed) {}
	~Food(){}

};

class ModuleFood : public Module{
public:
	ModuleFood();
	~ModuleFood();
	bool Start();
	update_status Update();
	bool CleanUp();
	void AddFood(FoodTypes FoodType, uint speed, iPoint position);
	void OnCollision(Collider* c1, Collider* c2);

	Food FOOD[50]; //En el Start se inicializa
	void ClearFood();
	void BlitFood();
	void RelocateFruitsOnPan();

	SDL_Texture* FoodTexts = nullptr;

	Animation PineApple;
	Animation Onion;
	Animation Pool_Ball;
	Animation Sausage;
	Animation Egg;
	Animation Chicken;
	Animation Cookie;
	Animation Nacho;
	Animation Candy;
};


#endif
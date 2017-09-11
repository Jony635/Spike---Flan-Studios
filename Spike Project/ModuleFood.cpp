#include "ModuleFood.h"
#include "Application.h"

ModuleFood::ModuleFood()
{
	//PineApple.PushBack({});
}
ModuleFood::~ModuleFood() {}


bool ModuleFood::Start() 
{
	FoodTexts=App->textures->Load("Resources/Spike/spike_food.png");
	ClearFood();
	return true;
}

update_status ModuleFood::Update()
{





	return update_status::UPDATE_CONTINUE;
}

bool ModuleFood::CleanUp()
{
	ClearFood();
	return true;
}
void ModuleFood::ClearFood()
{
	for (int i = 0; i < 50; ++i)
	{
		FOOD[i].Type = FoodTypes::NO_TYPE;
	}
}

void ModuleFood::AddFood(FoodTypes FoodType, uint speed)
{
	for (int i = 0; i < 50; ++i)
	{
		if (FOOD[i].Type == FoodTypes::NO_TYPE)
		{
			FOOD[i].Type = FoodType;
			FOOD[i].speed = speed;
			FOOD[i].State = FoodState::ON_PAN;
			//FOOD[i].Anim = ;
		}
		else if (i = 49)
		{
			LOG("Not enough space in Food Array");
		}
		break;
	}
}
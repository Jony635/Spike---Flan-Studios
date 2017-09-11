#include "ModuleFood.h"
#include "Application.h"
#include "ModuleCollision.h"

ModuleFood::ModuleFood()
{
	Chicken.PushBack({19, 23, 54, 38});
	Nacho.PushBack({109,24,42,36});
	Candy.PushBack({190,24,40,37});
	PineApple.PushBack({273, 24, 45,42});
	Cookie.PushBack({26,117, 40,41});
	Sausage.PushBack({102, 128, 52, 19});
	Onion.PushBack({182,113,56,50});
	Pool_Ball.PushBack({266,109,53,54});

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
			switch (FoodType)
			{
			case CHICKEN:
				FOOD[i].col = App->collision->AddCollider(Chicken.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Chicken;
				break;
			case NACHO:
				FOOD[i].col = App->collision->AddCollider(Nacho.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Nacho;
				break;
			case CANDY:
				FOOD[i].col = App->collision->AddCollider(Candy.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Candy;
				break;
			case PINEAPPLE:
				FOOD[i].col = App->collision->AddCollider(PineApple.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = PineApple;
				break;
			case COOKIE:
				FOOD[i].col = App->collision->AddCollider(Cookie.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Cookie;
				break;
			case SAUSAGE:
				FOOD[i].col = App->collision->AddCollider(Sausage.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Sausage;
				break;
			case ONION:
				FOOD[i].col = App->collision->AddCollider(Onion.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Onion;
				break;
			case POOL_BALL:
				FOOD[i].col = App->collision->AddCollider(Pool_Ball.frames[0], COLLIDER_FOOD, App->food);
				FOOD[i].Anim = Pool_Ball;
				break;
			}
		}
		else if (i = 49)
		{
			LOG("Not enough space in Food Array");
		}
		break;
	}
}

void ModuleFood::OnCollision(Collider* c1, Collider* c2)
{
	if (c2->type == COLLIDER_WALL)
	{

	}
}
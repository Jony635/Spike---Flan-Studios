#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"

ModulePowerUp::ModulePowerUp()
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		powerups[i] = nullptr;
	}

	binocular.PushBack({ 155,70,16,16 });
	binocular.PushBack({ 179,70,16,16 });
	binocular.PushBack({ 155,93,16,16 });
	binocular.PushBack({ 178,93,16,16 });
	binocular.speed = 0.08f;

	bulletproof_vest.PushBack({ 54,71,14,14 });
	bulletproof_vest.PushBack({ 77,71,14,14 });
	bulletproof_vest.PushBack({ 54,93,14,14 });
	bulletproof_vest.PushBack({ 77,93,14,14 });
	bulletproof_vest.speed = 0.08f;

	gasoline.PushBack({ 151,27,12,15 });
	gasoline.PushBack({ 175,27,12,15 });
	gasoline.PushBack({ 152,50,12,15 });
	gasoline.PushBack({ 176,50,12,15 });
	gasoline.speed = 0.08f;

	grenadex4.PushBack({ 99,76,23,15 });
	grenadex4.PushBack({ 125,76,23,15 });
	grenadex4.PushBack({ 99,93,23,15 });
	grenadex4.PushBack({ 125,93,23,15 });
	grenadex4.speed = 0.08f;

	grenadex5.PushBack({ 126,3,21,16 });
	grenadex5.PushBack({ 102,3,21,16 });	
	grenadex5.PushBack({ 150,3,21,16 });
	grenadex5.PushBack({ 175,4,21,16 });
	grenadex5.speed = 0.08f;

	medal.PushBack({ 101,27,16,10 });
	medal.PushBack({ 124,27,16,10 });
	medal.PushBack({ 101,55,16,10 });
	medal.PushBack({ 124,54,16,10 });
	medal.speed = 0.08f;

	medal_of_honor.PushBack({ 35,0,10,16 });
	medal_of_honor.PushBack({ 47,0,10,16 });
	medal_of_honor.PushBack({ 59,0,10,16 });
	medal_of_honor.PushBack({ 71,0,10,16 });
	medal_of_honor.speed = 0.08f;

	barrel.PushBack({ 203,73,12,16 });
	barrel.PushBack({ 228,73,12,16 });
	barrel.PushBack({ 204,96,12,16 });
	barrel.PushBack({ 228,96,12,16 });
	barrel.speed = 0.08f;

	bag.PushBack({ 6,23,12,15 });
	bag.PushBack({ 32,23,12,15 });
	bag.PushBack({ 6,46,12,15 });
	bag.PushBack({ 33,47,12,15 });
	bag.speed = 0.08f;

	ally_captured.PushBack({ 176,122,16,22 });
	ally_captured.PushBack({ 193,122,16,22 });
	ally_captured.speed = 0.02f;

}

ModulePowerUp::~ModulePowerUp()
{}

// Load assets
bool ModulePowerUp::Start()
{
	LOG("Loading power ups");
	graphics = App->textures->Load("Resources/Animations/Items.png");

	return true;
}

// Unload assets
bool ModulePowerUp::CleanUp()
{
	LOG("Unloading power ups");
	App->textures->Unload(graphics);

	// Unload fx

	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModulePowerUp::Update()
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		if (powerups[i] != nullptr && !powerups[i]->hidden)
		{
			
		}
	}

	return UPDATE_CONTINUE;
}


PowerUp* ModulePowerUp::AddPowerUp(/*const PowerUp_Types type*/ int x, int y, bool hidden, char* label) {

	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		if (powerups[i] == nullptr)
		{
			PowerUp* powerup = new PowerUp();
			SDL_Rect col;
			col.x = x;
			col.y = y;
			switch(1)
			{
			
			}
			powerup->position.x = x;
			powerup->position.y = y;
			powerup->collider = App->collision->AddCollider(col, COLLIDER_POWERUP, this);
			
			powerup->hidden = hidden;
			if (label != "null") {
				powerup->label = label;
			}
			powerups[i] = powerup;
			return powerups[i];
			break;
		}
	}
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUP; ++i)
	{
		// Always destroy particles that collide
		if (powerups[i] != nullptr && powerups[i]->collider == c1)
		{
			if (c2->type == COLLIDER_PLAYER && !powerups[i]->hidden)
			{
				App->audio->PlaySound("Resources/Audio/Sound Effects/Grenades_Powerups Taken.wav");
				switch (1)
				{
				
				}
			}
			else if (c2->type == COLLIDER_PLAYER_GRENADE_EXPL && powerups[i]->hidden)
			{
				powerups[i]->hidden = false;
			}
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

PowerUp::PowerUp()
{
	position.SetToZero();
}

PowerUp::~PowerUp()
{
	if (collider != nullptr)
		App->collision->EraseCollider(collider);
}
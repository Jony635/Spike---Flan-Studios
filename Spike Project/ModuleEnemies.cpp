#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "ModulePlayer.h"
#include <time.h>
#include <stdlib.h>
#include "ModulePowerUp.h"
#include "ModuleAudio.h"

#define SPAWN_MARGIN 50

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("Resources/Sprites/Enemies/All_Enemies.png");

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].y > App->render->camera.y - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", queue[i].y);
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	srand(time(0));
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->position.y < -2880 + SCREEN_HEIGHT)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
		if (enemies[i] != nullptr) enemies[i]->Move();
	}
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.y>App->render->camera.y + SCREEN_HEIGHT + SPAWN_MARGIN)
			{
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type!=ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = ENEMY_TYPES::NO_TYPE;
			queue[i].x = 0;
			queue[i].y = 0;

		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y, char* cpath)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			queue[i].cpath = cpath;
			ret = true;
			break;
		}
	}

	return ret;
}

uint ModuleEnemies::Enemies_Alive() {
	uint enemies_alive = 0;
	for (uint i = 0; i < MAX_ENEMIES; i++)
	{
		if (enemies[i] != nullptr) {
			enemies_alive++;
		}
	}
	return enemies_alive;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	if (!App->player->win)
	{
		for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

		if (i != MAX_ENEMIES)
		{
			if (info.y < App->player->position.y+SPAWN_MARGIN)
			{
				switch (info.type)
				{
				
				}
			}
		}
	}
}


void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			if (enemies[i]->type != ENEMY_TYPES::RUNNER && enemies[i]->type != ENEMY_TYPES::MOTORBIKE && enemies[i]->type != ENEMY_TYPES::CAR && enemies[i]->type != ENEMY_TYPES::TRUCK) //Los runner son inmortales
			{
				if ((c2->type == COLLIDER_PLAYER_SHOT || c2->type == COLLIDER_PLAYER_GRENADE_EXPL) && c1->enemytype != BOSSGRENADE && c1->enemytype != HOLE && c1->enemytype!=KNIFE && c1->enemytype!=BUNKER) //Si se les dispara o les explota una bomba y no son el boss grenade
				{
					if (c1->enemytype != ENEMY_TYPES::BOSSLVL1)
					{
						int spawn_Bag_Barrel = rand() % 20;
						switch (spawn_Bag_Barrel)
						{
						case 0:
							App->powerup->AddPowerUp(PowerUp_Types::BAG, enemies[i]->position.x, enemies[i]->position.y);
							break;
						case 7:
							App->powerup->AddPowerUp(PowerUp_Types::BARREL, enemies[i]->position.x, enemies[i]->position.y);
							break;
						default:
							break;
						}


						App->player->score += 150;
						App->audio->PlaySound("Resources/Audio/Sound Effects/Enemy Died.wav");
						App->particles->AddParticle(App->particles->die_Grey, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_DIE);
						delete enemies[i];
						enemies[i] = nullptr;
					}

					else //BossLvl1
					{
						int spawn_Bag_Barrel = rand() % 3;
						switch (spawn_Bag_Barrel)
						{
						case 0:
							App->powerup->AddPowerUp(PowerUp_Types::BAG, enemies[i]->position.x, enemies[i]->position.y);
							break;
						case 1:
							App->powerup->AddPowerUp(PowerUp_Types::BARREL, enemies[i]->position.x, enemies[i]->position.y);
							break;
						default:
							break;
						}

							App->player->score += 2000;
							App->audio->PlaySound("Resources/Audio/Sound Effects/Enemy Died.wav");
							App->particles->AddParticle(App->particles->die_Green, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_DIE);
							delete enemies[i];
							enemies[i] = nullptr;

							break;
						
					}
				}
				else if (c1->enemytype == BOSSGRENADE && c2->enemytype == BOSSGRENADE)
				{
					enemies[i]->setMove(false);
				}
				else if (c1->enemytype == BOSSGRENADE && c2->type == COLLIDER_PLAYER_GRENADE_EXPL) //Si es el bombas
				{
					int spawn_Bag_Barrel = rand() % 3;
					switch (spawn_Bag_Barrel)
					{
					case 0:
						App->powerup->AddPowerUp(PowerUp_Types::BAG, enemies[i]->position.x, enemies[i]->position.y);
						break;
					case 1:
						App->powerup->AddPowerUp(PowerUp_Types::BARREL, enemies[i]->position.x, enemies[i]->position.y);
						break;
					default:
						break;
					}
					App->player->score += 300;
					App->particles->AddParticle(App->particles->die_Green, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_DIE);
					App->audio->PlaySound("Resources/Audio/Sound Effects/Enemy Died.wav");
					delete enemies[i];
					enemies[i] = nullptr;

				}
				else if (c1->enemytype == HOLE && c2->type == COLLIDER_PLAYER_GRENADE_EXPL)
				{
					App->player->score += 150;
					App->particles->AddParticle(App->particles->die_Grey, enemies[i]->position.x, enemies[i]->position.y, COLLIDER_DIE);
					App->audio->PlaySound("Resources/Audio/Sound Effects/Enemy Died.wav");
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			if ((c2->type == COLLIDER_WALL || c2->type == COLLIDER_ANTIENEMY) && c1->enemytype != ENEMY_TYPES::BOSSLVL1 && c1->enemytype!= ENEMY_TYPES::BOSSGRENADE
				&& enemies[i]->type != ENEMY_TYPES::RUNNER && enemies[i]->type != ENEMY_TYPES::MOTORBIKE && enemies[i]->type != ENEMY_TYPES::CAR && enemies[i]->type != ENEMY_TYPES::TRUCK 
				&& enemies[i]->type != ENEMY_TYPES::BUNKER && enemies[i]->type != ENEMY_TYPES::KNIFE)
			{
				AddEnemy(enemies[i]->type, enemies[i]->position.x, enemies[i]->position.y - 200, enemies[i]->cpath);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}
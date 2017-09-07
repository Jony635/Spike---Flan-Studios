#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleLvl2.h"
#include "ModuleEnemies.h"
#include "ModuleWelcome.h"
#include "ModulePowerUp.h"

#include<stdio.h>


ModulePlayer::ModulePlayer()
{
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	if(font_score==-1)
	font_score = App->fonts->Load("Resources/ui/Alphabet.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'·$%&/()-.€@ASD_GHJ", 6);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");


	return true;
}

// Update: draw background
update_status ModulePlayer::Update() {

	

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	


	
}
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleLvl2.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePowerUp.h"
#include "ModuleSecretAreas.h"

ModuleLvl2::ModuleLvl2(){
	//stair visible
	stair.PushBack({ 0, 0, 16, 16 });
	stair.loop = false;
	stair.speed = 0.02f;

	//stair not visible
	stairinv.PushBack({ 21, 19, 6, 6 });
	stairinv.loop = false;
	stairinv.speed = 0.02f;

	current_stair1_animation = &stairinv;
	current_stair2_animation = &stairinv;
	current_stair3_animation = &stairinv;
	current_stair4_animation = &stairinv;
	current_stair5_animation = &stairinv;
	current_stair6_animation = &stairinv;
}

ModuleLvl2::~ModuleLvl2(){}

bool ModuleLvl2::Start() {

	LOG("Loading main scene");
	//Textures
	App->textures->Enable();
	background = App->textures->Load("Resources/Spike/spike_backgrownd.png");//foto del fondo
	//items = App->textures->Load("Resources/Animations/Items.png");//foto del fondo
	
	//Enables & Disables
	/*App->audio->Enable();
	
	App->player->Enable();
	App->collision->Enable();
	App->particles->Enable();
	App->powerup->Enable();*/

	
	
	return true;
}

update_status ModuleLvl2::Update(){

	//Render Map
	App->render->Blit(background, 0, - SCREEN_HEIGHT, NULL);
	

	////Fade to black to next lvl
	//if (App->input->keyboard[SDL_SCANCODE_F2]) {
	//	App->fade->FadeToBlack(this, App->endlvl2, 0);
	//}

	return UPDATE_CONTINUE;

}

bool ModuleLvl2::CleanUp(){

	LOG("Unloading lvl2 scene");

	//Disables
	App->particles->Disable();
	App->powerup->Disable();
	App->enemies->Disable();
	App->textures->Disable();
	App->collision->Disable();
	App->audio->Disable();
	App->player->Disable();

	//Unload textures
	if(background!=nullptr)
	App->textures->Unload(background);
	background = nullptr;
	if(items!=nullptr)
	App->textures->Unload(items);
	items = nullptr;
	return true;
}


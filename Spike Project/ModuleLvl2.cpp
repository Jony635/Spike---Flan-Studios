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


ModuleLvl2::ModuleLvl2(){
	//stair visible
	PanAnim.PushBack({11, 11, 313, 152});
}

ModuleLvl2::~ModuleLvl2(){}

bool ModuleLvl2::Start() {

	LOG("Loading main scene");
	//Textures
	App->textures->Enable();
	background = App->textures->Load("Resources/Spike/spike_backgrownd.png");//foto del fondo
	
	//Creating the Pan:
	PanText = App->textures->Load("Resources/Spike/Pan.png");
	Panptr = new Pan();
	Panptr->Anim = PanAnim;
	Panptr->position = { (SCREEN_WIDTH / 2)+500, -172 };
	Panptr->A = 200;
	Panptr->F = 0.5;

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
	Panptr->Timer += 0.01;

	Panptr->position.x = 125+ Panptr->A * cos(((2*PI)/5)-2 * PI* Panptr->Timer);



	App->render->Blit(background, 0, - SCREEN_HEIGHT, NULL);
	App->render->Blit(PanText, Panptr->position.x, Panptr->position.y, &Panptr->Anim.GetCurrentFrame(), true);

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
	if(Panptr!=nullptr)
	delete Panptr;
	Panptr = nullptr;
	//Unload textures
	if(background!=nullptr)
	App->textures->Unload(background);
	background = nullptr;
	return true;
}


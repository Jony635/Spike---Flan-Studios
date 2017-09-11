#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "How_to_Play_Scene.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleFood.h"
#include "InGameScene.h"
#include "MenuScene.h"

#include <stdio.h>


How_to_Play_Scene::How_to_Play_Scene() {}

How_to_Play_Scene::~How_to_Play_Scene() {}

bool How_to_Play_Scene::Start() {

	LOG("Loading Welcome scene");

	//Enables and Disables
	App->textures->Enable();
	App->audio->Enable();

	//fonts
	font_high_score = App->fonts->Load("Resources/ui/Alphabetred.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'�$%&/()-.�@ASD_GHJ", 6);
	font_welcome_score = App->fonts->Load("Resources/ui/Alphabetwhite.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'�$%&/()-.�@ASD_GHJ", 6);

	HowtoTexture = App->textures->Load("Resources/Spike/spike_HTP.png");

	Menu_Options = MENU::PLAY;


	//Cameras positions
	App->render->camera.x = 0;
	App->render->camera.y = 0 - SCREEN_HEIGHT;
	//App->audio->Play("Resources/Audio/Themes_SoundTrack/Title Theme.ogg", true);
	//init stairs

	//restart things

	return true;
}

update_status How_to_Play_Scene::Update() {


	if (!App->fade->IsFading())
	{
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN ||
			(App->input->axis[SDL_CONTROLLER_AXIS_LEFTY]==AXIS_Y_DOWN_DOWN && App->input->axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_IDLE)||
			App->input->keyboard[SDL_SCANCODE_D]==KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_RIGHT]==KEY_DOWN ||
			(App->input->axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_X_RIGHT_DOWN && App->input->axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_IDLE))
		{
			if (Indicator == 0) Indicator = 1;
			else Indicator = 0;
			
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN ||
			(App->input->axis[SDL_CONTROLLER_AXIS_LEFTY]==AXIS_Y_UP_DOWN && App->input->axis[SDL_CONTROLLER_AXIS_LEFTX] == AXIS_IDLE) ||
			App->input->keyboard[SDL_SCANCODE_A] == KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_LEFT]==KEY_DOWN ||
			(App->input->axis[SDL_CONTROLLER_AXIS_LEFTX]==AXIS_X_LEFT_DOWN && App->input->axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_IDLE))
		{
			if (Indicator == 0) Indicator = 1;
			else Indicator = 0;
		}
	}
	if (Indicator == 0) ballPos = { 30, -98};
	else ballPos = { 237, -98 };
	

	//Render Map
	App->render->Blit(HowtoTexture, 0, 0 - SCREEN_HEIGHT, nullptr);
	App->render->Blit(App->food->FoodTexts, ballPos.x, ballPos.y, &App->food->Pool_Ball.frames[0]);
	//render scores
	/*sprintf(App->player->score_text, "%06d", App->player->score);
	sprintf(one_up_text, "%s", "up");
	sprintf(high_text, "%s", "high");
	sprintf(App->player->high_score_text, "%06d", App->player->highscore);

	App->fonts->BlitText(16, 16, font_welcome_score, App->player->score_text);
	App->fonts->BlitText(24, 8, font_welcome_score, one_up_text);
	App->fonts->BlitText(16, 8, font_welcome_score, "1");
	App->fonts->BlitText(104, 16, font_high_score, App->player->high_score_text);
	App->fonts->BlitText(112, 8, font_high_score, high_text);*/

	//Fade to black to next lvl
	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_STATE::KEY_DOWN ||
		App->input->buttons[SDL_CONTROLLER_BUTTON_A]==KEY_STATE::KEY_DOWN)
	{
		if (Indicator == 0)
		{
			App->fade->FadeToBlack(this, App->mainscene, 1);
		}
		else if (Indicator == 1)
		{
			App->fade->FadeToBlack(this, App->menu, 1);
		}
	}

	return UPDATE_CONTINUE;

}

bool How_to_Play_Scene::CleanUp() {

	LOG("Unloading welcome scene");

	//Unload textures
	if (HowtoTexture != nullptr) App->textures->Unload(HowtoTexture);
	HowtoTexture = nullptr;

	if (font_high_score != -1)
		App->fonts->UnLoad(font_high_score);
	font_high_score = -1;
	if (font_welcome_score != -1)
		App->fonts->UnLoad(font_welcome_score);
	font_welcome_score = -1;

	App->player->score = 0;

	Indicator = 0;

	//Disables
	App->audio->Disable();
	App->player->Disable();



	return true;
}


#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "MenuScene.h"
#include "InGameScene.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleFood.h"
#include "How_to_Play_Scene.h"

#include <stdio.h>


MenuScene::MenuScene() {}

MenuScene::~MenuScene() {}

bool MenuScene::Start() {

	LOG("Loading Welcome scene");

	//Enables and Disables
	App->textures->Enable();
	App->audio->Enable();
	App->food->Enable();
	//fonts
	font_high_score = App->fonts->Load("Resources/ui/Alphabetred.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'�$%&/()-.�@ASD_GHJ", 6);
	font_welcome_score = App->fonts->Load("Resources/ui/Alphabetwhite.png", "0123456789abcdefghiklmnoprstuvwxyq<HIGH=!'�$%&/()-.�@ASD_GHJ", 6);

	MenuTexture = App->textures->Load("Resources/Spike/spike_menu.png");

	Menu_Options = MENU::PLAY;
	
	
	//Cameras positions
	App->render->camera.x = 0;
	App->render->camera.y = 0-SCREEN_HEIGHT;
	//App->audio->Play("Resources/Audio/Themes_SoundTrack/Title Theme.ogg", true);
	//init stairs
	
	//restart things
	
	return true;
}

update_status MenuScene::Update() {


	if (!App->fade->IsFading())
	{
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_DOWN] == KEY_DOWN ||
			App->input->axis[SDL_CONTROLLER_AXIS_LEFTY]==AXIS_Y_DOWN_DOWN)
		{
			if (Indicator == 2)
			{
				Indicator = 0;
			}
			else Indicator++;
		}
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_DOWN ||
			App->input->buttons[SDL_CONTROLLER_BUTTON_DPAD_UP] == KEY_DOWN ||
			App->input->axis[SDL_CONTROLLER_AXIS_LEFTY] == AXIS_Y_UP_DOWN)
		{
			if (Indicator == 0)
			{
				Indicator = 2;
			}
			else Indicator--;
		}
	}
	if (Indicator == 0) ballPos = {21,-204-54};
	else if (Indicator == 1) ballPos = {21,-128-54};
	else ballPos = {21, -48-54};

	//Render Map
	App->render->Blit(MenuTexture, 0, 0 - SCREEN_HEIGHT, nullptr);
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
		App->input->buttons[SDL_CONTROLLER_BUTTON_A] == KEY_STATE::KEY_DOWN)
	{
		if (Indicator == 0)
		{
			App->fade->FadeToBlack(this, App->mainscene, 0);
		}
		else if (Indicator == 1)
		{
			App->fade->FadeToBlack(this, App->howtoscene, 1);
		}
		else return update_status::UPDATE_STOP;
	}

	return UPDATE_CONTINUE;

}

bool MenuScene::CleanUp() {

	LOG("Unloading welcome scene");

	//Unload textures
	if(MenuTexture!=nullptr) App->textures->Unload(MenuTexture);
	MenuTexture = nullptr;
	
	if(font_high_score!=-1)
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


#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "InGameScene.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "MenuScene.h"
#include "Globals.h"
#include "ModuleFood.h"
#include "How_to_Play_Scene.h"



Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = fonts = new ModuleFonts();
	modules[i++] = menu = new MenuScene();
	modules[i++] = howtoscene = new How_to_Play_Scene();
	modules[i++] = mainscene = new InGameScene();
	modules[i++] = food = new ModuleFood();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();
	modules[i++] = audio = new ModuleAudio();

}	

Application::~Application()
{
	for (int i = NUM_MODULES - 1; i >= 0; --i) {
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Deactivate modules here ----
	mainscene->Disable();
	howtoscene->Disable();
	collision->Disable();
	player->Disable();
	food->Disable();
	// ----------------------------

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i) {
		
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;
	}

	return ret;
}
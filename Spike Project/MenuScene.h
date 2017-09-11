#ifndef __MENU_H__
#define __MENU__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"



struct SDL_Texture;

class MenuScene : public Module
{
public:
	MenuScene();
	~MenuScene();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	enum MENU {
		PLAY,
		HOW_TO_PLAY,
		EXIT
	}Menu_Options;

	uint Indicator = 0;

	SDL_Texture* MenuTexture = nullptr;
	iPoint ballPos = { 0,0 };

	char one_up_text[3];
	char high_text[4];

	int font_high_score = -1;
	int font_welcome_score = -1;

	char* one_up;
	char* high;

};

#endif // __MODULELVL2_H__

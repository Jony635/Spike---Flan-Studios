#ifndef __HOW_TO_PLAY_H__
#define __HOW_TO_PLAY_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"



struct SDL_Texture;

class How_to_Play_Scene : public Module
{
public:
	How_to_Play_Scene();
	~How_to_Play_Scene();

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

	SDL_Texture* HowtoTexture = nullptr;
	iPoint ballPos = { 0,0 };

	char one_up_text[3];
	char high_text[4];

	int font_high_score = -1;
	int font_welcome_score = -1;

	char* one_up;
	char* high;

};

#endif

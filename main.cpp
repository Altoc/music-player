#include <iostream>
#include "music.h"

bool EXIT_STATUS;

std::vector<SDL_Event> FRAME_EVENTS;
std::vector<Button*> BUTTONS;
int FINGER_X;
int FINGER_Y;

void initializeSDL(){
	EXIT_STATUS=false;

	//Initialize SDL Mixer
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Failed to init SDL\n");
		exit(1);
	}
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	Mix_Volume(-1, MIX_MAX_VOLUME);
	MUSIC_HANDLER.loadSongs();
  //init SDL TTF
  if (TTF_Init() == -1){
    LOG("Failed to init TTF: " << TTF_GetError());
  }else
    LOG("TTF Loaded.");
  //load fonts
  FONT_MANAGER.fonts_["Arial24"] = TTF_OpenFont("fonts/arial.ttf", 24);
  if(FONT_MANAGER.fonts_["Arial24"] == nullptr){
    LOG("Font failed to load: " << TTF_GetError());
  }else
    LOG("Fonts Loaded.");
}

void catchInput(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		FRAME_EVENTS.push_back(e);
	}
}

void handleInput(){
	std::string mouseStr;
	for(int i = 0; i < FRAME_EVENTS.size(); i++){
		switch(FRAME_EVENTS[i].type){
			case SDL_FINGERDOWN:
				FINGER_X = FRAME_EVENTS[i].tfinger.x * WINDOW.getScreenResolutionWidth();
				FINGER_Y = FRAME_EVENTS[i].tfinger.y * WINDOW.getScreenResolutionHeight();
				for(auto &i : BUTTONS){
					if((FINGER_X >= i->getScreenDimensions()->x && FINGER_X <= i->getScreenDimensions()->x + i->getScreenDimensions()->w) && (FINGER_Y >= i->getScreenDimensions()->y && i->getScreenDimensions()->y + i->getScreenDimensions()->h)){
						LOG("Clicked a SongButton");
						i->action();
					}
				}
				//LOG("Mouse at: " << std::to_string(FINGER_X) << ", " << std::to_string(FINGER_Y));
				break;
			case SDL_QUIT:
				EXIT_STATUS = true;
				break;
		}
	}
	FRAME_EVENTS.clear();
}

void run(){
	while(!EXIT_STATUS){
		//Gather input
		catchInput();
		//Handle input
		handleInput();
		//rendering
		WINDOW.clearRender();
		WINDOW.updateRender();
	}
}

int main(int  argc, char** argv){
	//Set up SDL
	initializeSDL();
	LOG("SDL Initialized.");	

	//SDL_Color labelColor = {0, 0, 0};
	//WINDOW.addToRenderObjects(new Label(0, 0, "Test", "Arial24", labelColor));
	
	//create song buttons
	int songButtonX = 0;
	int songButtonY = 0;
	int xIncrement = 144;
	int yIncrement = 64;
	for(auto &j : MUSIC_HANDLER.getSongs()){
		BUTTONS.push_back(new SongButton(songButtonX, songButtonY, 128, 48, j));
		songButtonY += yIncrement;
		if(songButtonY > WINDOW.getScreenResolutionHeight() - yIncrement){
			songButtonY = 0;
			songButtonX += xIncrement;
		}
	}
	//add a stop music button
	BUTTONS.push_back(new StopMusicButton(WINDOW.getScreenResolutionWidth() * 0.85, WINDOW.getScreenResolutionHeight() * 0.85));
	//add buttons to the render list
	for(auto &i : BUTTONS)
		WINDOW.addToRenderObjects(i);

	//loop
	run();

	return 0;
}

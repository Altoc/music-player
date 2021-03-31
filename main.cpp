#include <iostream>
#include "music-selector.h"
int WINDOW_WIDTH = 720;
int WINDOW_HEIGHT = 240;
SDL_Window* WINDOW;

void initializeSDL(){
	WINDOW = SDL_CreateWindow("Ian's Music Thing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	//Initialize SDL Mixer
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		printf("Failed to init SDL\n");
		exit(1);
	}
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) < 0) {
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
//		exit(2);
	}
}

int main(int  argc, char** argv){
	//Set up SDL
	initializeSDL();

	//Set up music handler
	std::cerr<<"Loading musicH"<<std::endl;
	MusicHandler musicH;
	std::cerr<<"playSong()"<<std::endl;
	musicH.playSong("Terrible Tim - Brotherman Bill");

	//loop
	while(Mix_Playing(-1) > 0);

	return 0;
}

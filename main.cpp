#include <iostream>
#include "music-selector.h"
int WINDOW_WIDTH = 720;
int WINDOW_HEIGHT = 240;
SDL_Window* WINDOW;

bool EXIT_STATUS;

std::vector<SDL_Event> FRAME_EVENTS;

void initializeSDL(){
	WINDOW = SDL_CreateWindow("Ian's Music Thing", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

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
}

void catchInput(){
	SDL_Event e;
	while(SDL_PollEvent(&e)){
		FRAME_EVENTS.push_back(e);
	}
}

void handleInput(){
	for(int i = 0; i < FRAME_EVENTS.size(); i++){
		switch(FRAME_EVENTS[i].type){
			case SDL_QUIT:
				EXIT_STATUS = true;
				break;
		}
	}
}

void run(){
	while(!EXIT_STATUS){
		//Gather input
		catchInput();
		//Handle input
		handleInput();
	}
}

int main(int  argc, char** argv){
	//Set up SDL
	initializeSDL();

	//Set up music handler
	MusicHandler musicH;
	musicH.playSong("Throne_Room");

	//loop
	run();

	return 0;
}

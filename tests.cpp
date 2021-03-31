#include<iostream>
#include"SDL2/SDL_mixer.h"
#include"SDL2/SDL.h"

int main(){

	//SDL_setenv("SDL_AUDIODRIVER","alsa",0);
	//putenv((char *)"SDL_AUDIODRIVER=alsa");

	// start SDL with audio support
	if(SDL_Init(SDL_INIT_AUDIO)==-1) {
	    printf("SDL_Init: %s\n", SDL_GetError());
	    exit(1);
	}
	// Get current audio driver
	printf("Current audio driver: %s\n", SDL_GetCurrentAudioDriver());

	std::cout<<"Number of available audio drivers:" << SDL_GetNumAudioDrivers()<<std::endl;
	const char* driver_name = "pulseaudio";
	SDL_AudioInit(driver_name);

	printf("Current audio driver: %s\n", SDL_GetCurrentAudioDriver());

	// open 44.1KHz, signed 16bit, system byte order,
	//      stereo audio, using 1024 byte chunks
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
	    printf("Mix_OpenAudio: %s\n", Mix_GetError());
	    exit(2);
	}
}

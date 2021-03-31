#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<iterator>
#include"SDL2/SDL.h"
#include"SDL2/SDL_mixer.h"

class MusicHandler{
public:
	MusicHandler();
	~MusicHandler();

	void loadSongs();
	void playSong(std::string songKey);
private:
	std::map<std::string, Mix_Music*> songs_;
  std::string currentSong_;
}
;

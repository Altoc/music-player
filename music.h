#ifndef MUSIC_H_
#define MUSIC_H_

class MusicHandler;

extern MusicHandler MUSIC_HANDLER;

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<iterator>
#include"engine.h"

class MusicHandler{
public:
	MusicHandler();
	~MusicHandler();

	void loadSongs();
	void playSong(std::string songKey);
	void pauseMusic();

	//getters
	std::vector<std::string> getSongs();
private:
	std::map<std::string, Mix_Music*> songs_;
  std::string currentSong_;
};

class SongButton : public Button{
public:
  SongButton(int x, int y, int w, int h, std::string songKey);
  ~SongButton();

  void render();

  //action the button performs on press
  void action() override;
private:
  std::string songKey_;
};

class StopMusicButton : public Button{
public:
	StopMusicButton(int x, int y);
	~StopMusicButton();

	void render();

	void action() override;
private:

};

#endif

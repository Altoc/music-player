#include "music.h"

MusicHandler MUSIC_HANDLER;

//Rogue Functions

std::vector<std::string> stringToVector(std::string str, char charToSplitAt) {
	std::vector<std::string> result;
	int strIndex = 0;
	int indexOfLastSplit = 0;
	while (strIndex <= str.size()) {
		if (str[strIndex] == charToSplitAt || strIndex == str.size()) {
			std::string substr = str.substr(indexOfLastSplit, strIndex - indexOfLastSplit);
			result.push_back(substr);
			indexOfLastSplit = strIndex + 1;
		}
		strIndex++;
	}
	return result;
}

//MusicHandler Functions

MusicHandler::MusicHandler(){
  currentSong_ = "";
  //loadSongs();
}

MusicHandler::~MusicHandler(){

}

void MusicHandler::loadSongs(){
	std::string file = "song-list.csv";
	std::ifstream assetFile;
	std::string strLine;
	assetFile.open(file);
	if (assetFile.is_open()) {
		std::vector<std::string> songKeys;
		getline(assetFile, strLine);
		if (strLine != ""){
			songKeys = stringToVector(strLine, ',');
		}
		for (auto& key : songKeys) {
			if (songs_.find(key) == songs_.end()) {
				std::string songFile = "songs/" + key + ".mp3";
				songs_[key] = Mix_LoadMUS(songFile.c_str());
				if(!songs_[key])
					printf("Mix_LoadMus(\"%s\")", songFile.c_str());
			} else {
				std::cerr<<"MusicHandler::loadSongs() failed to load: "<<key<<std::endl;
			}
		}
		//open song
		for (std::map<std::string, Mix_Music*>::iterator songItr = songs_.begin(); songItr != songs_.end(); ++songItr) {
			if (songItr->second == nullptr) {
				std::cerr << "Failed to load song: [" << songItr->first << "]" << Mix_GetError() << std::endl;
			}
		}
	} else {
		std::cerr<<"Could not open file: "<<file<<std::endl;
	}
}

void MusicHandler::playSong(std::string songKey){
	std::cout<<"Playing " << songKey <<std::endl;
	Mix_HaltMusic();
	if(Mix_PlayingMusic() == 0){
		Mix_PlayMusic(songs_[songKey], -1);
		currentSong_ = songKey;
	}
}

void MusicHandler::pauseMusic(){
	Mix_HaltMusic();
	//Mix_Pause(-1);
}

std::vector<std::string> MusicHandler::getSongs(){
	std::vector<std::string> result;
	for(auto &i : songs_)
		result.push_back(i.first);
	return result;
}

/*	Song Button	*/

SongButton::SongButton(int x, int y, int w, int h, std::string songKey) : Button(x,y,w,h){
  LOG("Created SongButton");
  songKey_ = songKey;
  objectName_ = "SongButton";
  SDL_Color buttonLabelColor = {255, 255, 255};
	buttonLabel_ = new Label(x, y, songKey, "Arial24", buttonLabelColor);
}

SongButton::~SongButton(){

}

void SongButton::render(){
  SDL_SetRenderDrawColor(WINDOW.getRenderer(), 0, 0, 0, 255);
  SDL_RenderFillRect(WINDOW.getRenderer(), screenDimensions_);
  if(buttonLabel_ != nullptr)
    buttonLabel_->render();
}

void SongButton::action(){
  MUSIC_HANDLER.playSong(songKey_);
  LOG("Pressed SongButton, trying to play " << songKey_);
}

/*	STOP MUSIC BUTTON	*/

StopMusicButton::StopMusicButton(int x, int y) : Button(x, y, 128, 64){
  LOG("Created StopMusicButton");
  objectName_ = "StopMusicButton";
  SDL_Color buttonLabelColor = {255, 255, 255};
  buttonLabel_ = new Label(x, y, "PAUSE", "Arial24", buttonLabelColor);
}

StopMusicButton::~StopMusicButton(){
	
}

void StopMusicButton::render(){
  SDL_SetRenderDrawColor(WINDOW.getRenderer(), 0, 0, 0, 255);
  SDL_RenderFillRect(WINDOW.getRenderer(), screenDimensions_);
  if(buttonLabel_ != nullptr)
    buttonLabel_->render();
}

void StopMusicButton::action(){
	LOG("Performing stop music button action");
	MUSIC_HANDLER.pauseMusic();
}










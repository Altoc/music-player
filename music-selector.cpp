#include "music-selector.h"

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
  loadSongs();
}

MusicHandler::~MusicHandler(){

}

void MusicHandler::loadSongs(){
	std::string file = "song-list.csv";
	std::ifstream assetFile;
	std::string strLine;
	std::cerr<<"openning file"<<std::endl;
	assetFile.open(file);
	if (assetFile.is_open()) {
		std::vector<std::string> songKeys;
		getline(assetFile, strLine);
		if (strLine != ""){
			std::cerr<<"setting songKey"<<std::endl;
			songKeys = stringToVector(strLine, ',');
		}
		for (auto& key : songKeys) {
			if (songs_.find(key) == songs_.end()) {
				std::string songFile = "songs/" + key + ".mp3";
				std::cerr<<"Loading Music for: "<<key<<std::endl;
				//songs_[key] = Mix_LoadMUS(songFile.c_str());
				songs_[key] = Mix_LoadWAV(songFile.c_str());
				if(!songs_[key])
					printf("Mix_LoadMus(\"%s\")", songFile.c_str());
				std::cerr<<"song openned"<<std::endl;
			} else {
				std::cerr<<"MusicHandler::loadSongs() failed to load: "<<key<<std::endl;
			}
		}
		//open song
		std::cerr<<"Opening songs. Size of songs_:"<<songs_.size()<<std::endl;
		for (std::map<std::string, Mix_Music*>::iterator songItr = songs_.begin(); songItr != songs_.end(); ++songItr) {
			std::cerr<<"test"<<std::endl;
			if (songItr->second == nullptr) {
				std::cerr << "Failed to load song: [" << songItr->first << "]" << Mix_GetError() << std::endl;
			}
		}
	} else {
		std::cerr<<"Could not open file: "<<file<<std::endl;
	}
}

void MusicHandler::playSong(std::string songKey){
	Mix_HaltMusic();
	if(Mix_PlayingMusic() == 0){
		std::cout<<"Playing " << songKey <<std::endl;
		Mix_PlayMusic(songs_[songKey], 1);
		currentSong_ = songKey;
	}
}



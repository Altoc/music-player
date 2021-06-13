#ifndef ENGINE_H_
#define ENGING_H_

#define LOG(a) std::cerr<<a<<std::endl;

class WindowManager;
class FontManager;
class Texture;
class Object;
class Label;
class Button;
class SongButton;

extern WindowManager WINDOW;
extern FontManager FONT_MANAGER;

#include <iostream>
#include <map>
#include <vector>
#include"SDL2/SDL.h"
#include"SDL2/SDL_mixer.h"
#include"SDL2/SDL_image.h"
#include"SDL2/SDL_ttf.h"

class WindowManager{
public:
	WindowManager(int w, int h);
	~WindowManager();

	//renderer functions
	void clearRender();
	void updateRender();

	//mutators
	void addToRenderObjects(Object* obj);

	//getters
	const int& getScreenResolutionWidth();
	const int& getScreenResolutionHeight();
	SDL_Renderer* getRenderer();
private:
	int screenResolutionWidth_;
	int screenResolutionHeight_;
	SDL_Window* window_;
	SDL_Renderer* renderer_;
	std::vector<Object*> renderObjects_;
};

class FontManager{
public:
	FontManager();
	~FontManager();
	TTF_Font* getFont(std::string key);
	std::map<std::string, TTF_Font*> fonts_;
private:
};

class Texture{
public:
	Texture();
	~Texture();
	void freeTexture();
	bool loadImg(std::string path);
	bool loadFromRenderedText(std::string font, std::string text, SDL_Color textColor);

	SDL_Texture* getTexture();
	const int& getWidth(){return w_;}
	const int& getHeight(){return h_;}

private:
	SDL_Texture* texture_;
	int w_;
	int h_;
};

class Object{
public:
	Object();
	~Object();

	const std::string& getName();

	virtual void render();

	//getters
	SDL_Rect* getScreenDimensions();
protected:
	std::string objectName_;
	Texture* texture_;
	SDL_Rect* spriteDimensions_;
	SDL_Rect* screenDimensions_;
};

class Label : public Object{
public:
	Label(int x, int y, std::string text, std::string font, SDL_Color color);
	~Label();
private:
	std::string text_;
	std::string font_;
	SDL_Color color_;
};

class Button : public Object{
public:
	Button();
	Button(int x, int y, int w, int h);
	~Button();
	//action the button performs on press
	virtual void action() = 0;
protected:
	Label* buttonLabel_;
};

#endif

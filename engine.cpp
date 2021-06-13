#include "engine.h"

WindowManager WINDOW(720,380);
FontManager FONT_MANAGER;

/*	WINDOW MANAGER	*/
WindowManager::WindowManager(int w, int h) : screenResolutionWidth_(w), screenResolutionHeight_(h){
	window_ = SDL_CreateWindow("DnD Music Generator: Lost In A World Of Fantasy by Ian And Emilee", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);

	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	LOG("Display Mode: " + std::to_string(dm.w) + " " + std::to_string(dm.h));

	renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	LOG("WindowManager Initialized.");
}

WindowManager::~WindowManager(){

}

void WindowManager::clearRender(){
	SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer_);
}

void WindowManager::updateRender(){
	for(auto &i : renderObjects_){
		//LOG("Rendering: " << i->getName() );
		i->render();
	}
	SDL_RenderPresent(renderer_);	
	//LOG("Done rendering");
}

void WindowManager::addToRenderObjects(Object* obj){
	renderObjects_.push_back(obj);
}

const int& WindowManager::getScreenResolutionWidth(){
	return screenResolutionWidth_;
}

const int& WindowManager::getScreenResolutionHeight(){
	return screenResolutionHeight_;
}

SDL_Renderer* WindowManager::getRenderer(){
	return renderer_;
}

/*	FONT MANAGER	*/

FontManager::FontManager(){
	//initialized in main.cpp
}

FontManager::~FontManager(){

}

TTF_Font* FontManager::getFont(std::string key){
	return fonts_[key];
}

/*	TEXTURE	*/

Texture::Texture(){
	texture_ = nullptr;
}

void Texture::freeTexture(){
	if(texture_ != nullptr){
		SDL_DestroyTexture(texture_);
		texture_ = nullptr;
	}
}

Texture::~Texture(){
	freeTexture();
}

bool Texture::loadImg(std::string path){
	freeTexture();	//free a previous texture if it exists
	SDL_Texture* newTexture = nullptr;	//the final texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());	//Load the image at the supplied file path
	if (loadedSurface == nullptr) {
		std::cerr << "loadImg() failed to load image: " << IMG_GetError() << std::endl;
	}
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF)); //Color key the loaded image
		newTexture = SDL_CreateTextureFromSurface(WINDOW.getRenderer(), loadedSurface);
		if (newTexture == nullptr) {
			std::cerr << "loadImg() failed to create texture from surface: " << IMG_GetError() << std::endl;
		}
		else {
			w_ = loadedSurface->w;
			h_ = loadedSurface->h;
		}
		//free the surface, we dont need it b/c we have the texture now
		SDL_FreeSurface(loadedSurface);
	}
	texture_ = newTexture;
	return texture_ != nullptr;
}

bool Texture::loadFromRenderedText(std::string font, std::string text, SDL_Color textColor){
	freeTexture();	//free a previous texture if it exists
	SDL_Surface* textSurface = TTF_RenderText_Solid(FONT_MANAGER.getFont(font), text.c_str(), textColor);
	if (textSurface == nullptr) {
		std::cerr << "loadImg() failed to load textSurface:" << TTF_GetError() << std::endl;
	}
	else {
		texture_ = SDL_CreateTextureFromSurface(WINDOW.getRenderer(), textSurface);
		if (texture_ == nullptr) {
			std::cerr << "loadImg() failed to create texture from surface: " << IMG_GetError() << std::endl;
		}
		else {
			w_ = textSurface->w;
			h_ = textSurface->h;
		}
		//free the surface, we dont need it b/c we have the texture now
		SDL_FreeSurface(textSurface);
	}
	return texture_ != nullptr;
}

SDL_Texture* Texture::getTexture(){
	return texture_;
}

/*	OBJECT	*/

Object::Object(){
	texture_ = nullptr;
	spriteDimensions_ = nullptr;
	screenDimensions_ = nullptr;
}

Object::~Object(){

}

const std::string& Object::getName(){
	return objectName_;
}

void Object::render(){
	SDL_RenderCopy(WINDOW.getRenderer(), texture_->getTexture(), spriteDimensions_, screenDimensions_);
}

SDL_Rect* Object::getScreenDimensions(){
	return screenDimensions_;
}

/*	LABEL	*/

Label::Label(int x, int y, std::string text, std::string font, SDL_Color color) : text_(text), font_(font){
	objectName_ = "Label";
	color_ = color;
	texture_ = new Texture;
	texture_->loadFromRenderedText(font_, text_, color_);		
	spriteDimensions_ = nullptr;
	screenDimensions_ = new SDL_Rect;
	screenDimensions_->x = x;
	screenDimensions_->y = y;
	screenDimensions_->w = texture_->getWidth();
	screenDimensions_->h = texture_->getHeight();
}

Label::~Label(){

}

/*	BUTTON	*/

Button::Button(){
	objectName_ = "Button";
	texture_ = nullptr;
	spriteDimensions_ = nullptr;
	screenDimensions_ = nullptr;
	buttonLabel_ = nullptr;
}

Button::Button(int x, int y, int w, int h){
	objectName_ = "Button";
	texture_ = nullptr;
	spriteDimensions_ = nullptr;
	screenDimensions_ = new SDL_Rect;
	screenDimensions_->x = x;
	screenDimensions_->y = y;
	screenDimensions_->w = w;
	screenDimensions_->h = h;
	buttonLabel_ = nullptr;
}

Button::~Button(){

}













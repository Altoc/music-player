#!/bin/bash
#g++ main.cpp -o music-selector music-selector.cpp `sdl-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf ;
#g++ tests.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o tests ;
g++ main.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o music-player music-selector.cpp ;

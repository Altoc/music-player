#!/bin/bash
#g++ main.cpp -o music-selector music-selector.cpp `sdl-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_ttf ;
g++ tests.cpp -o tests `sdl-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_ttf ;

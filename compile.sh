#!/bin/bash
#g++ main.cpp -o music-selector music-selector.cpp `sdl-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf ;
#g++ tests.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o tests ;
#g++ -std=c++17 -Wno-psabi  main.cpp -w -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf -o music-player engine.cpp music-selector.cpp ;

g++ -std=c++17 -Wno-psabi main.cpp -o music engine.cpp music.cpp `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf ;

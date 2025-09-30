#pragma once
#include "Ogre.h"
#include <string>

class Labirynth {
	int numFilas, numColumnas;

	Ogre::SceneManager* mSM;
public:
	Labirynth(std::string filePath, Ogre::SceneManager* sceneManager);
};
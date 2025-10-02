#pragma once
#include "Ogre.h"
#include <string>

using namespace Ogre;

class Labirynth {
	int numFilas, numColumnas;
	Vector3 initPos;
	Ogre::SceneManager* mSM;

	const double GAME_UNIT = 5.0;
public:
	Labirynth(std::string filePath, Ogre::SceneManager* sceneManager, Vector3 topLeftcorner);
};
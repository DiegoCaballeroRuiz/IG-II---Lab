#include "Labirynth.h"
#include <fstream>
#include <iostream>

#include "WallCube.h"
#include "EmptyCube.h"

Labirynth::Labirynth(std::string filePath, Ogre::SceneManager* sceneManager, Vector3 topLeftCorner)
	: mSM(sceneManager), initPos(topLeftCorner)
{
	std::ifstream input("stage1.txt");
	
	input >> numFilas >> numColumnas;

	std::cout << numFilas << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

	for (int i = 0; i < numFilas; ++i) {
		std::string fila;
		std::getline(input, fila);

		for (int j = 0; j < numColumnas; ++j) {
			Vector3 pos;
			char c = fila[j];

			pos = initPos + Vector3(GAME_UNIT * j, 0, -GAME_UNIT * i);

			IG2Object* cube;
			if (c == 'x') cube = new WallCube(initPos, "cube" + std::to_string(i) + ":" + std::to_string(j), sceneManager);
			else cube = new EmptyCube(initPos, "cube" + std::to_string(i) + ":" + std::to_string(j), sceneManager);

			
		}
	}
}
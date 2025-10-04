#include "Labirynth.h"
#include <fstream>
#include <iostream>
#include <cmath>

#include "WallCube.h"
#include "EmptyCube.h"
#include "Globals.h"

Labirynth::Labirynth(std::string filePath, Ogre::SceneManager* sceneManager, Vector3 topLeftCorner)
	: mSM(sceneManager), initPos(topLeftCorner)
{
	std::ifstream input("stage1.txt");
	
	mSceneNode = mSM->getRootSceneNode();

	input >> numFilas >> numColumnas;
	walls = new bool[numFilas*numColumnas];
	//std::cout << numFilas << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";

	for (int i = 0; i <= numFilas; ++i) {
		std::string fila;
		std::getline(input, fila);

		for (int j = 0; j < numColumnas; ++j) {
			Vector3 pos;
			char c = fila[j];

			pos = initPos + Vector3(GAME_UNIT * j, 0, GAME_UNIT * i);

			IG2Object* cube;
			std::string name = "cube" + std::to_string(i) + ':' + std::to_string(j);
			auto cubeNode = mSM->createSceneNode(name);

			if (c == 'x') {
				cube = new WallCube(pos, sceneManager, cubeNode);
				walls[i * numFilas + j] = true;
			}
			else {
				cube = new EmptyCube(pos, sceneManager, cubeNode);
				walls[i * numFilas + j] = false;
			}
			
			cubeNode->setScale((GAME_UNIT/cubeNode->getScale())*CUBE_SIZE);
			cubeNode->showBoundingBox(true);
			mSceneNode->addChild(cubeNode);

			
		}
	}
}

Labirynth::~Labirynth(){
	delete[] walls;
}

bool 
Labirynth::freeSquare(Vector3 pos) {
	int x = std::trunc(pos.x), y = std::trunc(pos.z);
	x /= GAME_UNIT;
	y /= GAME_UNIT;
	return walls[x * numFilas + y];

}
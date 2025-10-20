#include "Labirynth.h"
#include <fstream>
#include <iostream>
#include <cmath>

#include "WallCube.h"
#include "EmptyCube.h"
#include "Globals.h"
#include "Hero.h"
#include "OgreLight.h"

Labirynth::Labirynth(std::string filePath, Ogre::SceneManager* sceneManager, Vector3 topLeftCorner, Hero*& hero)
	: mSM(sceneManager)
{
	std::ifstream input("stage1.txt");
	
	mSceneNode = mSM->getRootSceneNode();

	input >> numFilas >> numColumnas;
	walls = std::vector<std::vector<bool>>(numFilas);
	for (auto& v : walls)
		v = std::vector<bool>(numColumnas);

	for (int i = 0; i < numFilas; ++i) {
		for (int j = 0; j < numColumnas; ++j) {
			Vector3 pos;
			char c;
			input >> c;

			pos = initPos + Vector3(GAME_UNIT * j, 0, GAME_UNIT * i);

			IG2Object* cube;
			std::string name = "cube" + std::to_string(i) + ':' + std::to_string(j);
			auto cubeNode = mSM->createSceneNode(name);

			if (c == 'x') {
				cube = new WallCube(pos, sceneManager, cubeNode);
				walls[j][i] = true;
			}
			else if (c == 'h') {
				auto sinbadNode = mSM->createSceneNode("Hero");
				hero = new Hero(pos, Vector3(), mSM, sinbadNode, this);
				mSceneNode->addChild(sinbadNode);
				sinbadNode->showBoundingBox(true);
				sinbadNode->setScale((GAME_UNIT / sinbadNode->getScale()) * SINBAD_SIZE);
				
				mLight = mSM->createLight("spotlight");
				mLight->setType(Light::LT_SPOTLIGHT);
				mLight->setDiffuseColour(ColourValue::Red);

				auto lightNode = sinbadNode->createChildSceneNode();
				lightNode->setDirection(Vector3(0, -1, 0));
				lightNode->setPosition(pos + Vector3(0, 70, 0));
				lightNode->attachObject(mLight);

				cube = new EmptyCube(pos, sceneManager, cubeNode);
				walls[j][i] = false;
			}
			else {
				cube = new EmptyCube(pos, sceneManager, cubeNode);
				walls[j][i] = false;
			}
			
			cubeNode->setScale((GAME_UNIT/cubeNode->getScale())*CUBE_SIZE);
			cubeNode->showBoundingBox(true);
			mSceneNode->addChild(cubeNode);

			
		}
	}
}

Labirynth::~Labirynth(){
}

bool 
Labirynth::canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir) {
	pos -= initPos;

	int x = pos.x += (GAME_UNIT / 2);
	int y = pos.z += (GAME_UNIT / 2);

	if (lookDir.x < 0) x -= GAME_UNIT / 2;
	else if (lookDir.x > 0) x += GAME_UNIT / 2;
	else if (lookDir.z < 0) y -= GAME_UNIT / 2;
	else if (lookDir.z > 0) y += GAME_UNIT / 2;
	
	x /= GAME_UNIT; 
	y /= GAME_UNIT;

	x = std::trunc(x);
	y = std::trunc(y);

	return !walls[x][y];
} 
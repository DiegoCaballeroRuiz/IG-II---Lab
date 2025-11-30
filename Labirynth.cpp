#include "Labirynth.h"
#include <fstream>
#include <iostream>
#include <cmath>

#include "WallCube.h"
#include "EmptyCube.h"
#include "Globals.h"
#include "Hero.h"
#include "OgreLight.h"
#include "Plane.h"
#include "Enemy.h"
#include "IG2App.h"
#include "SmokeContainer.h"

Labirynth::Labirynth(std::string filePath, Ogre::SceneManager* sceneManager, Ogre::SceneNode* sceneNode, Vector3 topLeftCorner, BombPool* bPool)
	: mSM(sceneManager)
{
	std::ifstream input("stage1.txt");

	mSceneNode = sceneNode;

	input >> numFilas >> numColumnas;
	walls = std::vector<std::vector<bool>>(numFilas);

	auto pNode = mSM->createSceneNode();
	p = new PlaneObject(Vector3(numFilas * GAME_UNIT / 2, -GAME_UNIT / 2, numColumnas * GAME_UNIT / 2), mSM, pNode, numFilas * GAME_UNIT - GAME_UNIT/2, numColumnas * GAME_UNIT - GAME_UNIT/2);
	mSceneNode->addChild(pNode);

	smokers.assign(numFilas, std::vector<SmokeContainer*>(numColumnas, nullptr));

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

			switch (c) {
			case 'x': {
					cube = new WallCube(pos, sceneManager, cubeNode);
					walls[j][i] = true; 
					break;
			}
			case 'h': {
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

					IG2App::getSingleton().addInputListener(hero);


					cube = new EmptyCube(pos, sceneManager, cubeNode);
					walls[j][i] = false;
					smokers[j][i] = new SmokeContainer(pos, mSceneNode->createChildSceneNode(), mSM, i * numFilas + j);
					IG2App::getSingleton().addInputListener(smokers[j][i]);

					hero->registerBombPool(bPool);

					break;
			}
			case 'e': {
				auto eNode = mSM->createSceneNode();
				eNode->setScale((GAME_UNIT / eNode->getScale()) * ENEMY_SIZE);
				Enemy* e = new Enemy(Vector3(0.0), Vector3(0.0), mSM, eNode, this, 5);
				e->setPosition(pos);
				mSceneNode->addChild(eNode);

				eNode->showBoundingBox(true);
				enemies.push_back(e);

				cube = new EmptyCube(pos, sceneManager, cubeNode);
				walls[j][i] = false;
				smokers[j][i] = new SmokeContainer(pos, mSceneNode->createChildSceneNode(), mSM, i * numFilas + j);
				IG2App::getSingleton().addInputListener(smokers[j][i]);

				break;
			}
			default: {
					cube = new EmptyCube(pos, sceneManager, cubeNode);
					walls[j][i] = false;

					smokers[j][i] = new SmokeContainer(pos, mSceneNode->createChildSceneNode(), mSM, i * numFilas + j);
					IG2App::getSingleton().addInputListener(smokers[j][i]);
			}
			}

			for (auto enemy : enemies) {
				IG2App::getSingleton().addInputListener(enemy);
			}
			
			cubeNode->setScale((GAME_UNIT/cubeNode->getScale())*CUBE_SIZE);
			cubeNode->showBoundingBox(true);
			mSceneNode->addChild(cubeNode);
		}
	}
}

Labirynth::~Labirynth(){
	for(int i = 0; i < numFilas; ++i)
		for (int j = 0; j < numColumnas; j++) {
			std::string name = "cube" + std::to_string(i) + ':' + std::to_string(j);
			auto cube = (SceneNode*)mSceneNode->getChild(name);
			delete cube->getAttachedObject(0);
		}

	delete p;

	delete hero;
	for (Enemy* enemy : enemies)
		delete enemy;
	enemies.clear();
}

bool 
Labirynth::canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir) {
	pos -= initPos;
	double u = GAME_UNIT * 0.5;
	double v =  GAME_UNIT*0.48;
	double x = pos.x += u;
	double y = pos.z += u;
	
	if (curDir != lookDir) {
		if (std::abs(lookDir.x) > 0) y += -curDir.z * v;
		else if (std::abs(lookDir.z) > 0) x += -curDir.x * v;
	}

	if (lookDir.x < 0) x -= u;
	else if (lookDir.x > 0) x += u;
	else if (lookDir.z < 0) y -= u;
	else if (lookDir.z > 0) y += u;
	
	x /= GAME_UNIT; 
	y /= GAME_UNIT;

	x = std::trunc(x);
	y = std::trunc(y);

	return !walls[x][y];
} 

bool 
Labirynth::setExplosion(Vector3 initialPos, Vector3 previousPos, int range) {
	if (range == 0 || !tileExploded(initialPos)) 
		return false;

	if (initialPos == previousPos) {
		setExplosion(initialPos + Vector3(GAME_UNIT, 0, 0), initialPos, range);
		setExplosion(initialPos + Vector3(-GAME_UNIT, 0, 0), initialPos, range);
		setExplosion(initialPos + Vector3(0, 0, GAME_UNIT), initialPos, range);
		setExplosion(initialPos + Vector3(0, 0, -GAME_UNIT), initialPos, range);
	}
	else {
		Vector3 dir = initialPos - previousPos;
		setExplosion(initialPos + dir, initialPos, range - 1);
	}

	return true;
}

bool 
Labirynth::tileExploded(Vector3 pos) {
	pos -= initPos;
	double u = GAME_UNIT * 0.1;
	double v = GAME_UNIT * 0.1;
	double x = pos.x += u;
	double y = pos.z += u;

	x /= GAME_UNIT;
	y /= GAME_UNIT;

	x = std::trunc(x);
	y = std::trunc(y);

	if (!walls[x][y])  {
		smokers[x][y]->startSmoking();
		checkBombCollision(pos);
		return true;
	}
	return false;
}

bool 
Labirynth::checkPlayerCollision() {
	auto heroHurtBox = hero->getAABB();
	for (Enemy* enemy : enemies) {
		auto enHitBox = enemy->getAABB();
		if (enHitBox.intersects(heroHurtBox)) return true;
	}
	return false;
}

void 
Labirynth::checkBombCollision(Vector3 pos) {
	Ogre::AxisAlignedBox exoplosionRect(pos - Vector3(GAME_UNIT / 2), pos + Vector3(GAME_UNIT / 2));

	if (exoplosionRect.intersects(hero->getAABB())) hero->getHit();

	for (auto it = enemies.begin(); it != enemies.end();) {
		if (exoplosionRect.intersects((*it)->getAABB())) {
			auto aux = *it;
			IG2App::getSingleton().removeInputListener(*it);
			it = enemies.erase(it);
			delete aux;
		}
		else ++it;
	}

	if (enemies.empty()) IG2App::getSingleton().closeApp();
}
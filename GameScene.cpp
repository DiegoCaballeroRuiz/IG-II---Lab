#include "GameScene.h"


#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

#include "IG2App.h"
#include "Labirynth.h"
#include "Hero.h"
#include "Enemy.h"
#include "InfoOverlay.h"

GameScene::GameScene(std::string map) 
	: SceneInterface() 
{ 
	root = IG2App::getSingleton().getSceneManager()->createSceneNode("GameSceneRoot");
	lab = new Labirynth(map, IG2App::getSingleton().getSceneManager(), root, Vector3(.0), sinbad, enemies);

	IG2App::getSingleton().addInputListener(sinbad);

	for (auto enemy : enemies) {
		IG2App::getSingleton().addInputListener(enemy);
	}
}

GameScene::~GameScene() {
	delete sinbad;
	delete lab;
	
	for (Enemy* enemy : enemies)
		delete enemy;
	enemies.clear();

	closeScene();
	delete root;
}

void 
GameScene::setupScene() {
	io = new InfoOverlay(3, 0, 210, 100, IG2App::getSingleton().getTrayManager());
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->addChild(root);
}

void 
GameScene::closeScene() {
	delete io;
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->removeChild("GameSceneRoot");
}

bool
GameScene::checkCollisions() {
	auto heroHurtBox = sinbad->getAABB();
	for (Enemy* enemy : enemies) {
		auto enHitBox = enemy->getAABB();
		if (enHitBox.intersects(heroHurtBox)) return true;
	}
	return false;
}

void 
GameScene::changeInfoOverlay(int lifes, int points) {
	io->setLives(lifes);
	io->setPoints(points);
}

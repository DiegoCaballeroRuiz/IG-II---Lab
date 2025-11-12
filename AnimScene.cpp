#include "AnimScene.h"

#include "IG2App.h"

#include "Ogre.h"

AnimScene::AnimScene() 
	: SceneInterface() 
{
	root = IG2App::getSingleton().getSceneManager()->createSceneNode("GameSceneRoot");
}

AnimScene::~AnimScene() {
	
}

void 
AnimScene::setupScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->addChild(root);

}

void 
AnimScene::closeScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->addChild(root);
}

bool 
AnimScene::checkCollisions() {
	return false;
}

void 
AnimScene::changeInfoOverlay(int lifes, int points) {

}
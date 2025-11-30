#pragma once
#include "SceneInterface.h"
#include "BombPool.h"
#include <string>
#include <vector>

class Labirynth;
class InfoOverlay;
class PlaneObject;

namespace Ogre {
	class SceneNode;
}

class Bomb;
class GameScene : public SceneInterface
{
private:
	Labirynth* lab;
	InfoOverlay* io;

	Ogre::SceneNode* root;
	BombPool bPool;
	PlaneObject* skybox;

	const int MAX_BOMBS = 3;
public:
	GameScene(std::string map);
	~GameScene();

	void setupScene() override;
	void closeScene() override;
	void changeInfoOverlay(int lifes, int points) override;
};


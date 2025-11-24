#pragma once
#include "SceneInterface.h"
#include "BombPool.h"
#include <string>
#include <vector>

class Hero;
class Labirynth;
class InfoOverlay;
class Enemy;

namespace Ogre {
	class SceneNode;
}

class Bomb;
class GameScene : public SceneInterface
{
private:
	Hero* sinbad;
	Labirynth* lab;
	InfoOverlay* io;
	std::vector<Enemy*> enemies;

	Ogre::SceneNode* root;
	BombPool pool;
public:
	GameScene(std::string map);
	~GameScene();

	void setupScene() override;
	void closeScene() override;
	void changeInfoOverlay(int lifes, int points) override;
	bool checkCollisions() override;
};


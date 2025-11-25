#pragma once

#include <vector>
#include <Ogre.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>
#include "SmokePool.h"


class Bomb;
class Labirynth;

namespace Ogre {
	class SceneNode;
};

class BombPool : public OgreBites::InputListener {
private:
	int firstFree;
	std::vector<Bomb*> bombs;
	Ogre::SceneNode* rootNode;

	Labirynth* lab;

	void initBomb(int iterator);
	void initBombs();

	void explodeBomb(int index);
public:
	BombPool();
	~BombPool();

	void init(int N, Ogre::SceneNode* rootNode, Labirynth* pool);
	void frameRendered(const Ogre::FrameEvent& evt) override;

	bool activateFreeBomb(Ogre::Vector3 pos);
};


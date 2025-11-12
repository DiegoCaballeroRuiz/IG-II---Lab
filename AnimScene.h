#pragma once
#include "SceneInterface.h"

namespace Ogre {
	class SceneNode;
}

class AnimScene : public SceneInterface
{
private:
	Ogre::SceneNode* root;
public:
	AnimScene();
	~AnimScene();

	void setupScene() override;
	void closeScene() override;
	bool checkCollisions() override;
	void changeInfoOverlay(int lifes, int points) override;
};


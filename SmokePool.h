#pragma once

#include <vector>
#include <Ogre.h>
#include <OgreInput.h>
#include <OgreFrameListener.h>

namespace Ogre {
	class SceneNode;
}

class SmokeContainer;

class SmokePool : public OgreBites::InputListener
{
private:
	int firstFree;
	std::vector<SmokeContainer*> smokers;
	Ogre::SceneNode* rootNode;

	void initSmoke(int iterator);
	void initSmokes();

	void deleteSmoke(int index);
public:
	SmokePool();
	~SmokePool();

	void init(int N, Ogre::SceneNode* rootNode);
	void frameRendered(const Ogre::FrameEvent& evt) override;

	bool activateFreeSmoker(Ogre::Vector3 pos);
};


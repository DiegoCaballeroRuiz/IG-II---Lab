#pragma once

#include "IG2Object.h"

class AnimatableEntity : public IG2Object
{
	NodeAnimationTrack* animTrack;
public:
	AnimatableEntity(Vector3 initPos, Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, std::string mesh, NodeAnimationTrack* animTrack);
	~AnimatableEntity();

	void addKeyFrame(Vector3 targetPos, float scale, Quaternion rotation, double startingTime);

	void frameRendered(const Ogre::FrameEvent& evt) override;

	void setTime(double time);

	NodeAnimationTrack* setAnimTrack(NodeAnimationTrack* newAnimTrack);
};


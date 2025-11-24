#pragma once
#include <string>
#include "IG2Object.h"

class AnimatableEntity : public IG2Object
{
	NodeAnimationTrack* animTrack;
	AnimationState* animationState;
	double speed;
public:
	AnimatableEntity(Vector3 initPos, Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, std::string mesh, NodeAnimationTrack* animTrack, double speed = 1.0);
	~AnimatableEntity();

	void addKeyFrame(Vector3 targetPos, float scale, Quaternion rotation, double startingTime);

	virtual void frameRendered(const Ogre::FrameEvent& evt) override;

	void setTime(double time);

	NodeAnimationTrack* setAnimTrack(NodeAnimationTrack* newAnimTrack);

	inline void attachAnimState(AnimationState* animState) { animationState = animState; }

	void setEnabledAnimState(std::string name, bool enabled);

	void attachToBone(const std::string& boneName, Ogre::Entity* ent);
	void detachAllBones();
};


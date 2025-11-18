#include "AnimatableEntity.h"

#include "OgreKeyFrame.h"

AnimatableEntity::AnimatableEntity(Vector3 initPos, Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, std::string mesh, NodeAnimationTrack* animTrack) 
	: IG2Object(initPos, node, sceneManager, mesh), animTrack(animTrack)
{
}
AnimatableEntity::~AnimatableEntity() {
	delete animTrack;
}

void 
AnimatableEntity::addKeyFrame(Vector3 targetPos, float scale, Quaternion rotation, double startingTime) {
	TransformKeyFrame* keyFrame;
	keyFrame = animTrack->createNodeKeyFrame(startingTime);
	keyFrame->setTranslate(targetPos);
	keyFrame->setRotation(rotation);
	keyFrame->setScale(Vector3(1.0) * scale);
}

NodeAnimationTrack* 
AnimatableEntity::setAnimTrack(NodeAnimationTrack* newAnimTrack) {
	NodeAnimationTrack* old = animTrack;
	animTrack = newAnimTrack;
	return old;
}

void 
AnimatableEntity::frameRendered(const Ogre::FrameEvent& evt) {
	auto animations = entity->getAllAnimationStates()->getEnabledAnimationStates();

	for (auto anim : animations) 
		anim->addTime(evt.timeSinceLastEvent);
}

void 
AnimatableEntity::setTime(double time) {
	animTrack->apply(Ogre::TimeIndex(time));
}

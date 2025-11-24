#include "AnimatableEntity.h"

#include "OgreKeyFrame.h"

AnimatableEntity::AnimatableEntity(Vector3 initPos, Ogre::SceneManager* sceneManager, Ogre::SceneNode* node, std::string mesh, NodeAnimationTrack* animTrack, double speed) 
	: IG2Object(initPos, node, sceneManager, mesh), animTrack(animTrack), speed(speed)
{
}

AnimatableEntity::~AnimatableEntity() {
	delete animTrack;
	delete animationState;
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

	mNode->setPosition(mNode->getPosition() + Vector3(.0, 1.0, .0));
	animationState->addTime(evt.timeSinceLastEvent * speed);

	auto animStates = entity->getAllAnimationStates();
	if (animStates == 0) return;

	auto animations = animStates->getEnabledAnimationStates();

	for (auto anim : animations) 
		anim->addTime(evt.timeSinceLastEvent);

}

void 
AnimatableEntity::setTime(double time) {
	animTrack->apply(Ogre::TimeIndex(time));
}

void 
AnimatableEntity::setEnabledAnimState(std::string name, bool enabled) {
	entity->getAnimationState(name)->setEnabled(enabled);
}

void 
AnimatableEntity::attachToBone(const std::string& boneName, Ogre::Entity* ent) {
	entity->attachObjectToBone(boneName, ent);
}

void 
AnimatableEntity::detachAllBones() {
	entity->detachAllObjectsFromBone();
}


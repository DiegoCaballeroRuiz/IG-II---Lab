#include "AnimationScene.h"

#include "IG2App.h"
#include "Plane.h"
#include "Globals.h"
#include "AnimatableEntity.h"
#include "OgreTimer.h"

AnimationScene::AnimationScene() 
	: SceneInterface()
{
	Ogre::SceneManager* manager = IG2App::getSingleton().getSceneManager();
	root = manager->createSceneNode("AnimationIntro");

	setSinbadAnims();
	setOgreheadAnims();
	
	floor = new PlaneObject(Vector3(.0), manager, root->createChildSceneNode(), 35 * GAME_UNIT, 25 * GAME_UNIT, "Animfloor");
	timer = new Timer();
}

AnimationScene::~AnimationScene() {
	delete floor;
	delete sinbad;
	delete ogreHead;
	delete floor;
	delete timer;
}


void 
AnimationScene::setupScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->addChild(root);
	IG2App::getSingleton().addInputListener(this);
	timer->reset();
}

void 
AnimationScene::closeScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->removeChild("AnimationIntro");
}

bool 
AnimationScene::keyPressed(const OgreBites::KeyboardEvent& evt) {
	return false;
}

void 
AnimationScene::setSinbadAnims() {

	Animation* animation = IG2App::getSingleton().getSceneManager()->createAnimation("Intro", 21.0);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	Ogre::NodeAnimationTrack* sinbadAnimTrack = animation->createNodeTrack(0);

	Ogre::SceneNode* node = root->createChildSceneNode();
	sinbadAnimTrack->setAssociatedNode(node);
	node->setScale((GAME_UNIT / node->getScale()) * SINBAD_SIZE);

	sinbad = new AnimatableEntity(Vector3(.0), IG2App::getSingleton().getSceneManager(), node, "Sinbad.mesh", sinbadAnimTrack);

	Vector3 centerPos = Vector3(.0), rightPos = Vector3(2.5, .0, .0), leftPos = Vector3(-2.5, .0, .0);
	//9 keyframes -> 21 seconds
	sinbad->addKeyFrame(centerPos, 1.0, Quaternion::IDENTITY, 4.0); //Start
	//sinbad->addKeyFrame(centerPos, 1.0, Quaternion(Radian(Degree(90.0)), Vector3(.0, 1.0, .0)), 4.0); //Rotate left
	sinbad->addKeyFrame(rightPos, 1.0, Quaternion::IDENTITY, 8.25); // Run away
	//sinbad->addKeyFrame(rightPos, 1.0, Quaternion(Radian(Degree(-180.0)), Vector3(.0, 1.0, .0)), 8.25); //Rotate right
	sinbad->addKeyFrame(leftPos, 1.0, Quaternion::IDENTITY, 16.5); //Run after
	//sinbad->addKeyFrame(leftPos, 1.0, Quaternion(Radian(Degree(180.0)), Vector3(.0, 1.0, .0)), 16.5); //Rotate left
	sinbad->addKeyFrame(centerPos, 1.0, Quaternion::IDENTITY, 20.75); // Run away
	//sinbad->addKeyFrame(centerPos, 1.0, Quaternion(Radian(Degree(-90.0)), Vector3(.0, 1.0, .0)), 20.75); //Rotate right
	sinbad->addKeyFrame(centerPos, 1.0, Quaternion::IDENTITY, 21.0); //End
}

void 
AnimationScene::setOgreheadAnims() {
	Ogre::NodeAnimationTrack* ogreHeadAnimTrack;
}

void 
AnimationScene::frameRendered(const Ogre::FrameEvent& evt) {
	if (timer->getMilliseconds() >= 21000) timer->reset();

	sinbad->setTime(timer->getMilliseconds() / 1000);
}

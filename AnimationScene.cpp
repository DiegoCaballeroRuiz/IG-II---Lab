#include "AnimationScene.h"

#include "IG2App.h"
#include "Plane.h"
#include "Globals.h"
#include "AnimatableEntity.h"
#include "OgreSceneNode.h"
#include "OgreTimer.h"
#include "SceneManager.h"
#include "Bomb.h"
#include "SphereObject.h"

AnimationScene::AnimationScene() 
	: SceneInterface()
{
	Ogre::SceneManager* manager = IG2App::getSingleton().getSceneManager();
	root = manager->createSceneNode("AnimationIntro");

	setSinbadAnims();
	setOgreheadAnims();
	
	floor = new PlaneObject(Vector3(.0), manager, root->createChildSceneNode(), 35 * GAME_UNIT, 25 * GAME_UNIT, "Animfloor", "Water");
	timer = new Timer();

	leftSword = manager->createEntity("Sword.mesh");
	rightSword = manager->createEntity("Sword.mesh");

	planet = new SphereObject(Vector3(.0, 3 * GAME_UNIT, -4 * GAME_UNIT), root->createChildSceneNode(), manager, 0.1, "emptySphere");
}

AnimationScene::~AnimationScene() {
	delete floor;
	delete sinbad;
	delete ogreHead;
	delete floor;
	delete timer;
	delete planet;
}


void 
AnimationScene::setupScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->addChild(root);
	IG2App::getSingleton().addInputListener(this);
	IG2App::getSingleton().addInputListener(sinbad);
	IG2App::getSingleton().addInputListener(ogreHead);

	SceneNode* camNode = IG2App::getSingleton().getCameraNode();
	camNode->setPosition(Vector3(.0, 5 * GAME_UNIT, 10 * GAME_UNIT));
	camNode->lookAt(Vector3(.0), Ogre::Node::TS_WORLD);
	
	timer->reset();
}

void 
AnimationScene::closeScene() {
	IG2App::getSingleton().getSceneManager()->getRootSceneNode()->removeChild("AnimationIntro");

	/*IG2App::getSingleton().removeInputListener(this);
	IG2App::getSingleton().removeInputListener(sinbad);
	IG2App::getSingleton().removeInputListener(ogreHead);*/
}

bool 
AnimationScene::keyPressed(const OgreBites::KeyboardEvent& evt) {
	switch (evt.keysym.sym)
	{
	case SDLK_s: {
		IG2App::getSingleton().getSceneSystem()->changeScene(SceneSystem::GAME_SCENE);
	}
	default:
		break;
	}
	return true;
}

void 
AnimationScene::setSinbadAnims() {

	Animation* animation = IG2App::getSingleton().getSceneManager()->createAnimation("IntroSinbad", 21.0);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::NodeAnimationTrack* sinbadAnimTrack = animation->createNodeTrack(0);

	Ogre::SceneNode* node = root->createChildSceneNode();
	sinbadAnimTrack->setAssociatedNode(node);
	node->setScale((GAME_UNIT / node->getScale()) * SINBAD_SIZE);

	sinbad = new AnimatableEntity(Vector3(.0), IG2App::getSingleton().getSceneManager(), node, "Sinbad.mesh", sinbadAnimTrack, 1.0);

	Vector3 centerPos = Vector3(.0, GAME_UNIT, .0), rightPos = Vector3(5 * GAME_UNIT, GAME_UNIT, .0), leftPos = Vector3(-5 * GAME_UNIT, GAME_UNIT, .0);
	Quaternion rightRot = Quaternion(Radian(Degree(90.0)), Vector3(.0, 1.0, .0)), leftRot = Quaternion(Radian(Degree(-90.0)), Vector3(.0, 1.0, .0));

	//8 keyframes -> 21 seconds
	sinbad->addKeyFrame(centerPos, 1.0, Quaternion::IDENTITY, 4.0); //Start
	sinbad->addKeyFrame(centerPos, 1.0, rightRot, 4.25); //Rotate left
	sinbad->addKeyFrame(rightPos, 1.0, rightRot, 8.25); // Run away
	sinbad->addKeyFrame(rightPos, 1.0, leftRot, 8.5); //Rotate right
	sinbad->addKeyFrame(leftPos, 1.0, leftRot, 16.5); //Run after
	sinbad->addKeyFrame(leftPos, 1.0, rightRot, 16.75); //Rotate left
	sinbad->addKeyFrame(centerPos, 1.0, rightRot, 20.75); // Run away
	sinbad->addKeyFrame(centerPos, 1.0, Quaternion::IDENTITY, 21.0); //Rotate right

	AnimationState* animState = IG2App::getSingleton().getSceneManager()->createAnimationState("IntroSinbad");
	animState->setEnabled(true);
	animState->setLoop(true);

	sinbad->attachAnimState(animState);
}

void
AnimationScene::setOgreheadAnims() {
	Animation* animation = IG2App::getSingleton().getSceneManager()->createAnimation("IntroOgreHead", 21.0);
	animation->setInterpolationMode(Ogre::Animation::IM_LINEAR);
	Ogre::NodeAnimationTrack* ogreHeadAnimTrack = animation->createNodeTrack(0);

	Ogre::SceneNode* node = root->createChildSceneNode();
	ogreHeadAnimTrack->setAssociatedNode(node);
	node->setScale((GAME_UNIT / node->getScale()) * ENEMY_SIZE);

	ogreHead = new AnimatableEntity(Vector3(.0), IG2App::getSingleton().getSceneManager(), node, "ogrehead.mesh", ogreHeadAnimTrack, 1.0);

	Vector3 center = Vector3(.0, GAME_UNIT, .0), right = Vector3(3.5 * GAME_UNIT, GAME_UNIT, .0), left = Vector3(-8.0 * GAME_UNIT, GAME_UNIT, .0);
	Quaternion rightRot = Quaternion(Radian(Degree(90.0)), Vector3(.0, 1.0, .0)), leftRot = Quaternion(Radian(Degree(-90.0)), Vector3(.0, 1.0, .0));

	ogreHead->addKeyFrame(left, 8 * ENEMY_SIZE * GAME_UNIT, rightRot, .0); // Start
	ogreHead->addKeyFrame(right, 8 * ENEMY_SIZE * GAME_UNIT, rightRot, 8.25); // Run after
	ogreHead->addKeyFrame(right, 8 * ENEMY_SIZE * GAME_UNIT, leftRot, 8.5); // Rotate left
	ogreHead->addKeyFrame(left, 8 * ENEMY_SIZE * GAME_UNIT, leftRot, 16.5); // Run away
	ogreHead->addKeyFrame(left, 8 * ENEMY_SIZE * GAME_UNIT, rightRot, 16.75); // Rotate right
	ogreHead->addKeyFrame(center, ENEMY_SIZE * GAME_UNIT * 0.001, rightRot, 20.75); // Run after and dissapear

	AnimationState* animState = IG2App::getSingleton().getSceneManager()->createAnimationState("IntroOgreHead");
	animState->setEnabled(true);
	animState->setLoop(true);

	ogreHead->attachAnimState(animState);
}

void 
AnimationScene::frameRendered(const Ogre::FrameEvent& evt) {
	if (timer->getMilliseconds() >= LOOP_DURATION) timer->reset();
	else if (timer->getMilliseconds() <= 4250) {
		sinbad->setEnabledAnimState(DANCE, true);
		sinbad->setEnabledAnimState(RUN_BASE, false);
		sinbad->setEnabledAnimState(RUN_TOP, false);
	}
	else {
		sinbad->setEnabledAnimState(DANCE, false);
		sinbad->setEnabledAnimState(RUN_BASE, true);
		sinbad->setEnabledAnimState(RUN_TOP, true);
	}

	if ( !swordsAttached && timer->getMilliseconds() >= 9000 && timer->getMilliseconds() <= 16500) {
		sinbad->attachToBone(HAND_L, leftSword);
		sinbad->attachToBone(HAND_R, rightSword);
		swordsAttached = true;
	}
	else if(swordsAttached && timer->getMilliseconds() >= 17500) {
		sinbad->detachAllBones();
		swordsAttached = false;
	}
}

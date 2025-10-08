#include "Hero.h"
#include "Labirynth.h"
#include "Globals.h"

Hero::Hero(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu) :
	IG2Object(initPos, sceneNode, sceneMng, "Sinbad.mesh"), labuburinth(labubu), currentDirection(direction),
	targetDirection(Vector3()) {}

bool Hero::keyPressed(const OgreBites::KeyboardEvent& evt){
	switch (evt.keysym.sym)
	{
	case SDLK_UP:
		targetDirection = Vector3(0, 0, -1);
		break;
	case SDLK_DOWN:
		targetDirection = Vector3(0, 0, 1);
		break;
	case SDLK_LEFT:
		targetDirection = Vector3(-1, 0, 0);
		break;
	case SDLK_RIGHT:
		targetDirection = Vector3(1, 0, 0);
		break;
	default:
		return false;
	}
	return true;
}

void Hero::frameRendered(const Ogre::FrameEvent& evt) {
	tryToMove(evt.timeSinceLastFrame);
}

bool 
Hero::tryToMove(double delta) {
	bool checked = false;
	if (currentDirection != targetDirection 
		&& labuburinth->freeSquare(getPosition() + targetDirection * SPEED * GAME_UNIT * delta)) {
		currentDirection = targetDirection;

		Quaternion q = getOrientation().getRotationTo(currentDirection);
		mNode->rotate(q);

		checked = true;
	}
	if (!(checked || labuburinth->freeSquare(getPosition() + currentDirection * SPEED * GAME_UNIT * delta))) return false;

	setPosition(getPosition() + currentDirection * SPEED * GAME_UNIT * delta);
	return true;
}

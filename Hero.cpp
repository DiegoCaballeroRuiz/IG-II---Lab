#include "Hero.h"
#include "Labirynth.h"
#include "Globals.h"
#include "IG2App.h"
#include "InfoOverlay.h"

Hero::Hero(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu) :
	Character(HERO_SPEED, labubu, sceneMng, sceneNode, "Sinbad.mesh", initPos), currentDirection(direction),
	targetDirection(Vector3(0.0, 0.0, 0.0)), inmuneTime(0.0), lives(3) {}

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
	bool collided = IG2App::getSingleton().checkCollisions();
	tryToMove(evt.timeSinceLastFrame);
	collided = collided || IG2App::getSingleton().checkCollisions();
	
	if(inmuneTime >= 0) inmuneTime -= evt.timeSinceLastFrame;//por si alguien tuviese abierta la aplicacion 2 anyos
	if (collided && inmuneTime <= 0) {
		lives--;
		inmuneTime = HERO_INMUNE_TIME;
		if (lives <= 0) 
			IG2App::getSingleton().endGame();
		
		IG2App::getSingleton().changeInfo(lives, 0);
	}
}

bool 
Hero::tryToMove(double delta) {
	bool checked = false;
	if (currentDirection != targetDirection 
		&& labuburinth->canMove(getPosition() + targetDirection * speed * GAME_UNIT * delta, targetDirection, currentDirection)) {
		currentDirection = targetDirection;

		Quaternion q = getOrientation().getRotationTo(currentDirection);
		mNode->rotate(q);

		checked = true;
	}
	if (!(checked || labuburinth->canMove(getPosition() + currentDirection * speed * GAME_UNIT * delta, currentDirection, currentDirection))) return false;

	setPosition(getPosition() + currentDirection * speed * GAME_UNIT * delta);
	return true;
}

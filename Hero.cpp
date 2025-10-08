#include "Hero.h"
#include "Labirynth.h"
#include "Globals.h"

Hero::Hero(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu) :
	IG2Object(initPos, sceneNode, sceneMng, "Sinbad.mesh"), labuburinth(labubu), currentDirection(direction),
	targetDirection(Vector3()) {}

void  Hero::keypressed(OgreBites::Keycode key){
	switch (key)
	{
	case SDLK_UP:
		targetDirection = Vector3(0, 0, 1);
		break;
	case SDLK_DOWN:
		targetDirection = Vector3(0, 0, -1);
		break;
	case SDLK_LEFT:
		targetDirection = Vector3(-1, 0, 0);
		break;
	case SDLK_RIGHT:
		targetDirection = Vector3(1, 0, 0);
		break;
	default:
		break;
	}
}
bool 
Hero::tryToMove() {
	bool checked = false;
	if (getOrientation() != targetDirection 
		&& labuburinth->freeSquare(getPosition() + targetDirection * SPEED * GAME_UNIT)) {
		currentDirection = targetDirection;

		Quaternion q = getOrientation().getRotationTo(currentDirection);
		mNode->rotate(q);

		checked = true;
	}
	if (!(checked || labuburinth->freeSquare(getPosition() + currentDirection * SPEED * GAME_UNIT))) return false;

	setPosition(getPosition() + currentDirection * SPEED * GAME_UNIT);
	return true;
}

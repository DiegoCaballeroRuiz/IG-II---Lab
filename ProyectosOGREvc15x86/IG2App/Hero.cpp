#include "Hero.h"

Hero::Hero(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu) :
	IG2Object(initPos, sceneNode, sceneMng), labuburinth(labubu), targetDirection(Vector3()) {}

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
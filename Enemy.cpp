#include "Enemy.h"
#include "Labirynth.h"
#include <random>

Enemy::Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu)
	: IG2Object(initPos, sceneNode, sceneMng, "ogrehead.mesh"), backDirection(-direction), labuburynth(labubu)
{
	possibleDirections = {
		Vector3(-1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 0, -1),
		Vector3(0, 0, 1),
	};
}

void 
Enemy::frameRendered(const Ogre::FrameEvent& evt) {
	std::vector<Vector3> validDirections;
	for (Vector3 direction : possibleDirections) {
		if (direction != backDirection && labuburynth->canMove(getPosition() + direction * SPEED * evt.timeSinceLastEvent, direction, -backDirection)) {
			validDirections.push_back(direction);
		}
	}

	if (validDirections.size() == 0) backDirection = -backDirection;
	else backDirection = -validDirections[rand() % validDirections.size()];

	setPosition(getPosition() - backDirection * SPEED * evt.timeSinceLastEvent);
}

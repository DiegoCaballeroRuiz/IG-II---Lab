#include "Enemy.h"
#include "Labirynth.h"
#include <random>
#include "Globals.h"
#include "Pivot.h"

Enemy::Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int childGroupSize)
	: Character(ENEMY_SPEED, labubu, sceneMng, sceneNode, "ogrehead.mesh", initPos), backDirection(-direction), cooldown(0)
{
	possibleDirections = {
		Vector3(-1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 0, -1),
		Vector3(0, 0, 1),
	};

	fish = new Pivot(initPos, mNode->createChildSceneNode(), mSM, "fish.mesh", 1.0, Vector3(0, 1, 0), childGroupSize);
	fish->setScale(Vector3(10.0));
	penguins = new Pivot(initPos, mNode->createChildSceneNode(), mSM, "penguin.mesh", 10.0, Vector3(1, 0, 0), childGroupSize);
}

Enemy::~Enemy() {
	delete fish;
	delete penguins;
}

void 
Enemy::frameRendered(const Ogre::FrameEvent& evt) {
	fish->update(evt.timeSinceLastFrame);
	penguins->update(evt.timeSinceLastFrame);

	tryToMove(evt.timeSinceLastEvent);
}

bool 
Enemy::tryToMove(double delta) {
	auto newPos = getPosition() - backDirection * speed * delta;
	if (labuburinth->canMove(newPos, -backDirection, -backDirection))
		setPosition(newPos);
	Quaternion q = getOrientation().getRotationTo(-backDirection);
	mNode->rotate(q);

	cooldown -= delta;

	if (cooldown > 0.0) return false;


	std::vector<Vector3> validDirections;
	for (Vector3 direction : possibleDirections) {
		if (direction != backDirection && labuburinth->canMove(getPosition() + direction * speed * delta, direction, -backDirection)) {
			validDirections.push_back(direction);
		}
	}

	if (validDirections.size() == 0) backDirection = -backDirection;
	else {
		backDirection = -validDirections[rand() % validDirections.size()];
		cooldown = ENEMY_ROTATE_COOLDOWN;
	}

	return true;
}

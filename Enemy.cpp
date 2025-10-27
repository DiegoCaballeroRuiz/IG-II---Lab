#include "Enemy.h"
#include "Labirynth.h"
#include <random>
#include "Globals.h"
#include "Pivot.h"

Enemy::Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int childGroupSize)
	: IG2Object(initPos, sceneNode, sceneMng, "ogrehead.mesh"), backDirection(-direction), labuburynth(labubu), cooldown(0)
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

	auto newPos = getPosition() - backDirection * SPEED * evt.timeSinceLastFrame;
	if (labuburynth->canMove(newPos, -backDirection, -backDirection))
		setPosition(newPos);
	Quaternion q = getOrientation().getRotationTo(-backDirection);
	mNode->rotate(q);

	cooldown -= evt.timeSinceLastFrame;

	if (cooldown > 0.0)return;
	

	std::vector<Vector3> validDirections;
	for (Vector3 direction : possibleDirections) {
		if (direction != backDirection && labuburynth->canMove(getPosition() + direction * SPEED * evt.timeSinceLastFrame, direction, -backDirection)) {
			validDirections.push_back(direction);
		}
	}

	if (validDirections.size() == 0) backDirection = -backDirection;
	else {
		backDirection = -validDirections[rand() % validDirections.size()];
		cooldown = ROTATE_COOLDOWN;
	}
}
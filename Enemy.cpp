#include "Enemy.h"
#include "Labirynth.h"
#include <random>
#include <math.h>
#include <cmath>
#include "Globals.h"

Enemy::Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int son)
	: IG2Object(initPos, sceneNode, sceneMng, "ogrehead.mesh"), backDirection(-direction), labuburynth(labubu), cooldown(0), childGroupSize(son)
{
	possibleDirections = {
		Vector3(-1, 0, 0),
		Vector3(1, 0, 0),
		Vector3(0, 0, -1),
		Vector3(0, 0, 1),
	};
	children.assign(2 * childGroupSize, nullptr);
	creatChildrenGroup("fish.mesh", 0, Vector3(0, 1, 0));
	creatChildrenGroup("penguin.mesh", childGroupSize, Vector3(0, 1, 0));
}

void 
Enemy::frameRendered(const Ogre::FrameEvent& evt) {

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

void 
Enemy::creatChildrenGroup(std::string meshName, int index, Vector3 rotAxis) {

	double rot = 2 * M_PI / childGroupSize;
	double r = 1000 * GAME_UNIT;
	for (int i = 0; i < childGroupSize; ++i) {
		auto childNode = mNode->createChildSceneNode();
		double sin = std::sin(rot * i) * r;
		double cos = std::cos(rot * i) * r;

		Vector3 diff;
		if (rotAxis == Vector3(1, 0, 0)) {
			diff = Vector3(0, cos, sin);
		}
		else if (rotAxis == Vector3(0, 1, 0)) {
			diff = Vector3(cos, 0, sin);
		}
		else {
			diff = Vector3(sin, cos, 0);
		}
		childNode->setPosition(childNode->getPosition() + diff);

		IG2Object* childEntity = new IG2Object(Vector3(), childNode, mSM, meshName);

		children[index+i] = childNode;
	}
}

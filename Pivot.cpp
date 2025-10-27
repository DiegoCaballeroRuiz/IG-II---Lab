#include "Pivot.h"
#include "Globals.h"
#include <cmath>
#include <math.h>


Pivot::Pivot(Vector3 initPos, SceneNode* sceneNode, SceneManager* sceneManager, std::string meshName, double radius, Vector3 axis, int nChildren)
	: IG2Object(initPos, sceneNode, sceneManager), children(nChildren, nullptr), axis(axis)
{
	double rot = 2 * M_PI / nChildren;

	for (int i = 0; i < nChildren; ++i) {
		auto childNode = mNode->createChildSceneNode();
		double sin = std::sin(rot * i) * radius * GAME_UNIT;
		double cos = std::cos(rot * i) * radius * GAME_UNIT;

		Vector3 diff;
		if (axis == Vector3(1, 0, 0)) {
			diff = Vector3(0, cos, sin);
		}
		else if (axis == Vector3(0, 1, 0)) {
			diff = Vector3(cos, 0, sin);
		}
		else {
			diff = Vector3(sin, cos, 0);
		}

		IG2Object* childEntity = new IG2Object(Vector3(0.0), childNode, mSM, meshName);
		childEntity->setPosition(diff);

		children.push_back(childEntity);
	}
};

Pivot::~Pivot() {
	for (auto child : children) {
		delete child;
	}
	children.clear();
}


void 
Pivot::update(double delta) {
	if (axis == Vector3(1, 0, 0)) {
		pitch(Ogre::Radian(0.2 * delta));
		for (auto child : children) {
			child->pitch(Ogre::Radian(-3.0 * delta));
		}
	}
	else if (axis == Vector3(0, 1, 0)) {
		yaw(Ogre::Radian(0.2 * delta));
		for (auto child : children) {
			child->yaw(Ogre::Radian(-3.0 * delta));
		}
	}
	else {
		roll(Ogre::Radian(0.2 * delta));
		for (auto child : children) {
			child->roll(Ogre::Radian(-3.0 * delta));
		}
	}
}

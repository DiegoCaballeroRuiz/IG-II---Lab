#pragma once
#include "IG2Object.h"

class Pivot : public IG2Object
{
	std::vector<IG2Object*> children;
	Vector3 axis;

public:
	Pivot(Vector3 initPos, SceneNode* sceneNode, SceneManager* sceneManager, std::string meshName, double radius, Vector3 axis, int nChildren);
	~Pivot();
	void update(double delta);
};


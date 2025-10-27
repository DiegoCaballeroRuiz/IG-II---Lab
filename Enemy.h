#pragma once
#include "IG2Object.h"
class Labirynth;
class Enemy : public IG2Object
{
private:
    Vector3 backDirection;
    std::vector<Vector3> possibleDirections;
    vector<SceneNode*> children;
    const double SPEED = 5.0;
    const double ROTATE_COOLDOWN = 1.0;
    double cooldown;
    int childGroupSize;
    Labirynth* labuburynth;

    void creatChildrenGroup(std::string meshName, int index, Vector3 rotAxis);

public:
    Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int childGroupSize);
    ~Enemy() {}
    void frameRendered(const Ogre::FrameEvent& evt) override;
};
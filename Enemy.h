#pragma once
#include "IG2Object.h"
class Labirynth;
class Pivot;
class Enemy : public IG2Object
{
private:
    Vector3 backDirection;
    std::vector<Vector3> possibleDirections;
    
    const double SPEED = 5.0;
    const double ROTATE_COOLDOWN = 1.0;
    double cooldown;
    Labirynth* labuburynth;

    Pivot* penguins; 
    Pivot* fish;

public:
    Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int childGroupSize);
    ~Enemy();
    void frameRendered(const Ogre::FrameEvent& evt) override;
};
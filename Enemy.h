#pragma once
#include "Character.h"

class Pivot;
class Enemy : public Character
{
private:
    Vector3 backDirection;
    std::vector<Vector3> possibleDirections;
    
   
    double cooldown;
    Pivot* penguins; 
    Pivot* fish;

public:
    Enemy(Vector3 initPos, Vector3 direction, SceneManager* sceneMng, SceneNode* sceneNode, Labirynth* labubu, int childGroupSize);
    ~Enemy();
    void frameRendered(const Ogre::FrameEvent& evt) override;

    bool tryToMove(double delta) override;
};
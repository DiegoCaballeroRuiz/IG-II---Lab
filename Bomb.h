#pragma once

#include "IG2Object.h"
#include "Ogre.h"
class Bomb : public IG2Object
{
protected:
	struct object {
		Ogre::Entity* ent;
		Ogre::SceneNode* node;
	};

	object fuse;
	double timeUntilExplosion;
	const double EXPLOSION_DURATION = 3.5;

	Ogre::Vector3 unitScale;
	Ogre::ParticleSystem* pSys;

	const double SCALE_VARIANCE = .25;
public:
	Bomb(Ogre::Vector3 initPos, Ogre::SceneNode* node, Ogre::SceneManager* sceneMng, int iterator = 0);
	~Bomb();

	void update(double dt);

	void activateBomb();
	inline bool isActive() { return timeUntilExplosion >= 0; }
};


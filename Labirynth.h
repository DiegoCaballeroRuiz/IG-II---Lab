#pragma once
#include "Ogre.h"
#include <string>
#include <vector>

class Hero;
namespace Ogre {
	class Light;
}

using namespace Ogre;
class Labirynth {
	int numFilas, numColumnas;
	Vector3 initPos;
	SceneManager* mSM;
	SceneNode* mSceneNode;
	Light* mLight;
	std::vector<std::vector<bool>> walls;
	//Material wallMateria, floorMaterial;

	
public:
	Labirynth(std::string filePath, SceneManager* sceneManager, Vector3 topLeftcorner, Hero*& hero);
	~Labirynth();

	bool canMove(Vector3 pos, Vector3 lookDir, Vector3 curDir);
};
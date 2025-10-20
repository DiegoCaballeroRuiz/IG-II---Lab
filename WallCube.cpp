#include "WallCube.h"

WallCube::WallCube(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode) :
	IG2Object(initPos, sceneNode, sceneMng, "cube.mesh") 
{
	//entity->setMaterialName("Wall/WallFloorAO");
}

#include "WallCube.h"

WallCube::WallCube(Vector3 initPos, String nodeName, SceneManager* sceneMng) : 
	IG2Object(initPos, sceneMng->createSceneNode(nodeName), sceneMng, "cube.mesh") {}

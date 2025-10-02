#include "EmptyCube.h"

EmptyCube::EmptyCube(Vector3 initPos, String nodeName, SceneManager* sceneMng) :
	IG2Object(initPos, sceneMng->createSceneNode(nodeName), sceneMng) {}

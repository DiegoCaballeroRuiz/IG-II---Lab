#include "Plane.h"

PlaneObject::PlaneObject(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode) 
	: IG2Object(initPos, sceneNode, sceneMng, Ogre::MeshManager::getSingleton().createPlane("Floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Vector3(1, 0, 0), Vector3()), 100, 100))
{

}

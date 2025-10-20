#include "Plane.h"

PlaneObject::PlaneObject(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode)
	: IG2Object(initPos, sceneNode, sceneMng)
{
	entity = sceneMng->createEntity("Floor", Ogre::MeshManager::getSingleton().createPlane("Floor", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z));
}
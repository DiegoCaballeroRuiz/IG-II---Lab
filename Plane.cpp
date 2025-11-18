#include "Plane.h"

PlaneObject::PlaneObject(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode, double width, double height, std::string name)
	: IG2Object(initPos, sceneNode, sceneMng)
{
	Ogre::MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), width, height, 1, 1, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	entity = sceneMng->createEntity(name);
	sceneNode->attachObject(entity);

	entity->setMaterialName("FloorChrome");
}
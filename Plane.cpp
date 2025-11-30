#include "Plane.h"

PlaneObject::PlaneObject(Vector3 initPos, SceneManager* sceneMng, SceneNode* sceneNode, double width, double height, std::string name, std::string materialName)
	: IG2Object(initPos, sceneNode, sceneMng)
{
	Ogre::MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), width, height, 10, 10, true, 10, 10.0, 10.0, Vector3::UNIT_Z);
	entity = sceneMng->createEntity(name);
	sceneNode->attachObject(entity);

	entity->setMaterialName(materialName);
}

void 
PlaneObject::frameRendered(const Ogre::FrameEvent& evt) {
	yaw(Ogre::Radian(Ogre::Degree(evt.timeSinceLastFrame)));
}

#include "SphereObject.h"

SphereObject::SphereObject(Vector3 pos, SceneNode* mNode, SceneManager* mSM, double scale, std::string materialName) 
	: IG2Object(pos, mNode, mSM, "uv_sphere.mesh")
{
	setScale(Vector3(scale));
	setMaterialName(materialName);
}
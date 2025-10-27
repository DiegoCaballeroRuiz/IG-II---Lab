#include "IG2App.h"
#include "Labirynth.h"
#include "Hero.h"
#include "Plane.h"
#include "InfoOverlay.h"
#include "Enemy.h"
#include "Globals.h"

#include <math.h>

using namespace std;
using namespace Ogre;

template<> IG2App* Ogre::Singleton<IG2App>::msSingleton = nullptr;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt) {

    // ESC key finished the rendering...
    if (evt.keysym.sym == SDLK_ESCAPE) {
        getRoot()->queueEndRendering();
    }

    return true;
}


void IG2App::shutdown() {

    mShaderGenerator->removeSceneManager(mSM);
    mSM->removeRenderQueueListener(mOverlaySystem);

    mRoot->destroySceneManager(mSM);

    delete mTrayMgr;  mTrayMgr = nullptr;
    delete mCamMgr; mCamMgr = nullptr;

    // do not forget to call the base 
    OgreBites::ApplicationContext::shutdown();
}

void IG2App::setup(void) {

    // do not forget to call the base first
    OgreBites::ApplicationContext::setup();

    // Create the scene manager
    mSM = mRoot->createSceneManager();

    // Register our scene with the RTSS
    mShaderGenerator->addSceneManager(mSM);
        
    mSM->addRenderQueueListener(mOverlaySystem);
    //mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);
    mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", getRenderWindow());
    mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
    addInputListener(mTrayMgr);

    

    // Adds the listener for this object
    addInputListener(this);
    setupScene();
}

void IG2App::setupScene(void) {
    
    //------------------------------------------------------------------------
    // Creating the camera
    Camera* cam = mSM->createCamera("Cam");
    cam->setNearClipDistance(1);
    cam->setFarClipDistance(10000);
    cam->setAutoAspectRatio(true);
    //cam->setPolygonMode(Ogre::PM_WIREFRAME);

    mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
    mCamNode->attachObject(cam);

    // Siempre mira al 0,0,0????????
    mCamNode->setPosition(0, 0, 1000);
    mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
    // and tell it to render into the main window
    Viewport* vp = getRenderWindow()->addViewport(cam);

    mCamMgr = new OgreBites::CameraMan(mCamNode);
    addInputListener(mCamMgr);
    mCamMgr->setStyle(OgreBites::CS_ORBIT);

    //------------------------------------------------------------------------
    // Creating the light

    //mSM->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
    
    Light* luz = mSM->createLight("Luz");
    luz->setType(Ogre::Light::LT_DIRECTIONAL);
    luz->setDiffuseColour(0.75, 0.75, 0.75);

    mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
    mLightNode->attachObject(luz);
    mLightNode->setDirection(Ogre::Vector3(-0.75, -1, -0.75));
 
    lab = new Labirynth("..\Stages\stage1.txt"s, mSM, Ogre::Vector3(), hero, enemies);
    addInputListener(hero);

    for (auto enemy : enemies) {
        addInputListener(enemy);
    }

    //auto floorNode = mSM->getRootSceneNode()->createChildSceneNode();    
    //floor = new PlaneObject(Vector3(), mSM, floorNode);
    //floorNode->showBoundingBox(true);

    io = new InfoOverlay(3, 0, 210, 100, mTrayMgr);

    
    
    //------------------------------------------------------------------------
    // Creating Sinbad

    /*Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
    mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
    mSinbadNode->attachObject(ent);*/

    //// Show bounding box
    //mSinbadNode->showBoundingBox(true);

    // Set position of Sinbad
    //mSinbadNode->setPosition(x, y, z);

    // Set scale of Sinbad
    //mSinbadNode->setScale(20, 20, 20);

    //mSinbadNode->yaw(Ogre::Degree(-45));
    //mSinbadNode->setVisible(false);    

}

bool 
IG2App::checkCollisions() const{
    auto heroHurtBox = hero->getAABB();
    for (Enemy* enemy : enemies) {
        auto enHitBox = enemy->getAABB();
        if (enHitBox.intersects(heroHurtBox)) return true;
    }
    return false;
}

InfoOverlay* 
IG2App::getLabel() {
    return io;
}

void 
IG2App::endGame() {
    for (auto enemy : enemies)
        delete enemy;

    delete hero;
    delete io;
    delete floor;
    delete lab;

    shutdown();
}

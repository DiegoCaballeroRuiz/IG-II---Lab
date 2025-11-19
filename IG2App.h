#ifndef __IG2App_H__
#define __IG2App_H__

#include <OgreApplicationContext.h>
#include <OgreSceneManager.h>
#include <OgreRTShaderSystem.h>       
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreInput.h>
#include <OgreMeshManager.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Ogre.h"
#include <OgreWindowEventUtilities.h>
#include <SDL_keycode.h>

class SceneSystem;
class IG2App: public OgreBites::ApplicationContext, OgreBites::InputListener, public Ogre::Singleton<IG2App> {

public:
    explicit IG2App() : OgreBites::ApplicationContext("IG2App"), Ogre::Singleton<IG2App>(), sceneSystem() {};
    virtual ~IG2App() {};

    bool checkCollisions();


    void endGame();
    inline Ogre::SceneManager* getSceneManager() { return mSM; }
    inline SceneSystem* getSceneSystem() { return sceneSystem; }
    inline OgreBites::TrayManager* getTrayManager() { return mTrayMgr; }

    void changeInfo(int lifes, int points);
    inline Ogre::SceneNode* getCameraNode() { return mCamNode; }
protected:
    virtual void shutdown();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void setupScene();


    Ogre::SceneNode* mSinbadNode = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    SceneSystem* sceneSystem;
};

#endif

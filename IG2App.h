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

class Hero;
class Labirynth;
class InfoOverlay;
class PlaneObject;
class Enemy;
class IG2App: public OgreBites::ApplicationContext, OgreBites::InputListener, public Ogre::Singleton<IG2App> {

public:
    explicit IG2App() : OgreBites::ApplicationContext("IG2App"), Ogre::Singleton<IG2App>() {};
    virtual ~IG2App() {};

    bool checkCollisions()const;

    InfoOverlay* getLabel();
protected:
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void setup();
    virtual void shutdown();
    virtual void setupScene();


    Ogre::SceneNode* mSinbadNode = nullptr;

    Ogre::SceneManager* mSM = nullptr;
    OgreBites::TrayManager* mTrayMgr = nullptr;

    Ogre::Light* light = nullptr;
    Ogre::SceneNode* mLightParent = nullptr;
    Ogre::SceneNode* mLightNode = nullptr;

    Ogre::SceneNode* mCamNode = nullptr;
    OgreBites::CameraMan* mCamMgr = nullptr;

    Hero* hero;
    Labirynth* lab;
    PlaneObject* floor;
    InfoOverlay* io;
    std::vector<Enemy*> enemies;
};

#endif

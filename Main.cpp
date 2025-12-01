#include "IG2App.h"

int main(int argc, char* argv[]){

    IG2App app;

    try{        
        app.initApp();
        app.getRoot()->startRendering();
    }
    catch (Ogre::Exception& e) {
        Ogre::LogManager::getSingleton().logMessage("An exception has occured: " + e.getFullDescription() + "\n");
    }
    catch (std::exception& e) {
        std::cerr << e.what();
    }
    catch (std::string s) {
        std::cerr << s;
    }
    app.closeApp();
    return 0;
}
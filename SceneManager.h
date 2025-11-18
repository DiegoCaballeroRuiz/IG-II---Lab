#pragma once

#include <vector>
class SceneInterface;
class SceneSystem
{
public:
	enum SceneType {
		ANIM_SCENE,
		GAME_SCENE,
		NUM_SCENES
	};

	SceneSystem();
	void changeScene(SceneType s);
	inline SceneInterface* getActiveScene() { return scenes[activeScene]; }
private:
	std::vector<SceneInterface*> scenes;
	SceneType activeScene = NUM_SCENES;
};


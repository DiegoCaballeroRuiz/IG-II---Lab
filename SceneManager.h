#pragma once

#include <vector>
class SceneInterface;
class SceneSystem
{
public:
	enum SceneType {
		GAME_SCENE,
		ANIM_SCENE,
		NUM_SCENES
	};

	SceneSystem();
	void changeScene(SceneType s);
	inline SceneInterface* getActiveScene() { return scenes[activeScene]; }
private:
	std::vector<SceneInterface*> scenes;
	SceneType activeScene;
};


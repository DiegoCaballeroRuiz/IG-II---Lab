#include "SceneManager.h"
#include "GameScene.h"
#include "AnimationScene.h"

SceneSystem::SceneSystem() {
	scenes = {
		new AnimationScene(),
		new GameScene("stage1.txt")
	};
}

void 
SceneSystem::changeScene(SceneType s) {
	if(activeScene != NUM_SCENES) scenes[activeScene]->closeScene();
	activeScene = s;
	scenes[activeScene]->setupScene();
}
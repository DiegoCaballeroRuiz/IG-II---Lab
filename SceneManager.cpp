#include "SceneManager.h"
#include "GameScene.h"

SceneSystem::SceneSystem() {
	scenes = {
		new GameScene("stage1.txt")
	};
}

void 
SceneSystem::changeScene(SceneType s) {
	scenes[activeScene]->closeScene();
	activeScene = s;
	scenes[activeScene]->setupScene();
}
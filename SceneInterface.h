#pragma once


class SceneInterface
{
public:
	SceneInterface() {}
	virtual ~SceneInterface() {}
	virtual void setupScene() = 0;
	virtual void closeScene() = 0;

	virtual bool checkCollisions() = 0;
	virtual void changeInfoOverlay(int lifes, int points) = 0;
};
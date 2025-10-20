#pragma once
#include <string>

namespace OgreBites {
	class TrayManager;
	class TextBox;
	class Label;
}

class InfoOverlay
{
private:
	int _lives, _points;
	OgreBites::TrayManager* _trayMgr;
	OgreBites::TextBox* _textBox;
	OgreBites::Label* _label;

	std::string parseTextBoxInfo();
public:
	InfoOverlay(int lives, int points, double width, double heith, OgreBites::TrayManager* trayMgr);

	void setLives(int lives);
	void setPoints(int points);

	int getLives()const;
	int getPoints()const;
};


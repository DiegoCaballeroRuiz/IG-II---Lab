#include "InfoOverlay.h"
#include "OgreTrays.h"

InfoOverlay::InfoOverlay(int lives, int points, double width, double heigth, OgreBites::TrayManager* trayMgr) 
	: _lives(lives), _points(points), _trayMgr(trayMgr)
{
	_label = _trayMgr->createLabel(OgreBites::TL_BOTTOMRIGHT, "infoLabel", "LVL 1", width);
	_textBox = _trayMgr->createTextBox(OgreBites::TL_BOTTOMRIGHT, "testeBox", "Info", width, heigth);
	_textBox->setText(parseTextBoxInfo());
}

std::string 
InfoOverlay::parseTextBoxInfo() {
	return "Lives: " + std::to_string(_lives) + "\nPoints: " + std::to_string(_points);
}

void 
InfoOverlay::setLives(int lives) {
	_lives = lives;
	_textBox->setText(parseTextBoxInfo());
}
void 
InfoOverlay::setPoints(int points) {
	_points = points;
	_textBox->setText(parseTextBoxInfo());
}

int 
InfoOverlay::getLives()const {
	return _lives;
}
int 
InfoOverlay::getPoints()const {
	return _points;
}
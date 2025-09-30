#include "Labirynth.h"
#include <fstream>
#include <iostream>

Labirynth::Labirynth(std::string filePath, Ogre::SceneManager* sceneManager) : mSM(sceneManager) 
{
	std::ifstream input(filePath);

	input >> numFilas >> numColumnas;

	for (int i = 0; i < numFilas; ++i) {
		std::string fila;
		std::getline(input, fila);

		std::cout << fila;
	}
}
#pragma once

#include <cstdlib>
#include <iostream>
#include "ConfigParser.h"

int main()
{
	/*
	Erstelle und lade Konfiguration
	*/
	ConfigParser l_clsParser;
	l_clsParser.Load("game.cfg");
	/*
	Testweise Ausgabe
	*/
	cout << "Spinning: " << l_clsParser.GetSpinning() << endl;
	cout << "Spin Speed: " << l_clsParser.GetSpinSpeed() << endl;
	cout << "Background Color: " << l_clsParser.GetBackgroundColor().toString() << endl;
	cout << "Terrain Path: " << l_clsParser.GetTerrainPath() << endl;
	cout << "Terrain Width: " << l_clsParser.GetTerrainWidth() << endl;
	cout << "Terrain Depth: " << l_clsParser.GetTerrainDepth() << endl;
	cout << "Terrain Height: " << l_clsParser.GetTerrainHeight() << endl;
	/*
	Ende
	*/
	system("pause");
    return 0;
}
